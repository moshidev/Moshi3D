/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "_aux.h"
#include "mesh.h"
#include "cube.h"

void Cube::cube_init_vertices(std::vector<Tupla3f>& v, float lado) {
   const float offset = lado/2;
   v.reserve(8);
   v.emplace_back(-offset, -offset, -offset);
   v.emplace_back(-offset, -offset,  offset);
   v.emplace_back(-offset,  offset, -offset);
   v.emplace_back(-offset,  offset,  offset);
   v.emplace_back(offset, -offset, -offset);
   v.emplace_back(offset, -offset,  offset);
   v.emplace_back(offset,  offset, -offset);
   v.emplace_back(offset,  offset,  offset);
   
   v.resize(8);
}

void Cube::cube_init_indices(std::vector<Tupla3u>& i) {
   i.reserve(12);
   i.emplace_back(0, 3, 2);
   i.emplace_back(1, 7, 3);
   i.emplace_back(7, 5, 4);
   i.emplace_back(6, 4, 0);
   i.emplace_back(5, 1, 0);
   i.emplace_back(2, 7, 6);

   i.emplace_back(0, 1, 3);
   i.emplace_back(1, 5, 7);
   i.emplace_back(7, 4, 6);
   i.emplace_back(6, 0, 2);
   i.emplace_back(5, 0, 4);
   i.emplace_back(2, 3, 7);
   i.resize(12);
}

Cube::Cube(float lado) {
   cube_init_vertices(vertices, lado);
   cube_init_indices(indices);
   init_color(vertices.size());
}