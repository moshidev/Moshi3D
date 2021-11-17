/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(bool gen_buffer) {
    if (gen_buffer) {
        glGenBuffers(1, &id);
    }
}

VertexBuffer::VertexBuffer(GLsizeiptr size, const GLvoid* data, GLenum usage) {
    glGenBuffers(1, &id);
    set_data(size, data, usage);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id);
}

void VertexBuffer::bind(void) const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind(void) const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::set_data(GLsizeiptr size, const GLvoid* data, GLenum usage) {
    if (!id) {
        glGenBuffers(1, &id);
    }
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    unbind();
}