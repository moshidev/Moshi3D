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

   indices.emplace_back(0, 3, 2);
   indices.emplace_back(0, 1, 3);
   indices.emplace_back(1, 7, 3);
   indices.emplace_back(1, 5, 7);
   indices.emplace_back(5, 6, 7);
   indices.emplace_back(5, 4, 6);
   indices.emplace_back(4, 2, 6);
   indices.emplace_back(4, 0, 2);
   indices.emplace_back(0, 4, 1);
   indices.emplace_back(5, 1, 4);
   indices.emplace_back(3, 7, 2);
   indices.emplace_back(6, 2, 7);
   
}

