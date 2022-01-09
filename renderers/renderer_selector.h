/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_SELECTOR_RENDERER_H_
#define MOSHI3D_SELECTOR_RENDERER_H_

#include "tuplasg.h"
#include "renderer.h"

class RendererSelector : public Renderer {
    Tupla3u color;
public:
    RendererSelector(const Tupla3u& color_ini);
    void render(const Mesh3D& m);
};

#endif /* MOSHI3D_SELECTOR_RENDERER_H_ */