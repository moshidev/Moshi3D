#include "_aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   float offset = lado/2;
   
   v.push_back({offset, offset, offset});
   v.push_back({offset, offset, -offset});
   v.push_back({offset, -offset, offset});
   v.push_back({offset, -offset, -offset});
   v.push_back({-offset, offset, offset});
   v.push_back({-offset, offset, -offset});
   v.push_back({-offset, -offset, offset});
   v.push_back({-offset, -offset, -offset});

   f.push_back({0, 1, 2});
   f.push_back({0, 2, 6});
   f.push_back({0, 4, 5});
   f.push_back({0, 5, 1});
   f.push_back({0, 6, 4});
   f.push_back({1, 3, 2});
   f.push_back({1, 5, 7});
   f.push_back({1, 7, 3});
   f.push_back({2, 3, 6});
   f.push_back({3, 7, 6});
   f.push_back({4, 6, 7});
   f.push_back({4, 7, 5});
}

