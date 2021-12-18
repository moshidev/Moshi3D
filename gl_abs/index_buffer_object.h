/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_INDEX_BUFFER_OBJECT_H_
#define MOSHI3D_INDEX_BUFFER_OBJECT_H_

#include "_aux.h"

/**
 * @warning should not be destroyed after GLU shuts down the OpenGL instance
 */
class IndexBufferObject {
    GLuint id {0};
    unsigned int index_count {0};

public:
    IndexBufferObject(bool gen_buffer=false);
    IndexBufferObject(GLsizei count, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
    ~IndexBufferObject();

    inline bool usable(void) const { return id; };
    void bind(void) const;
    void unbind(void) const;
    void set_indices(GLsizei count, const GLvoid* data, GLenum usage=GL_STATIC_DRAW);
    inline unsigned get_num_indices(void) const { return index_count; }
};

#endif /* MOSHI3D_INDEX_BUFFER_OBJECT_H_ */