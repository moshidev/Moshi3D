/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_VERTEX_BUFFER_H_
#define MOSHI3D_VERTEX_BUFFER_H_

#include "_aux.h"

/**
 * @warning should not be destroyed after GLU shuts down the OpenGL instance
 */
class VertexBuffer {
    GLuint id;

public:
    VertexBuffer();
    VertexBuffer(GLsizeiptr size, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
    ~VertexBuffer();

    void bind(void);
    void unbind(void);
    void set_data(GLsizeiptr size, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
};

#endif /* MOSHI3D_VERTEX_BUFFER_H_ */