#include "file_io/ply_reader.h"
#include "revolution_object.h"
#include <algorithm>

static bool operator<(const Tupla3f& a, const Tupla3f& b) {
    return a[1] < b[1] ||
            (a[1] == b[1] && (a[0] < b[0])) ||
            (a[1] == b[1] && (a[0] == b[0]) && (a[2] < b[2]));
}

RevolutionObject::RevolutionObject() {}

RevolutionObject::RevolutionObject(const std::string& ifile, int num_instances, bool make_covers) {
    std::vector<Tupla3f> revolution_coordinates;
    ply::read_vertices(ifile, revolution_coordinates);
    make_revolution_surface(revolution_coordinates, num_instances, make_covers);
    init_color(vertices.size());
    has_covers = covers_enabled = make_covers;
}

RevolutionObject::RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool make_covers) {
    make_revolution_surface(revolution_coordinates, num_instances, make_covers);
    init_color(vertices.size());
    has_covers = covers_enabled = make_covers;
}

void RevolutionObject::make_revolution_surface(std::vector<Tupla3f> revolution_coordinates, int num_instances, bool make_covers) {
    std::vector<Tupla3f>& rv = revolution_coordinates;
    Tupla3f south, north;
    std::sort(rv.begin(), rv.end());
    covers_extract_poles(rv, south, north);

    revolution_surface_make_geometry(rv, num_instances);
    revolution_surface_make_topology(rv, num_instances);

    int i = 0;
    if (make_covers) {
        int height = rv.size()-1;
        covers_make_south(south, num_instances);
        covers_make_north(north, num_instances, height);
    }
}

void RevolutionObject::revolution_surface_make_geometry(std::vector<Tupla3f>& rv, int num_instances) {
    for (int i = 0; i < num_instances; i++) {
        double angle = -2*M_PI/num_instances * i;
        for (const auto& c : rv) {
            vertices.emplace_back(c(0)*cos(angle), c(1), c(0)*sin(angle));
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
    covers.emplace_back(cover_south_IB, cover_south);
    covers_make_topology(cover_south, vertices.size()-1, num_instances, 0, false);
}

void RevolutionObject::covers_make_north(const Tupla3f& north, int num_instances, int height) {
    vertices.push_back(north);
    covers.emplace_back(cover_north_IB, cover_north);
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

void RevolutionObject::covers_extract_poles(std::vector<Tupla3f>& rv, Tupla3f& south, Tupla3f& north) {
    covers_extract_pole(rv, --rv.end(), north);
    covers_extract_pole(rv, rv.begin(), south);
}

void RevolutionObject::covers_extract_pole(std::vector<Tupla3f>& rv, std::vector<Tupla3f>::iterator it, Tupla3f& pole) {
    constexpr int x = 0, y = 1, z = 2;
    pole = *it;
    if (pole(x) == 0.0 && pole(z) == 0.0) {
        rv.erase(it);
    }
    pole(x) = 0.0;
    pole(z) = 0.0;
}

void RevolutionObject::make_current_buffered_data_list(void) {
    auto& list = current_buffered_data_list;

    list.clear();
    list.splice(list.begin(), mklist_buffered_polygon_mode(get_vertices_VB(), get_indices_IB()));
    list.splice(list.begin(), mklist_buffered_chess_mode(get_vertices_VB(), get_indices_IB()));
    if (covers_enabled) {
        for (auto& [ib,v] : covers) {
            init_index_buffer(ib, v);
            list.splice(list.begin(), mklist_buffered_polygon_mode(get_vertices_VB(), ib));
            list.splice(list.begin(), mklist_buffered_chess_mode(get_vertices_VB(), ib));
        }
    }
}

void RevolutionObject::make_current_raw_data_list(void) {
    auto& list = current_raw_data_list;

    list.clear();
    list.splice(list.begin(), mklist_raw_polygon_mode(vertices, indices));
    list.splice(list.begin(), mklist_raw_chess_mode(vertices, indices));
    if (covers_enabled) {
        for (auto& [ib,i] : covers) {
            list.splice(list.begin(), mklist_raw_polygon_mode(vertices, i));
            list.splice(list.begin(), mklist_raw_chess_mode(vertices, i));
        }
    }
}

void RevolutionObject::enable_covers_visibility(bool b) {
    covers_enabled = has_covers ? b : false;    // ...?
    make_current_data_lists();
}