#include "tetraedro.h"
#include "_aux.h"
#include "malla.h"

Tetraedro::Tetraedro(float l)
{
    const float  x_offset = l / 2;
    const float  y_offset = sqrt(5*l*l/4) / 2;
    const float& z_offset = y_offset;

    vertices.emplace_back(-x_offset, -y_offset, -z_offset);
    vertices.emplace_back( x_offset, -y_offset, -z_offset);
    vertices.emplace_back(        0, -y_offset,  z_offset);
    vertices.emplace_back(        0,  y_offset,         0);

    indices.emplace_back(0, 3, 1);
    indices.emplace_back(0, 2, 3);
    indices.emplace_back(2, 1, 3);
    indices.emplace_back(0, 1, 2);
}