/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_TEXTURE_OBJECT_H_
#define MOSHI3D_TEXTURE_OBJECT_H_

#include "_aux.h"
#include <memory>
#include <string>

/**
 * @warning should not be destroyed after GLU shuts down the OpenGL instance
 */
class TextureObject {
    GLuint id {0};
    
    static GLuint gen_texture_id(const unsigned char* data, unsigned int width, unsigned int height);
    static std::unique_ptr<unsigned char[]> init_data_from_image(const std::string& texture_name, unsigned int& width, unsigned int& height);

public:
    TextureObject(const std::string& texture_fname);
    ~TextureObject();

    inline bool usable(void) const { return id; }
    void bind(void) const;
    void unbind(void) const;

    void set_texture(const std::string& texture_fname);
    void set_texture(const unsigned char* data, unsigned int width, unsigned int height);

    static inline void enable(bool t) { t ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D); }
    static inline bool is_enabled(void) { return glIsEnabled(GL_TEXTURE_2D); }
};

#endif /* MOSHI3D_TEXTURE_OBJECT_H_ */