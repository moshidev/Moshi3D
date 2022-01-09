/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_IMMEDIATE_RENDERER_H_
#define MOSHI3D_IMMEDIATE_RENDERER_H_

#include "renderer.h"

class RendererImmediate : public Renderer {
    public:
    void render(const Mesh3D& m);
};

#endif /* MOSHI3D_IMMEDIATE_RENDERER_H_ */