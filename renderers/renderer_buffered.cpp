/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer_buffered.h"
#include "mesh.h"
#include "light.h"
#include "_aux.h"

static void set_vertex_pointer(const VertexBuffer<Tupla3f>& vb) {
    vb.bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);
    vb.unbind();
}

static void set_color_pointer(const VertexBuffer<Tupla3f>& vb) {
    vb.bind();
    glColorPointer(3, GL_FLOAT, 0, 0);
    vb.unbind();
}

static void set_normal_pointer(const VertexBuffer<Tupla3f>& vb) {
    vb.bind();
    glNormalPointer(GL_FLOAT, 0, 0);
    vb.unbind();
}

static void set_texture_coordinates(const VertexBuffer<Tupla2f>& vb) {
    vb.bind();
    glTexCoordPointer(2, GL_FLOAT, 0, 0);
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
    glEnableClientState(GL_NORMAL_ARRAY);
    
    bool lighting_enabled = Light::is_lighting_enabled();
    for (const auto& d : m.get_data_list()) {
        update_lighting_status(lighting_enabled, d.affected_by_light);
        glPolygonMode(GL_FRONT, d.polygon_mode);

        set_vertex_pointer(d.vertices);
        set_normal_pointer(d.vertices_normals);
        if (d.color) {
            glEnableClientState(GL_COLOR_ARRAY);
            set_color_pointer(*d.color);
        }
        if (d.material) {
            d.material->set_current();
        }
        if (d.texture) {
            glEnable(GL_TEXTURE_2D);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            set_texture_coordinates(d.texture->texture_coordinates);
            d.texture->texture->bind();
        }
        
        draw_elements_from_indices(d.face_indices, d.indices_count, d.indices_offset);
        update_lighting_status(lighting_enabled, d.affected_by_light);

        glDisable(GL_TEXTURE_2D);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_CULL_FACE);
}