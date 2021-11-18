#include "positional_light.h"

PositionalLight::PositionalLight(const Tupla3f& position)
:Light{Tupla4f{position(0), position(1), position(2), 1}}
{   }

PositionalLight::PositionalLight(const Tupla3f& position, Tupla4f color_ambient, Tupla4f color_diffuse, Tupla4f color_specular)
:Light{Tupla4f{position(0), position(1), position(2), 1}, color_ambient, color_diffuse, color_specular}
{   }