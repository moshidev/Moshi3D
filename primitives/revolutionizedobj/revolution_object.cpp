#include "file_io/ply_reader.h"
#include "revolution_object.h"
#include <algorithm>

RevolutionObject::RevolutionObject() {}

RevolutionObject::RevolutionObject(const std::string& ifile, int num_instances, bool make_covers) {
    std::vector<Tupla3f> revolution_coordinates;
    ply::read_vertices(ifile, revolution_coordinates);
    make_revolution_surface(revolution_coordinates, num_instances, make_covers, make_covers);
    init_color(vertices.size());
    init_normal_vectors();
}

RevolutionObject::RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool make_covers) {
    make_revolution_surface(revolution_coordinates, num_instances, make_covers, make_covers);
    init_color(vertices.size());
    init_normal_vectors();
}

RevolutionObject::RevolutionObject(const std::string& ifile, int num_instances, bool make_cover_south, bool make_cover_north, int axis) {
    std::vector<Tupla3f> revolution_coordinates;
    ply::read_vertices(ifile, revolution_coordinates);
    make_revolution_surface(revolution_coordinates, num_instances, make_cover_south, make_cover_north, axis);
    init_color(vertices.size());
    init_normal_vectors();
}

RevolutionObject::RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool make_cover_south, bool make_cover_north, int axis) {
    make_revolution_surface(revolution_coordinates, num_instances, make_cover_south, make_cover_north, axis);
    init_color(vertices.size());
    init_normal_vectors();
}

static void ordenar(std::vector<Tupla3f>& rv, int axis) {
    if (rv.front()[axis] > rv.back()[axis]) {
        int size = rv.size();
        int mid = rv.size()/2;
        for (int i = 0; i < mid; i++) {
            std::swap(rv[i], rv[size-i-1]);
        }
    }
}

void RevolutionObject::make_revolution_surface(std::vector<Tupla3f> revolution_coordinates, int num_instances, bool make_cover_south, bool make_cover_north, int axis) {
    std::vector<Tupla3f>& rv = revolution_coordinates;
    Tupla3f south, north;
    ordenar(rv, axis);
    covers_extract_poles(rv, south, north, axis);

    revolution_surface_make_geometry(rv, num_instances, axis);
    revolution_surface_make_topology(rv, num_instances);

    if (make_cover_south) {
        covers_make_south(south, num_instances);
    }
    if (make_cover_north) {
        int height = rv.size()-1;
        covers_make_north(north, num_instances, height);
    }
}

void RevolutionObject::revolution_surface_make_geometry(std::vector<Tupla3f>& rv, int num_instances, int eje) {
    for (int i = 0; i < num_instances; i++) {
        double angle = 2*M_PI/num_instances * i;
        double _sin = sin(angle);
        double _cos = cos(angle);
        for (const auto& c : rv) {
            if (eje == 0)       // X axis
                vertices.emplace_back(c[0], c[1]*_cos-c[2]*_sin, c[1]*_sin+c[2]*_cos);
            else if (eje == 1)  // Y axis
                vertices.emplace_back(c[0]*_cos+c[2]*_sin, c[1], -c[0]*_sin+c[2]*_cos);
            else                // Z axis
                vertices.emplace_back(c[0]*_cos-c[1]*_sin, c[0]*_sin+c[1]*_cos, c[2]);
        }
    }
}

void RevolutionObject::revolution_surface_make_topology(const std::vector<Tupla3f>& rv, int num_instances) {
    const int midpoint = num_instances*(rv.size()-1);
    indices.resize(2*midpoint);

    for (int i = 0; i < num_instances; i++) {
        for (int j = 0; j < (rv.size()-1); j++) {
            int a = i*rv.size()+j;                      // Vértice columna i
            int b = ((i+1)%num_instances)*rv.size()+j;  // Vértice columna i+1
            int offset = i*(rv.size()-1) + j;
            indices[offset] = {a, b, b+1};
            indices[offset+midpoint] = {a, b+1, a+1};   // Los impares los insertamos a partir de la mitad para el modo ajedrez
        }
    }
}

void RevolutionObject::covers_make_south(const Tupla3f& south, int num_instances) {
    vertices.push_back(south);
    covers_make_topology(cover_south, vertices.size()-1, num_instances, 0, false);
}

