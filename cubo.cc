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
   vertices.emplace_back(offset, -offset, -offset);
   vertices.emplace_back(offset, -offset,  offset);
   vertices.emplace_back(offset,  offset, -offset);
   vertices.emplace_back(offset,  offset,  offset);

   indices.emplace_back(5, 1, 0);
   indices.emplace_back(4, 5, 0);
   indices.emplace_back(3, 2, 0);
   indices.emplace_back(1, 3, 0);
   indices.emplace_back(2, 4, 0);
   indices.emplace_back(7, 3, 1);
   indices.emplace_back(1, 5, 7);
   indices.emplace_back(7, 5, 6);
   indices.emplace_back(5, 4, 6);
   indices.emplace_back(4, 2, 6);
   indices.emplace_back(6, 2, 3);
   indices.emplace_back(3, 7, 6);
}

