#include "_aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   const float offset = lado/2;

   vertices.reserve(8);
   triangles.reserve(12);
   
   vertices.emplace_back(-offset, -offset, -offset);
   vertices.emplace_back(-offset, -offset,  offset);
   vertices.emplace_back(-offset,  offset, -offset);
   vertices.emplace_back(-offset,  offset,  offset);
   vertices.emplace_back(offset, -offset, -offset);
   vertices.emplace_back(offset, -offset,  offset);
   vertices.emplace_back(offset,  offset, -offset);
   vertices.emplace_back(offset,  offset,  offset);

   triangles.emplace_back(0, 1, 5);
   triangles.emplace_back(0, 5, 4);
   triangles.emplace_back(0, 2, 3);
   triangles.emplace_back(0, 3, 1);
   triangles.emplace_back(0, 4, 2);
   triangles.emplace_back(1, 3, 7);
   triangles.emplace_back(1, 5, 7);
   triangles.emplace_back(6, 5, 7);
   triangles.emplace_back(6, 4, 5);
   triangles.emplace_back(6, 2, 4);
   triangles.emplace_back(6, 2, 3);
   triangles.emplace_back(6, 7, 3);
}

