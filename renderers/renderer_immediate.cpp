/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer_immediate.h"
#include "malla.h"
#include "_aux.h"

void RendererImmediate::render(Malla3D& m) const {
    const std::set<int>& polygon_modes = m.get_polygon_modes();
    
    glEnable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, m.get_vertices_data());
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, m.get_color_data());

    for (auto& mode : polygon_modes) {
        glPolygonMode(GL_FRONT_AND_BACK, mode);
        glDrawElements(GL_TRIANGLES, m.get_indices_size(), GL_UNSIGNED_INT, m.get_indices_data());
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}