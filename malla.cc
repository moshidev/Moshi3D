#include "malla.h"
#include "_aux.h"
#include <iostream>

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

Malla3D::~Malla3D() {}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_immediate()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v.data());
    glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_buffered()
{
    // (la primera vez, se deben crear los VBOs y guardar sus identificadores en
    // el objeto) completar (práctica 1)
    // .....
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_immediate o bien a draw_buffered

void Malla3D::draw()
{
    draw_immediate();
}