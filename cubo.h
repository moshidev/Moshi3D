// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED

#include "_aux.h"
#include "malla.h"

class Cubo : public Malla3D {
  public:
    Cubo(float l = 1);
};

#endif /* CUBO_H_INCLUDED */