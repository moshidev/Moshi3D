#include "malla.h"
#include "_aux.h"
#include <iostream>

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

Malla3D::~Malla3D() {}

void Malla3D::draw_immediate()
{
    glEnable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());
    glDrawElements(GL_TRIANGLES, 3*indices.size(), GL_UNSIGNED_INT, indices.data());
    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void set_vertex_pointer(GLuint vertex_vbo_id) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo_id);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void draw_elements_from_indices(GLuint indices_vbo_id, GLsizei count) {
    glEnable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Malla3D::draw_buffered()
{
    if (vertices_VBO_id == 0) {
        vertices_VBO_id = create_VBO(GL_ARRAY_BUFFER, sizeof(Tupla3f)*vertices.size(), vertices.data());
    }
    if (indices_VBO_id == 0) {
        indices_VBO_id = create_VBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(Tupla3u)*indices.size(), indices.data());
    }

    glEnable(GL_CULL_FACE);
    set_vertex_pointer(vertices_VBO_id);
    draw_elements_from_indices(indices_VBO_id, 3*indices.size());
}

void Malla3D::draw()
{
    draw_buffered();
}

GLuint Malla3D::create_VBO(GLuint target, GLsizeiptr size, const void* data, GLuint usage) {
    GLuint vbo_id;
    glGenBuffers(1, &vbo_id);
    glBindBuffer(target, vbo_id);
    glBufferData(target, size, data, usage);
    glBindBuffer(target, 0);
    return vbo_id;
}