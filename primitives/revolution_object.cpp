#include "ply_reader.h"
#include "revolution_object.h"

static bool operator<(const Tupla3f& a, const Tupla3f& b) {
    return a[1] < b[1] ||
            (a[1] == b[1] && (a[0] < b[0])) ||
            (a[1] == b[1] && (a[0] == b[0]) && (a[2] < b[2]));
}

void RevolutionObject::make_mesh(std::vector<Tupla3f> revolution_coordinates, std::vector<Tupla3f>& result, int num_instances) {
    std::vector<Tupla3f>& rv = revolution_coordinates;
    Tupla3f south, north;
    result.clear();
    result.reserve(rv.size()*num_instances);
    std::sort(rv.begin(), rv.end());

    for (int i = 0; i < num_instances; i++) {
        double angle = -2*M_PI/num_instances * i;
        for (const auto& c : rv) {
            result.emplace_back(c[0]*cos(angle)*150.0f, c[1]*150.0f-75.0f, c[0]*sin(angle)*150.0f);
        }
    }

    int midpoint = num_instances*(rv.size()-1);
    indices.resize(2*midpoint);
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

RevolutionObject::RevolutionObject(const std::string& ifile, int num_instances, bool upper_surface, bool lower_surface) {
    std::vector<Tupla3f> coordinates;
    ply::read_vertices(ifile, coordinates);
    make_mesh(coordinates, vertices, num_instances);
    init_color(vertices.size());
}

RevolutionObject::RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool upper_surface, bool lower_surface) {
    make_mesh(revolution_coordinates, vertices, num_instances);
    init_color(vertices.size());
}