void RevolutionObject::covers_make_north(const Tupla3f& north, int num_instances, int height) {
    vertices.push_back(north);
    covers_make_topology(cover_north, vertices.size()-1, num_instances, height, true);
}

void RevolutionObject::covers_make_topology(std::vector<Tupla3u>& ci, int shared_vertice_index, int num_instances, int height_offset,bool clockwise) {
    int a, b;
    int& v1 = clockwise ? a : b;
    int& v2 = clockwise ? b : a;
    const int distance = vertices.size() / num_instances;

    ci.resize(num_instances);
    for (int i = 0; i < 2; i++) {
        for (int j = i; j < num_instances; j+=2) {
            a = j*distance + height_offset;
            b = ((j+1)%num_instances)*distance + height_offset;
            ci[j/2+i*num_instances/2] = {shared_vertice_index, v1, v2};
        }
    }
}

void RevolutionObject::covers_extract_poles(std::vector<Tupla3f>& rv, Tupla3f& south, Tupla3f& north, int axis) {
    covers_extract_pole(rv, --rv.end(), north, axis);
    covers_extract_pole(rv, rv.begin(), south, axis);
}

void RevolutionObject::covers_extract_pole(std::vector<Tupla3f>& rv, std::vector<Tupla3f>::iterator it, Tupla3f& pole, int axis) {
    constexpr double epsi = 0.0000002;
    int a = axis==0 ? 2 : axis-1;
    int b = axis==2 ? 0 : axis+1;

    pole = *it;
    if (pole(a) > -epsi && pole(a) < epsi && pole(b) > -epsi && pole(b) < epsi) {
        rv.erase(it);
    }
    pole(a) = 0.0;
    pole(b) = 0.0;
}

void RevolutionObject::init_normal_vectors(void) {
    compute_normal_faces(indices_normal, indices);
    compute_normal_faces(cover_south_normal, cover_south);
    compute_normal_faces(cover_north_normal, cover_north);
    sum_normal_to_vertices(indices_normal, indices);
    sum_normal_to_vertices(cover_south_normal, cover_south);
    sum_normal_to_vertices(cover_north_normal, cover_north);
    normalize_vertices();
}

void RevolutionObject::make_current_buffered_data_list(void) {
    auto& list = current_buffered_data_list;

    list.clear();
    list.splice(list.begin(), mklist_buffered_polygon_mode(get_vertices_VB(), get_indices_IB()));
    list.splice(list.begin(), mklist_buffered_chess_mode(get_vertices_VB(), get_indices_IB()));
    if (render_cover_south) {
        init_index_buffer(cover_south_IB, cover_south);
        list.splice(list.begin(), mklist_buffered_polygon_mode(get_vertices_VB(), cover_south_IB));
        list.splice(list.begin(), mklist_buffered_chess_mode(get_vertices_VB(), cover_south_IB));
    }
    if (render_cover_north) {
        init_index_buffer(cover_north_IB, cover_north);
        list.splice(list.begin(), mklist_buffered_polygon_mode(get_vertices_VB(), cover_north_IB));
        list.splice(list.begin(), mklist_buffered_chess_mode(get_vertices_VB(), cover_north_IB));
    }
}

void RevolutionObject::make_current_raw_data_list(void) {
    auto& list = current_raw_data_list;

    list.clear();
    list.splice(list.begin(), mklist_raw_polygon_mode(vertices, indices));
    list.splice(list.begin(), mklist_raw_chess_mode(vertices, indices));
    if (render_cover_south) {
        list.splice(list.begin(), mklist_raw_polygon_mode(vertices, cover_south));
        list.splice(list.begin(), mklist_raw_chess_mode(vertices, cover_south));
    }
    if (render_cover_north) {
        list.splice(list.begin(), mklist_raw_polygon_mode(vertices, cover_north));
        list.splice(list.begin(), mklist_raw_chess_mode(vertices, cover_north));
    }
}

void RevolutionObject::enable_covers_visibility(bool b) {
    render_cover_south = cover_south.empty() ? false : (force_cover_south ? true : b);
    render_cover_north = cover_north.empty() ? false : (force_cover_north ? true : b);
    make_current_data_lists();
}