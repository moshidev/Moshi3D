#include "directional_light.h"

DirectionalLight::DirectionalLight(const Tupla2f& orientation)
:Light{Tupla4f{0,0,1,0}}, alpha{orientation(0)}, beta{orientation(1)}
{    }

DirectionalLight::DirectionalLight(const Tupla2f& orientation, Tupla4f color_ambient, Tupla4f color_diffuse, Tupla4f color_specular)
:Light{Tupla4f{0,0,1,0}, color_ambient, color_diffuse, color_specular}, alpha{orientation(0)}, beta{orientation(1)}
{    }