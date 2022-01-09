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

void RendererImmediate::render(const Mesh3D& m) {
    glEnable(GL_CULL_FACE);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-25.0, 12.5);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    bool lighting_enabled = Light::is_lighting_enabled();
    for (const auto& r : m.get_data_list()) {
        update_lighting_status(lighting_enabled, r.affected_by_light);
        glPolygonMode(GL_FRONT_AND_BACK, r.polygon_mode);

        glVertexPointer(3, GL_FLOAT, 0, r.vertices.data.data());
        glNormalPointer(GL_FLOAT, 0, r.vertices_normals.data.data());

        if (r.color) {
            glColorPointer(3, GL_FLOAT, 0, r.color->data.data());
        }
        if (r.material) {
            r.material->set_current();
        }
        if (r.texture) {
            glEnable(GL_TEXTURE_2D);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_FLOAT, 0, r.texture->texture_coordinates.data.data());
            r.texture->texture->bind();
        }
        
        glDrawElements(GL_TRIANGLES, r.indices_count, GL_UNSIGNED_INT, r.face_indices.data.data() + r.indices_offset/3);
        update_lighting_status(lighting_enabled, r.affected_by_light);

        glDisable(GL_TEXTURE_2D);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_CULL_FACE);
}