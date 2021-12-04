#include "directional_light.h"

DirectionalLight::DirectionalLight(const Tupla2f& orientation)
:Light{Tupla4f{0,0,1,0}}, alpha{orientation(0)}, beta{orientation(1)}
{
    set_position(alpha, beta);
}

DirectionalLight::DirectionalLight(const Tupla2f& orientation, Tupla4f color_ambient, Tupla4f color_diffuse, Tupla4f color_specular)
:Light{Tupla4f{0,0,1,0}, color_ambient, color_diffuse, color_specular}, alpha{orientation(0)}, beta{orientation(1)}
{
    set_position(alpha, beta);
}

void DirectionalLight::increment_alpha(float value) {
    alpha += value;
    set_position(alpha, beta);
}

void DirectionalLight::increment_beta(float value) {
    beta += value;
    set_position(alpha, beta);
}

void DirectionalLight::set_position(float alpha, float beta) {
    const float x_hip = sin(alpha);
    position[1] = cos(alpha);
    position[0] = x_hip * sin(beta);
    position[2] = x_hip * cos(beta);
}