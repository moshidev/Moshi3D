/**
 * Daniel Pedrosa Montes © <pedrosam.sh@gmail.com>
 * MIT License.
 */

#ifndef MOSHI3D_BUFFERED_RENDERER_H_
#define MOSHI3D_BUFFERED_RENDERER_H_

#include "renderer.h"

class BufferedRenderer : public Renderer {
    public:
    void render(Malla3D& m) const;
};

#endif /* MOSHI3D_BUFFERED_RENDERER_H_ */