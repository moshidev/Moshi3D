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