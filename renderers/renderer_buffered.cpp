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

static void set_color_pointer(Mesh3D& m, int mode) {
    const VertexBuffer* colorvb {nullptr};
    switch (mode)
    {
    case GL_FILL:
        colorvb = &m.get_color_solid_VBO();
        break;  
    case GL_LINE:
        colorvb = &m.get_color_line_VBO();
        break;
    case GL_POINT:
        colorvb = &m.get_color_point_VBO();
        break;
    }

    if (colorvb) {
        colorvb->bind();
        glColorPointer(3, GL_FLOAT, 0, 0);
        colorvb->unbind();
    }
}

static void draw_elements_from_indices(const IndexBuffer& ib, GLsizei count, GLsizei offset=0) {
    ib.bind();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset*sizeof(unsigned int)));
    ib.unbind();
}

static void render_chess(Mesh3D& m) {
    const std::set<int>& polygon_modes = m.get_polygon_modes();

    glEnableClientState(GL_VERTEX_ARRAY);

    set_vertex_pointer(m.get_vertices_VBO());

    for (auto& mode : polygon_modes) {
        glPolygonMode(GL_FRONT_AND_BACK, mode);
        if (mode == GL_LINE || mode == GL_POINT) {
            glEnableClientState(GL_COLOR_ARRAY);
            set_color_pointer(m, mode);
            glDrawElements(GL_TRIANGLES, m.get_indices_count(), GL_UNSIGNED_INT, m.get_indices_data());
        }
        else {
            glDisableClientState(GL_COLOR_ARRAY);
            const auto& colors = m.get_chess_colors();
            GLsizei first_half = m.get_indices_count()/2;
            GLsizei second_half = m.get_indices_count() - first_half;
            glColor3fv((GLfloat*)&colors.first);
            draw_elements_from_indices(m.get_indices_VBO(), first_half, 0);
            glColor3fv((GLfloat*)&colors.second);
            draw_elements_from_indices(m.get_indices_VBO(), second_half, first_half);
        }
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

static void render_std(Mesh3D& m) {
    const std::set<int>& polygon_modes = m.get_polygon_modes();
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    set_vertex_pointer(m.get_vertices_VBO());

    for (auto& mode : polygon_modes) {
        set_color_pointer(m, mode);
        glPolygonMode(GL_FRONT_AND_BACK, mode);
        draw_elements_from_indices(m.get_indices_VBO(), m.get_indices_count());
    }

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void RendererBuffered::render(Mesh3D& m) const {
    glEnable(GL_CULL_FACE);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-25.0, 12.5);

    if (m.get_chess_enabled()) {
        render_chess(m);
    }
    else {
        render_std(m);
    }

    glDisable(GL_POLYGON_OFFSET_LINE);
    glDisable(GL_CULL_FACE);
}