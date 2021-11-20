/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer_immediate.h"
#include "light.h"
#include "mesh.h"
#include "_aux.h"

static void update_lighting_status(bool lighting_enabled, bool affected_by_light) {
    bool currently_enabled = Light::is_lighting_enabled();
    if (currently_enabled && !affected_by_light) {
        Light::enable_lighting(false);
    }
    else if (lighting_enabled && !currently_enabled) {
        Light::enable_lighting(true);
    }
}

void RendererImmediate::render(Mesh3D& m) const {
    glEnable(GL_CULL_FACE);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-25.0, 12.5);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    bool lighting_enabled = Light::is_lighting_enabled();
    for (const auto& r : m.get_raw_data_list()) {
        update_lighting_status(lighting_enabled, r.get_affected_by_light());
        glPolygonMode(GL_FRONT_AND_BACK, r.get_polygon_mode());

        glVertexPointer(3, GL_FLOAT, 0, r.get_vertices_data().data());
        if (Light::is_lighting_enabled()) {
            glNormalPointer(GL_FLOAT, 0, r.get_vertices_normals_data().data());
            r.get_material().set_current();
        }
        else {
            glColorPointer(3, GL_FLOAT, 0, r.get_color_data().data());
        }
        
        glDrawElements(GL_TRIANGLES, r.get_indices_count(), GL_UNSIGNED_INT, r.get_indices_data().data() + r.get_indices_offset()/3);
        update_lighting_status(lighting_enabled, r.get_affected_by_light());
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_CULL_FACE);
}