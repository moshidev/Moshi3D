/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef TETRAEDRO_H_INCLUDED
#define TETRAEDRO_H_INCLUDED

#include "_aux.h"
#include "malla.h"

class Tetrahedron : public Malla3D {
  public:
    Tetrahedron(float l = 1);
};

#endif /* TETRAEDRO_H_INCLUDED */