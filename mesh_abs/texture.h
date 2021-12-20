/**
  * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
  * GPLv3 License.
  */

 #ifndef MOSHI3D_TEXTURE_H_
 #define MOSHI3D_TEXTURE_H_

#include "texture_object.h"
#include "vertex_buffer.hpp"
#include "tuplasg.h"
#include <vector>
#include <memory>

struct Texture {
    const std::shared_ptr<TextureObject> texture;
    VertexBuffer<Tupla2f>& texture_coordinates;
    Texture(const std::shared_ptr<TextureObject>& texture, VertexBuffer<Tupla2f>& texture_coordinates)
    : texture{texture}, texture_coordinates{texture_coordinates}
    {   }
};

#endif /* MOSHI3D_TEXTURE_H_ */