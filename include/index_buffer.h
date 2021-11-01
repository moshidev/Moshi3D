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
    GLuint id;
    unsigned int index_count;

public:
    IndexBuffer();
    IndexBuffer(GLsizei count, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
    ~IndexBuffer();

    void bind(void);
    void unbind(void);
    void set_indices(GLsizei count, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
};

#endif /* MOSHI3D_INDEX_BUFFER_H_ */