/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer.h"
#include "mesh.h"
#include "_aux.h"
#include <iostream>

Mesh3D::Mesh3D() {
    enable_polygon_modes(GL_FILL);
}

Mesh3D::~Mesh3D() {}

void Mesh3D::draw(const Renderer& r) {
    r.render(*this);
}

void Mesh3D::set_color_chess(void) {
    color.set_chess(*this);
}

void Mesh3D::set_color_plain(void) {
    color.set_plain(*this);
}

GLuint Mesh3D::create_VBO(GLuint target, GLsizeiptr size, const void* data, GLuint usage) {
    GLuint vbo_id;
    glGenBuffers(1, &vbo_id);
    glBindBuffer(target, vbo_id);
    glBufferData(target, size, data, usage);
    glBindBuffer(target, 0);
    return vbo_id;
}

const VertexBuffer& Mesh3D::get_vertices_VBO(void) {
    if (vertices_VBO == nullptr) {
        vertices_VBO = new VertexBuffer(sizeof(Tupla3f)*vertices.size(), vertices.data());
    }
    return *vertices_VBO;
}

const IndexBuffer& Mesh3D::get_indices_VBO(void) {
    if (indices_VBO == nullptr) {
        indices_VBO = new IndexBuffer(3*indices.size(), indices.data());
    }
    return *indices_VBO;
}