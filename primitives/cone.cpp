#include "cone.h"

Cone::Cone(int num_vertices_side_face, int num_instances, float height, float radius, bool make_north_cover) {
    std::vector<Tupla3f> perfil;
    float h = height/num_vertices_side_face;
    float r = radius/num_vertices_side_face;
    for (int i = 0; i < num_vertices_side_face; i++) {
        perfil.emplace_back(i*r, (num_vertices_side_face-i-1)*h, 0.0);
    }
    make_revolution_surface(perfil, num_instances, true, make_north_cover);
    init_color(vertices.size());
}