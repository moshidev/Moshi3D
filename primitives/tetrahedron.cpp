/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "tetrahedron.h"
#include "_aux.h"
#include "mesh.h"

Tetrahedron::Tetrahedron(float l)
{
    const float x_offset = l / 2;
    const float y_offset = sqrt(9*l*l/16) / 2;
    const float z_offset = sqrt(3*l*l/4) / 3;

    vertices.emplace_back(-x_offset, -y_offset, -z_offset);
    vertices.emplace_back( x_offset, -y_offset, -z_offset);
    vertices.emplace_back(        0, -y_offset,  z_offset*2);
    vertices.emplace_back(        0,  y_offset,         0);

    indices.emplace_back(1, 2, 0);
    indices.emplace_back(1, 0, 3);
    indices.emplace_back(2, 3, 0);
    indices.emplace_back(3, 2, 1);

    init_color(vertices.size());
}