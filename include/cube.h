/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED

#include "_aux.h"
#include "malla.h"

class Cube : public Malla3D {
  public:
    Cube(float l = 1);

    void set_color_rgb_cube(void);
};

#endif /* CUBO_H_INCLUDED */