/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer_buffered.h"
#include "mesh.h"
#include "_aux.h"

static void set_vertex_pointer(const VertexBuffer& vb) {
    vb.bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);
    vb.unbind();
}

static void set_color_pointer(const VertexBuffer& vb) {
    vb.bind();
    glColorPointer(3, GL_FLOAT, 0, 0);
    vb.unbind();
}

static void draw_elements_from_indices(const IndexBuffer& ib, GLsizei count, GLsizei offset=0) {
    ib.bind();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset*sizeof(unsigned int)));
    ib.unbind();
}

void RendererBuffered::render(Mesh3D& m) const {
    glEnable(GL_CULL_FACE);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-25.0, 12.5);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    for (const auto& r : m.get_buffer_data_list()) {
        glPolygonMode(GL_FRONT_AND_BACK, r.get_polygon_mode());
        set_vertex_pointer(r.get_vertices());
        set_color_pointer(r.get_color());
        draw_elements_from_indices(r.get_indices(), r.get_indices_count(), r.get_indices_offset());
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_CULL_FACE);
}