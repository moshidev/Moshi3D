/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "index_buffer_object.h"

IndexBufferObject::IndexBufferObject(bool gen_buffer) {
    if (gen_buffer) {
        glGenBuffers(1, &id);
    }
}

IndexBufferObject::IndexBufferObject(GLsizei count, const GLvoid* data, GLenum usage) {
    glGenBuffers(1, &id);
    set_indices(count, data, usage);
}

IndexBufferObject::~IndexBufferObject() {
    glDeleteBuffers(1, &id);
}

void IndexBufferObject::bind(void) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBufferObject::unbind(void) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferObject::set_indices(GLsizei count, const GLvoid* data, GLenum usage) {
    if (!id) {
        glGenBuffers(1, &id);
    }
    bind();
    index_count = count;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, usage);
    unbind();
}