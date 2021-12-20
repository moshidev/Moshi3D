/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED

#include "_aux.h"
#include "mesh.h"
#include <vector>
#include <memory>

class Cube : public Mesh3D {
    void cube_init_vertices(std::vector<Tupla3f>& v, float lado);
    void cube_init_indices(std::vector<Tupla3u>& i);
    void cube_init_texture_coordinates(std::vector<Tupla2f>& tc);
    VertexBuffer<Tupla2f> texture_coordinates;

public:
    Cube(float l = 1);
    void set_texture(const std::shared_ptr<TextureObject>& texture);
};

#endif /* CUBO_H_INCLUDED */