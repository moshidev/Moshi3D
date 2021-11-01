/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "index_buffer.h"

IndexBuffer::IndexBuffer() {
    glGenBuffers(1, &id);
}

IndexBuffer::IndexBuffer(GLsizei count, const GLvoid* data, GLenum usage) {
    glGenBuffers(1, &id);
    set_indices(count, data, usage);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &id);
}

void IndexBuffer::bind(void) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind(void) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::set_indices(GLsizei count, const GLvoid* data, GLenum usage) {
    bind();
    index_count = count;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, usage);
    unbind();
}