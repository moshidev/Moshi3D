/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_RENDERIZABLE_H_
#define MOSHI3D_RENDERIZABLE_H_

#include "transformation.h"

class Renderer;

class Renderizable {
public:
    virtual void draw(const Renderer& r, float time_point=0) const = 0;
};

#endif /* MOSHI3D_RENDERIZABLE_H_ */