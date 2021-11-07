/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_RENDERER_H_
#define MOSHI3D_RENDERER_H_

class Mesh3D;

class Renderer {
    public:
    virtual void render(Mesh3D& m) const = 0;
};

#endif /* MOSHI3D_RENDERER_H_ */