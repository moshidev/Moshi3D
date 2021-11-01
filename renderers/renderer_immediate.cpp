/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer_immediate.h"
#include "mesh.h"
#include "_aux.h"

static void set_color_pointer(Mesh3D& m, int mode) {
    const GLvoid* colorvb {nullptr};
    switch (mode)
    {
    case GL_FILL:
        colorvb = m.get_color_solid_data();
        break;  
    case GL_LINE:
        colorvb = m.get_color_line_data();
        break;
    case GL_POINT:
        colorvb = m.get_color_point_data();
        break;
    }

    if (colorvb) {
        glColorPointer(3, GL_FLOAT, 0, colorvb);
    }
}

void RendererImmediate::render(Mesh3D& m) const {
    const std::set<int>& polygon_modes = m.get_polygon_modes();
    
    glEnable(GL_CULL_FACE);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-25.0, 12.5);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, m.get_vertices_data());

    for (auto& mode : polygon_modes) {
        set_color_pointer(m, mode);
        glPolygonMode(GL_FRONT_AND_BACK, mode);
        glDrawElements(GL_TRIANGLES, m.get_indices_count(), GL_UNSIGNED_INT, m.get_indices_data());
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_CULL_FACE);
}