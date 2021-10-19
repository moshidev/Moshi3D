/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer.h"
#include "malla.h"
#include "_aux.h"
#include <iostream>

Malla3D::Malla3D() {
    enable_polygon_modes(GL_FILL);
}

Malla3D::~Malla3D() {}

void Malla3D::draw(const Renderer& r) {
    r.render(*this);
}

void Malla3D::set_color_chess(void) {
    color.set_chess(*this);
}

void Malla3D::set_color_plain(void) {
    color.set_plain(*this);
}

GLuint Malla3D::create_VBO(GLuint target, GLsizeiptr size, const void* data, GLuint usage) {
    GLuint vbo_id;
    glGenBuffers(1, &vbo_id);
    glBindBuffer(target, vbo_id);
    glBufferData(target, size, data, usage);
    glBindBuffer(target, 0);
    return vbo_id;
}

GLuint Malla3D::get_vertices_VBO_id(void) {
    if (vertices_VBO_id == 0) {
        vertices_VBO_id = create_VBO(GL_ARRAY_BUFFER, sizeof(Tupla3f)*vertices.size(), vertices.data());
    }
    return vertices_VBO_id;
}

GLuint Malla3D::get_indices_VBO_id(void) {
    if (indices_VBO_id == 0) {
        indices_VBO_id = create_VBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(Tupla3u)*indices.size(), indices.data());
    }
    return indices_VBO_id;
}