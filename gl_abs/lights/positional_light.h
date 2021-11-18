/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_POSITIONAL_LIGHT_H_
#define MOSHI3D_POSITIONAL_LIGHT_H_

#include "light.h"

class PositionalLight : public Light {
public:
    PositionalLight() = delete;
    PositionalLight(const PositionalLight& l) = delete;
    PositionalLight(const Tupla3f& position);
    PositionalLight(const Tupla3f& position, Tupla4f color_ambient, Tupla4f color_diffuse, Tupla4f color_specular);
};

#endif /* MOSHI3D_POSITIONAL_LIGHT_H_ */