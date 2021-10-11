#include "_aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   const float offset = lado/2;

   vertices.reserve(8);
   indices.reserve(12);
   
   vertices.emplace_back(-offset, -offset, -offset);
   vertices.emplace_back(-offset, -offset,  offset);
   vertices.emplace_back(-offset,  offset, -offset);
   vertices.emplace_back(-offset,  offset,  offset);
   vertices.emplace_back(offset, -offset,  offset);
   vertices.emplace_back(offset, -offset, -offset);
   vertices.emplace_back(offset,  offset,  offset);
   vertices.emplace_back(offset,  offset, -offset);

   indices.emplace_back(3, 2, 0);
   indices.emplace_back(0, 1, 3);
   indices.emplace_back(3, 1, 6);
   indices.emplace_back(4, 6, 1);
   indices.emplace_back(7, 6, 4);
   indices.emplace_back(4, 5, 7);
   indices.emplace_back(7, 5, 2);
   indices.emplace_back(0, 2, 5);

   indices.emplace_back(1, 0, 5);
   indices.emplace_back(1, 5, 4);
   indices.emplace_back(6, 2, 3);
   indices.emplace_back(6, 7, 2);
}