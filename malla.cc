#include "renderer.h"
#include "malla.h"
#include "_aux.h"
#include <iostream>

Malla3D::~Malla3D() {}

void Malla3D::draw(const Renderer& r) {
    r.render(*this);
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

GLuint Malla3D::get_color_VBO_id(void) {
    if (color_VBO_id == 0) {
        color_VBO_id = create_VBO(GL_ARRAY_BUFFER, sizeof(Tupla3f)*color.size(), color.data());
    }

    return color_VBO_id;
}

void Malla3D::set_color_array(const std::vector<Tupla3f>& c) {
   color = c;
}