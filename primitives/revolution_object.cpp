#include "ply_reader.h"
#include "revolution_object.h"

static bool operator<(const Tupla3f& a, const Tupla3f& b) {
    return a[1] < b[1] ||
            (a[1] == b[1] && (a[0] < b[0])) ||
            (a[1] == b[1] && (a[0] == b[0]) && (a[2] < b[2]));
}

void RevolutionObject::revolution_surface_make_topology(const std::vector<Tupla3f>& rv, int num_instances, int midpoint) {
    for (int i = 0; i < num_instances; i++) {
        for (int j = 0; j < (rv.size()-1); j++) {
            int a = i*rv.size()+j;                      // Vértice columna i
            int b = ((i+1)%num_instances)*rv.size()+j;  // Vértice columna i+1
            int offset = i*(rv.size()-1) + j;
            indices[offset] = {a, b, b+1};
            indices[offset+midpoint] = {a, b+1, a+1};   // Los impares los insertamos a partir de la mitad para el modo ajedréz
        }
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

void RevolutionObject::covers_extract_pole(std::vector<Tupla3f>& rv, std::vector<Tupla3f>::iterator it, Tupla3f& pole) {
    constexpr int x = 0, y = 1, z = 2;
    pole = *it;
    if (pole(x) == 0.0 && pole(z) == 0.0) {
        rv.erase(it);
    }
    pole(x) = 0.0;
    pole(z) = 0.0;
}

void RevolutionObject::covers_extract_poles(std::vector<Tupla3f>& rv, Tupla3f& south, Tupla3f& north) {
    covers_extract_pole(rv, --rv.end(), north);
    covers_extract_pole(rv, rv.begin(), south);
}

void RevolutionObject::covers_make_topology(int shared_vertice_index, int num_instances, int height_offset, int index_offset_a, int index_offset_b, bool clockwise) {
    int a, b;
    int& v1 = clockwise ? a : b;
    int& v2 = clockwise ? b : a;
    const int distance = vertices.size() / num_instances;
    for (int i = 0; i < num_instances; i++) {
        const int& offset = i%2 ? index_offset_b : index_offset_a;
        a = i*distance + height_offset;
        b = ((i+1)%num_instances)*distance + height_offset;
        indices[offset + i] = {shared_vertice_index, v1, v2};
    }
}

void RevolutionObject::covers_make_south(const Tupla3f& south, int num_instances, int midpoint, int offset) {
    vertices.push_back(south);
    covers_make_topology(vertices.size()-1, num_instances, 0, midpoint-offset, 2*midpoint-offset, false);
}

void RevolutionObject::covers_make_north(const Tupla3f& north, int num_instances, int height, int midpoint, int offset) {
    vertices.push_back(north);
    covers_make_topology(vertices.size()-1, num_instances, height, midpoint-offset, 2*midpoint-offset, true);
}

void RevolutionObject::make_revolution_surface(std::vector<Tupla3f> revolution_coordinates, int num_instances, bool make_south_cover, bool make_north_cover) {
    std::vector<Tupla3f>& rv = revolution_coordinates;
    Tupla3f south, north;
    std::sort(rv.begin(), rv.end());
    covers_extract_poles(rv, south, north);

    int midpoint = num_instances*(rv.size()-1) + (make_south_cover ? num_instances : 0) + (make_north_cover ? num_instances : 0);
    indices.resize(2*midpoint);
    revolution_surface_make_geometry(rv, num_instances);
    revolution_surface_make_topology(rv, num_instances, midpoint);

    int i = 0;
    if (make_south_cover) {
        covers_make_south(south, num_instances, midpoint, (++i)*num_instances);
    }
    if (make_north_cover) {
        covers_make_north(north, num_instances, rv.size()-1, midpoint, (++i)*num_instances);
    }
}

RevolutionObject::RevolutionObject() {}

RevolutionObject::RevolutionObject(const std::string& ifile, int num_instances, bool make_south_cover, bool make_north_cover) {
    std::vector<Tupla3f> revolution_coordinates;
    ply::read_vertices(ifile, revolution_coordinates);
    make_revolution_surface(revolution_coordinates, num_instances, make_south_cover, make_north_cover);
    init_color(vertices.size());
}

RevolutionObject::RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool make_south_cover, bool make_north_cover) {
    make_revolution_surface(revolution_coordinates, num_instances, make_south_cover, make_north_cover);
    init_color(vertices.size());
}