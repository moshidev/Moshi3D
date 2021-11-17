/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_INDEX_BUFFER_H_
#define MOSHI3D_INDEX_BUFFER_H_

#include "_aux.h"

/**
 * @warning should not be destroyed after GLU shuts down the OpenGL instance
 */
class IndexBuffer {
    GLuint id {0};
    unsigned int index_count {0};

public:
    IndexBuffer(bool gen_buffer=false);
    IndexBuffer(GLsizei count, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
    ~IndexBuffer();

    inline bool usable(void) const { return id; };
    void bind(void) const;
    void unbind(void) const;
    void set_indices(GLsizei count, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
    inline unsigned get_num_indices(void) const { return index_count; }
};

#endif /* MOSHI3D_INDEX_BUFFER_H_ */