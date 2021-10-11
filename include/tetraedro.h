// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: tetraedro.h

//
// #############################################################################

#ifndef TETRAEDRO_H_INCLUDED
#define TETRAEDRO_H_INCLUDED

#include "_aux.h"
#include "malla.h"

class Tetraedro : public Malla3D {
  public:
    Tetraedro(float l = 1);
};

#endif /* TETRAEDRO_H_INCLUDED */