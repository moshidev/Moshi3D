/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_BUFFERED_RENDERER_H_
#define MOSHI3D_BUFFERED_RENDERER_H_

#include "renderer.h"

class RendererBuffered : public Renderer {
    public:
    void render(Mesh3D& m) const;
};

#endif /* MOSHI3D_BUFFERED_RENDERER_H_ */