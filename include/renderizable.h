/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_RENDERIZABLE_H_
#define MOSHI3D_RENDERIZABLE_H_

class Renderer;

class Renderizable {
public:
    virtual ~Renderizable() = 0;
    virtual void draw(Renderer& r) const = 0;
};

#endif /* MOSHI3D_RENDERIZABLE_H_ */