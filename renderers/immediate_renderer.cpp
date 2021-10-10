#include "immediate_renderer.h"
#include "malla.h"
#include "_aux.h"

void ImmediateRenderer::render(Malla3D& m) const {
    const GLvoid* vertices_data = m.get_vertices_data();
    const GLvoid* indices_data = m.get_indices_data();
    const GLsizei indices_size = m.get_indices_size();
    glEnable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices_data);
    glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, indices_data);
    glDisableClientState(GL_VERTEX_ARRAY);
}