#include "cone.h"

Cone::Cone(int num_vertices_side_face, int num_instances, float height, float radius) {
    constexpr int Y_axis = 1;
    std::vector<Tupla3f> perfil;
    float h = height/num_vertices_side_face;
    float r = radius/num_vertices_side_face;
    for (int i = 0; i < num_vertices_side_face; i++) {
        perfil.emplace_back(i*r, (num_vertices_side_face-i-1)*h, 0.0);
    }
    make_revolution_surface(perfil, num_instances, true, true, Y_axis);
    force_cover_north = true;
    init_color(vertices.data.size());
    init_normal_vectors();
}