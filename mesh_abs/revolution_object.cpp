#include "file_io/ply_reader.h"
#include "revolution_object.h"
#include <algorithm>

RevolutionObject::RevolutionObject() {}

RevolutionObject::RevolutionObject(const std::string& ifile, int num_instances, bool make_covers) {
    std::vector<Tupla3f> revolution_coordinates;
    ply::read_vertices(ifile, revolution_coordinates);
    make_revolution_surface(revolution_coordinates, num_instances, make_covers, make_covers);
    init_color(vertices.data.size());
    init_normal_vectors();
}

RevolutionObject::RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool make_covers) {
    make_revolution_surface(revolution_coordinates, num_instances, make_covers, make_covers);
    init_color(vertices.data.size());
    init_normal_vectors();
}

RevolutionObject::RevolutionObject(const std::string& ifile, int num_instances, bool make_cover_south, bool make_cover_north, int axis) {
    std::vector<Tupla3f> revolution_coordinates;
    ply::read_vertices(ifile, revolution_coordinates);
    make_revolution_surface(revolution_coordinates, num_instances, make_cover_south, make_cover_north, axis);
    init_color(vertices.data.size());
    init_normal_vectors();
}

RevolutionObject::RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool make_cover_south, bool make_cover_north, int axis) {
    make_revolution_surface(revolution_coordinates, num_instances, make_cover_south, make_cover_north, axis);
    init_color(vertices.data.size());
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
    revolution_surface_make_texture_coordinates(rv, num_instances, axis, south[axis], north[axis]);

    const int height = rv.size();
    if (make_cover_south) {
        covers_make_south(south, num_instances, height);
    }
    if (make_cover_north) {
        covers_make_north(north, num_instances, height);
    }
}

void RevolutionObject::revolution_surface_make_geometry(std::vector<Tupla3f>& rv, int num_instances, int axis) {
    for (int i = 0; i < num_instances + 1; i++) {
        double angle = 2*M_PI/num_instances * i;
        double _sin = sin(angle);
        double _cos = cos(angle);
        for (const auto& c : rv) {
            if (axis == 0)       // X axis
                vertices.data.emplace_back(c[0], c[1]*_cos-c[2]*_sin, c[1]*_sin+c[2]*_cos);
            else if (axis == 1)  // Y axis
                vertices.data.emplace_back(c[0]*_cos+c[2]*_sin, c[1], -c[0]*_sin+c[2]*_cos);
            else                // Z axis
                vertices.data.emplace_back(c[0]*_cos-c[1]*_sin, c[0]*_sin+c[1]*_cos, c[2]);
        }
    }
}

void RevolutionObject::revolution_surface_make_texture_coordinates(const std::vector<Tupla3f>& rv, int num_instances, int axis, float low_p, float top_p) {
    for (int i = 0; i < num_instances+1; i++) {
        const float x = ((float)i)/num_instances;
        for (const auto& p : rv) {
            const float y = (p[axis]-low_p) / (top_p-low_p);
            texture_coordinates.data.emplace_back(x, y);
        }
    }
}

void RevolutionObject::revolution_surface_make_topology(const std::vector<Tupla3f>& rv, int num_instances) {
    const int midpoint = num_instances*(rv.size()-1);
    indices.data.resize(2*midpoint);

    for (int i = 0; i < num_instances; i++) {
        for (int j = 0; j < (rv.size()-1); j++) {
            int a = i*rv.size()+j;                      // Vértice columna i
            int b = (i+1)*rv.size()+j;  // Vértice columna i+1
            int offset = i*(rv.size()-1) + j;
            indices.data[offset] = {a, b, b+1};
            indices.data[offset+midpoint] = {a, b+1, a+1};   // Los impares los insertamos a partir de la mitad para el modo ajedrez
        }
    }
}

