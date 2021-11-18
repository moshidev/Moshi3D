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

    inline void increment_alpha(float value) { alpha += value; }
    inline void increment_beta(float value) {beta += value; }

protected:
    float alpha;
    float beta;
};

#endif /* MOSHI3D_DIRECTIONAL_LIGHT_H_ */