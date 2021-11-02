#include "cylinder.h"

Cylinder::Cylinder(int num_vertices_side_face, int num_instances, float height, float radius, bool make_south_cover, bool make_north_cover) {
    std::vector<Tupla3f> perfil;
    float d = height/num_vertices_side_face;
    for (int i = 0; i < num_vertices_side_face; i++) {
        perfil.emplace_back(radius, i*d, 0);
    }
    make_revolution_surface(perfil, num_instances, make_south_cover, make_north_cover);
    init_color(vertices.size());
}