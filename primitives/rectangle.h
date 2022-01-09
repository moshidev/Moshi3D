/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_RECTANGLE_H_
#define MOSHI3D_RECTANGLE_H_

#include "tuplasg.h"
#include "mesh.h"

class Rectangle : public Mesh3D {
    VertexBuffer<Tupla2f> texture_coordinates;

public:
    Rectangle(const Tupla2f& dimensions);
    void set_texture(const std::shared_ptr<TextureObject>& texture);
};

#endif /* MOSHI3D_RECTANGLE_H_ */