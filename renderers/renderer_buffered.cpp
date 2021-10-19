/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer_buffered.h"
#include "malla.h"
#include "_aux.h"

void set_vertex_pointer(GLuint vertices_vbo_id) {
    glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo_id);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void set_color_pointer(GLuint color_vbo_id) {
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo_id);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void draw_elements_from_indices(GLuint indices_vbo_id, GLsizei count) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void RendererBuffered::render(Malla3D& m) const {
    GLuint vertices_VBO_id = m.get_vertices_VBO_id();
    GLuint indices_VBO_id = m.get_indices_VBO_id();
    GLuint color_VBO_id = m.get_color_VBO_id();
    GLsizei indices_size = m.get_indices_size();
    glEnable(GL_CULL_FACE);
    set_vertex_pointer(vertices_VBO_id);
    set_color_pointer(color_VBO_id);
    draw_elements_from_indices(indices_VBO_id, indices_size);
}