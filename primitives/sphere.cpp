#include "sphere.h"

Sphere::Sphere(int num_vertices_side_face, int num_instances, float radius) {
    std::vector<Tupla3f> perfil;
    double d = M_PI/num_vertices_side_face;
    perfil.emplace_back(0.0f, -radius, 0.0f);
    for (int i = 1; i < num_vertices_side_face; i++) {
        perfil.emplace_back(radius*cos(i*d-M_PI_2), radius*sin(i*d-M_PI_2), 0.0f);
    }
    perfil.emplace_back(0.0f, radius, 0.0f);
    make_revolution_surface(perfil, num_instances);
    init_color(vertices.size());
}