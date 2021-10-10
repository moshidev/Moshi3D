/**
 * Daniel Pedrosa Montes © <pedrosam.sh@gmail.com>
 * MIT License.
 */

#ifndef MOSHI3D_IMMEDIATE_RENDERER_H_
#define MOSHI3D_IMMEDIATE_RENDERER_H_

#include "renderer.h"

class ImmediateRenderer : public Renderer {
    public:
    void render(const Malla3D& m) const;
};

#endif /* MOSHI3D_IMMEDIATE_RENDERER_H_ */