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
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());
    glDrawElements(GL_TRIANGLES, 3*triangles.size(), GL_UNSIGNED_INT, triangles.data());
    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_buffered()
{
    if (vertices_VBO_id & triangles_VBO_id == 0) {
        vertices_VBO_id = create_VBO(GL_ARRAY_BUFFER, 3*vertices.size(), vertices.data());
        triangles_VBO_id = create_VBO(GL_ELEMENT_ARRAY_BUFFER, 3*triangles.size(), triangles.data());
    }

    
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_immediate o bien a draw_buffered

void Malla3D::draw()
{
    draw_immediate();
}

GLuint Malla3D::create_VBO(GLuint target, GLsizeiptr size, const void* data, GLuint usage) {
    GLuint vbo_id;
    glGenBuffers(1, &vbo_id);
    glBindBuffer(target, vbo_id);
    glBufferData(target, size, data, usage);
    glBindBuffer(target, 0);
    return vbo_id;
}