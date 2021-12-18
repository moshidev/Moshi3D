/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "vertex_buffer_object.h"

VertexBufferObject::VertexBufferObject(bool gen_buffer) {
    if (gen_buffer) {
        glGenBuffers(1, &id);
    }
}

VertexBufferObject::VertexBufferObject(GLsizeiptr size, const GLvoid* data, GLenum usage) {
    glGenBuffers(1, &id);
    set_data(size, data, usage);
}

VertexBufferObject::~VertexBufferObject() {
    glDeleteBuffers(1, &id);
}

void VertexBufferObject::bind(void) const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBufferObject::unbind(void) const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::set_data(GLsizeiptr size, const GLvoid* data, GLenum usage) {
    if (!id) {
        glGenBuffers(1, &id);
    }
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    unbind();
}