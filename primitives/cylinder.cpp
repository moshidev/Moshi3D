#include "cylinder.h"

Cylinder::Cylinder(int num_vertices_side_face, int num_instances, float height, float radius) {
    constexpr int Y_axis = 1;
    std::vector<Tupla3f> perfil;
    float d = height/(num_vertices_side_face-1);
    for (int i = 0; i < num_vertices_side_face; i++) {
        perfil.emplace_back(radius, i*d, 0);
    }
    make_revolution_surface(perfil, num_instances, true, true, Y_axis);
    init_color(vertices.data.size());
    init_normal_vectors();
}