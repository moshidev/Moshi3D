/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer_buffered.h"
#include "mesh.h"
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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RendererBuffered::render(Mesh3D& m) const {
    const std::set<int>& polygon_modes = m.get_polygon_modes();
    
    glEnable(GL_CULL_FACE);
    glShadeModel(m.get_color_shade_mode());
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    set_vertex_pointer(m.get_vertices_VBO_id());
    set_color_pointer(m.get_color_VBO_id());

    for (auto& mode : polygon_modes) {
        glPolygonMode(GL_FRONT_AND_BACK, mode);
        draw_elements_from_indices(m.get_indices_VBO_id(), m.get_indices_size());
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}