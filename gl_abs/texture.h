/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_TEXTURE_H_
#define MOSHI3D_TEXTURE_H_

#include "_aux.h"
#include <memory>
#include <string>

/**
 * @warning should not be destroyed after GLU shuts down the OpenGL instance
 */
class Texture {
    GLuint id {0};
    std::unique_ptr<unsigned char[]> data;
    unsigned int width {0};
    unsigned int height {0};

    static GLuint gen_texture_id(const std::unique_ptr<unsigned char[]>& data, unsigned int width, unsigned int height);
    std::unique_ptr<unsigned char[]> init_data_from_image(const std::string& texture_name, unsigned int& width, unsigned int& height);

public:
    Texture(const std::string& texture_name);
    ~Texture();

    void bind(void);
    void unbind(void) const;
};

#endif /* MOSHI3D_TEXTURE_H_ */