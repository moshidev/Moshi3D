#include "sphere.h"

Sphere::Sphere(int num_vertices_side_face, int num_instances, float radius) {
    constexpr int Y_axis = 1;
    std::vector<Tupla3f> perfil;
    double d = M_PI/num_vertices_side_face;
    perfil.emplace_back(0.0f, -radius, 0.0f);
    for (int i = 1; i < num_vertices_side_face; i++) {
        perfil.emplace_back(radius*cos(i*d-M_PI_2), radius*sin(i*d-M_PI_2), 0.0f);
    }
    perfil.emplace_back(0.0f, radius, 0.0f);
    make_revolution_surface(perfil, num_instances, true, true, Y_axis);
    force_cover_south = force_cover_north = true;
    init_color(vertices.data.size());
    init_normal_vectors();
}