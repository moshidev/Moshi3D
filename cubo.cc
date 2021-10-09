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

   triangles.emplace_back(5, 1, 0);
   triangles.emplace_back(4, 5, 0);
   triangles.emplace_back(3, 2, 0);
   triangles.emplace_back(1, 3, 0);
   triangles.emplace_back(2, 4, 0);
   triangles.emplace_back(7, 3, 1);
   triangles.emplace_back(1, 5, 7);
   triangles.emplace_back(7, 5, 6);
   triangles.emplace_back(5, 4, 6);
   triangles.emplace_back(4, 2, 6);
   triangles.emplace_back(6, 2, 3);
   triangles.emplace_back(3, 7, 6);
}

