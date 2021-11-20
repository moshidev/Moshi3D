/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_DIRECTIONAL_LIGHT_H_
#define MOSHI3D_DIRECTIONAL_LIGHT_H_

#include "light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight() = delete;
    DirectionalLight(const DirectionalLight& l) = delete;
    DirectionalLight(const Tupla2f& orientation);
    DirectionalLight(const Tupla2f& orientation, Tupla4f color_ambient, Tupla4f color_diffuse, Tupla4f color_specular);

    void increment_alpha(float value);
    void increment_beta(float value);

protected:
    float alpha;
    float beta;

    void set_position(float alpha, float beta);
};

#endif /* MOSHI3D_DIRECTIONAL_LIGHT_H_ */