// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "_aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D {
  public:
    // dibuja el objeto en modo inmediato
    void draw_immediate();

    // dibuja el objeto en modo diferido (usando VBOs)
    void draw_buffered();

    // función que redibuja el objeto
    // está función llama a 'draw_immediate' (modo inmediato)
    // o bien a 'draw_buffered' (modo diferido, VBOs)
    void draw();

  protected:
    void calcular_normales(); // calcula tabla de normales de vértices (práctica 3)

    std::vector<Tupla3f> v; // tabla de coordenadas de vértices (una tupla por
                            // vértice, con tres floats)
    std::vector<Tupla3i> f; // una terna de 3 enteros por cada cara o triángulo

  public:
    virtual ~Malla3D() = 0;
    // completar: tabla de colores, tabla de normales de vértices
};

#endif