#include "color.h"
#include "malla.h"

GLuint Color::get_VBO_id(void) {
    if (color_VBO_id == 0) {
        color_VBO_id = Malla3D::create_VBO(GL_ARRAY_BUFFER, sizeof(Tupla3f)*color.size(), color.data());
    }

    return color_VBO_id;
}

void Color::update_VBO(void) {
    if (color_VBO_id != 0) {
        glBindBuffer(GL_ARRAY_BUFFER, color_VBO_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Tupla3f)*color.size(), color.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void Color::init(const Cube& c) {
    color.resize(8);
}

void Color::init(const Tetrahedron& t) {
    color.resize(4);
}

void Color::set_chess(const Malla3D& m, const Tupla3f& color_a, const Tupla3f& color_b) {
    color.clear();
    for (int i = 0; i < m.get_indices_size()/2; i++) {
        color.push_back(color_a);
        color.push_back(color_b);
    }
    update_VBO();
}

void Color::set_plain(const Malla3D& m, const Tupla3f& color_a) {
    color.clear();
    for (int i = 0; i < m.get_indices_size(); i++) {
        color.push_back(color_a);
    }
    update_VBO();
}

void Color::set_rgb(const Cube& c) {
    color.clear();
    for (int i = 0; i < 8; i++) {
        Tupla3f t {
            1.0 * (i & 0x1),
            1.0 * ((i & 0x2) >> 1),
            1.0 * ((i & 0x4) >> 2)
        };
        color.push_back(t);
    }
    std::swap(color[4], color[5]);
    std::swap(color[6], color[7]);
    update_VBO();
}