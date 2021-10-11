/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "primitive_colorizer.h"

void PrimitiveColorizer::plain_color(Malla3D& m, const Tupla3f& color) {
    std::vector<Tupla3f> color_v{m.get_num_vertices(), color};
    m.set_color_array(color_v);
}

void PrimitiveColorizer::chess(Tetraedro& t, const Tupla3f& color_a, const Tupla3f& color_b) {
    std::vector<Tupla3f> color_v{4, color_a};
    color_v[1] = color_b;
    color_v[3] = color_b;
    t.set_color_array(color_v);
}

void PrimitiveColorizer::chess(Cube& c, const Tupla3f& color_a, const Tupla3f& color_b) {
    std::vector<Tupla3f> color_v;
    for (int i = 0; i < 4; i++) {
        color_v.emplace_back(color_a);
        color_v.emplace_back(color_b);
    }
    c.set_color_array(color_v);
}

void PrimitiveColorizer::rgb_cube(Cube& c) {
    std::vector<Tupla3f> color_v;
    color_v.resize(8);
    for (int i = 0; i < 8; i++) {
        color_v[i] = Tupla3f{1.0 * (i & 0x1), 1.0 * ((i & 0x2) >> 1), 1.0 * ((i & 0x4) >> 2)};
    }
    std::swap(color_v[4], color_v[5]);
    std::swap(color_v[6], color_v[7]);
    c.set_color_array(color_v);
}