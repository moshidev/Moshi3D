/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "vertex_buffer.h"

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &id);
}

VertexBuffer::VertexBuffer(GLsizeiptr size, const GLvoid* data, GLenum usage) {
    glGenBuffers(1, &id);
    set_data(size, data, usage);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id);
}

void VertexBuffer::bind(void) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind(void) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::set_data(GLsizeiptr size, const GLvoid* data, GLenum usage) {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    unbind();
}