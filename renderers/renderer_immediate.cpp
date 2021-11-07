/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer_immediate.h"
#include "mesh.h"
#include "_aux.h"

void RendererImmediate::render(Mesh3D& m) const {
    glEnable(GL_CULL_FACE);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-25.0, 12.5);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    for (const auto& r : m.get_raw_data_list()) {
        glPolygonMode(GL_FRONT_AND_BACK, r.get_polygon_mode());
        glVertexPointer(3, GL_FLOAT, 0, r.get_vertices_data().data());
        glColorPointer(3, GL_FLOAT, 0, r.get_color_data().data());
        glDrawElements(GL_TRIANGLES, r.get_indices_count(), GL_UNSIGNED_INT, r.get_indices_data().data() + r.get_indices_offset()/3);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_CULL_FACE);
}