void RevolutionObject::covers_make_south(const Tupla3f& south, int num_instances, int height) {
    covers_make_geometry(south, num_instances);
    covers_make_topology(cover_south_indices.data, vertices.data.size()-num_instances, num_instances, height, 0, false);
    covers_make_texture_coordinates(vertices.data.size()-num_instances, num_instances, 0);
}

void RevolutionObject::covers_make_north(const Tupla3f& north, int num_instances, int height) {
    covers_make_geometry(north, num_instances);
    covers_make_topology(cover_north_indices.data, vertices.data.size()-num_instances, num_instances, height, height-1, true);
    covers_make_texture_coordinates(vertices.data.size()-num_instances, num_instances, 1);
}

void RevolutionObject::covers_make_texture_coordinates(int min_shared_vertice_index, int num_instances, float y) {
    for (int i = 0; i < num_instances; i++) {
        texture_coordinates.data.emplace_back(((float)i)/num_instances, y);
    }
    texture_coordinates.data.emplace_back(1, y);
}

void RevolutionObject::covers_make_topology(std::vector<Tupla3u>& ci, int shared_vertice_index, int num_instances, int height, int height_offset, bool clockwise) {
    int a, b;
    int& v1 = clockwise ? a : b;
    int& v2 = clockwise ? b : a;

    ci.resize(num_instances);
    for (int i = 0; i < 2; i++) {
        for (int j = i; j < num_instances; j+=2) {
            a = j*height + height_offset;
            b = ((j+1)%num_instances)*height + height_offset;
            ci[j/2+i*num_instances/2] = {shared_vertice_index + j, v1, v2};
        }
    }
}

void RevolutionObject::covers_make_geometry(const Tupla3f& pole, int num_instances) {
    for (int i = 0; i < num_instances; i++) {
        vertices.data.push_back(pole);
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
    pole(b) = 0.001;
}

void RevolutionObject::init_normal_vectors(void) {
    std::vector<Tupla3f> cover_south_indices_normal;
    std::vector<Tupla3f> cover_north_indices_normal;
    std::vector<Tupla3f> indices_normal;
    compute_normal_faces(indices_normal, indices.data);
    compute_normal_faces(cover_south_indices_normal, cover_south_indices.data);
    compute_normal_faces(cover_north_indices_normal, cover_north_indices.data);
    sum_normal_faces_to_vertices_normals(indices_normal, indices.data);
    sum_normal_faces_to_vertices_normals(cover_south_indices_normal, cover_south_indices.data);
    sum_normal_faces_to_vertices_normals(cover_north_indices_normal, cover_north_indices.data);
    normalize_vertices_normals();
}

void RevolutionObject::make_current_data_list(void) {
    auto& cl = current_data_list;

    cl.clear();
    cl.splice(cl.begin(), mklist_polygon_mode(indices));
    cl.splice(cl.begin(), mklist_chess_mode(indices));
    cl.splice(cl.begin(), mklist_shaded_mode(indices, material));
    if (render_cover_south) {
        init_index_buffer(cover_south_indices);
        cl.splice(cl.begin(), mklist_polygon_mode(cover_south_indices));
        cl.splice(cl.begin(), mklist_chess_mode(cover_south_indices));
        cl.splice(cl.begin(), mklist_shaded_mode(cover_south_indices, material));
    }
    if (render_cover_north) {
        init_index_buffer(cover_north_indices);
        cl.splice(cl.begin(), mklist_polygon_mode(cover_north_indices));
        cl.splice(cl.begin(), mklist_chess_mode(cover_north_indices));
        cl.splice(cl.begin(), mklist_shaded_mode(cover_north_indices, material));
    }
}

void RevolutionObject::enable_covers_visibility(bool b) {
    render_cover_south = cover_south_indices.data.empty() ? false : (force_cover_south ? true : b);
    render_cover_north = cover_north_indices.data.empty() ? false : (force_cover_north ? true : b);
    make_current_data_lists();
}

void RevolutionObject::set_texture(const std::shared_ptr<TextureObject>& texture) {
    this->texture = std::make_unique<Texture>(texture, texture_coordinates);
}