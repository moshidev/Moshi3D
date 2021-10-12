/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "_aux.h"
#include "malla.h"
#include "cube.h"

static void cube_init_vertices(std::vector<Tupla3f>& v, float lado) {
   const float offset = lado/2;
   v.reserve(8);
   v.emplace_back(-offset, -offset, -offset);
   v.emplace_back(-offset, -offset,  offset);
   v.emplace_back(-offset,  offset, -offset);
   v.emplace_back(-offset,  offset,  offset);
   v.emplace_back(offset, -offset,  offset);
   v.emplace_back(offset, -offset, -offset);
   v.emplace_back(offset,  offset,  offset);
   v.emplace_back(offset,  offset, -offset);
   v.resize(8);
}

static void cube_init_indices(std::vector<Tupla3u>& i) {
   i.reserve(12);
   i.emplace_back(3, 2, 0);
   i.emplace_back(0, 1, 3);
   i.emplace_back(3, 1, 6);
   i.emplace_back(4, 6, 1);
   i.emplace_back(7, 6, 4);
   i.emplace_back(4, 5, 7);
   i.emplace_back(7, 5, 2);
   i.emplace_back(0, 2, 5);
   i.emplace_back(1, 0, 4);
   i.emplace_back(4, 0, 5);
   i.emplace_back(6, 7, 3);
   i.emplace_back(3, 7, 2);
   i.resize(12);
}

static void cube_init_color(std::vector<Tupla3f>& c) {
   c.resize(8);
}

Cube::Cube(float lado)
{
   cube_init_vertices(vertices, lado);
   cube_init_indices(indices);
   cube_init_color(color);
}