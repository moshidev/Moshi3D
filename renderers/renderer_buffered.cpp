/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer_buffered.h"
#include "mesh.h"
#include "light.h"
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

static void set_normal_pointer(const VertexBuffer& vb) {
    vb.bind();
    glNormalPointer(GL_FLOAT, 0, 0);
    vb.unbind();
}

static void draw_elements_from_indices(const IndexBuffer& ib, GLsizei count, GLsizei offset=0) {
    ib.bind();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset*sizeof(unsigned int)));
    ib.unbind();
}

static void update_lighting_status(bool lighting_enabled, bool affected_by_light) {
    bool currently_enabled = Light::is_lighting_enabled();
    if (currently_enabled && !affected_by_light) {
        Light::enable_lighting(false);
    }
    else if (lighting_enabled && !currently_enabled) {
        Light::enable_lighting(true);
    }
}

void RendererBuffered::render(const Mesh3D& m) const {
    glEnable(GL_CULL_FACE);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-25.0, 12.5);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    bool lighting_enabled = Light::is_lighting_enabled();
    for (const auto& r : m.get_buffer_data_list()) {
        update_lighting_status(lighting_enabled, r.get_affected_by_light());
        glPolygonMode(GL_FRONT, r.get_polygon_mode());

        set_vertex_pointer(r.get_vertices());
        if (Light::is_lighting_enabled()) {
            set_normal_pointer(r.get_vertices_normals());
            r.get_material().set_current();
        }
        else {
            set_color_pointer(r.get_color());
        }
        
        draw_elements_from_indices(r.get_indices(), r.get_indices_count(), r.get_indices_offset());
        update_lighting_status(lighting_enabled, r.get_affected_by_light());
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_CULL_FACE);
}