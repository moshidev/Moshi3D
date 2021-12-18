/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_VERTEX_BUFFER_OBJECT_H_
#define MOSHI3D_VERTEX_BUFFER_OBJECT_H_

#include "_aux.h"

/**
 * @warning should not be destroyed after GLU shuts down the OpenGL instance
 */
class VertexBufferObject {
    GLuint id {0};

public:
    VertexBufferObject(bool gen_buffer=false);
    VertexBufferObject(const VertexBufferObject& v) = delete;
    VertexBufferObject(GLsizeiptr size, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
    ~VertexBufferObject();

    inline bool usable(void) const { return id; };
    void bind(void) const;
    void unbind(void) const;
    void set_data(GLsizeiptr size, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
};

#endif /* MOSHI3D_VERTEX_BUFFER_OBJECT_H_ */