#include "renderer_selector.h"
#include "vertex_buffer.hpp"
#include "index_buffer.h"
#include "mesh.h"
#include "light.h"
#include "_aux.h"

static void set_vertex_pointer(const VertexBuffer<Tupla3f>& vb) {
    vb.bind();
    glVertexPointer(3, GL_FLOAT, 0, 0);
    vb.unbind();
}

static void draw_elements_from_indices(const IndexBuffer& ib, GLsizei count, GLsizei offset=0) {
    ib.bind();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset*sizeof(unsigned int)));
    ib.unbind();
}

RendererSelector::RendererSelector(const Tupla3u& color_ini)
:color{color_ini}
{   }

void RendererSelector::render(const Mesh3D& m) {
    bool lights_enabled = Light::is_lighting_enabled();
    Light::enable_lighting(false);
    
    glDisable(GL_DITHER);
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glEnable(GL_CULL_FACE);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-25.0, 12.5);
    glEnableClientState(GL_VERTEX_ARRAY);

    for (const auto& d : m.get_data_list()) {
        glPolygonMode(GL_FRONT, d.polygon_mode);

        set_vertex_pointer(d.vertices);
        glColor3ub(color[0], color[1], color[2]);
        
        draw_elements_from_indices(d.face_indices, d.indices_count, d.indices_offset);
    }

    Light::enable_lighting(lights_enabled);
}
