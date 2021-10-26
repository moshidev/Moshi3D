/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED

#include "_aux.h"
#include "mesh.h"

class Cube : public Mesh3D {
    void cube_init_vertices(std::vector<Tupla3f>& v, float lado);
    void cube_init_indices(std::vector<Tupla3u>& i);

public:
    Cube(float l = 1);

    void set_color_rgb_cube(void);
};

#endif /* CUBO_H_INCLUDED */