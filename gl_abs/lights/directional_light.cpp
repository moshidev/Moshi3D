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
    const float z_hip = cos(alpha);
    position[1] = sin(alpha);
    position[0] = z_hip * sin(beta);
    position[2] = z_hip * cos(beta);
}