/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer.h"
#include "mesh.h"
#include "_aux.h"
#include <iostream>

Mesh3D::Mesh3D() {}

Mesh3D::~Mesh3D() {
    if (vertices_VBO) {
        delete vertices_VBO;
    }
    if (color_fill_VBO) {
        delete color_fill_VBO;
    }
    if (color_line_VBO) {
        delete color_line_VBO;
    }
    if (color_point_VBO) {
        delete color_point_VBO;
    }
    if (color_chess_a_VBO) {
        delete color_chess_a_VBO;
    }
    if (color_chess_b_VBO) {
        delete color_chess_b_VBO;
    }
    if (indices_VBO) {
        delete indices_VBO;
    }
}

void Mesh3D::draw(const Renderer& r) {
    r.render(*this);
}

void Mesh3D::make_data_lists(void) {
    current_buffer_data_list.clear();

    VertexBuffer& v = get_vertices_VBO();
    IndexBuffer& i = get_indices_VBO();
    const auto& it = current_buffer_data_list.begin();

    if (chess_enabled) {
        current_buffer_data_list.splice(it, get_chess_buffer_list(v, i));
    }

    for (const auto& m : polygon_modes) {
        switch (m)
        {
        case GL_FILL:
            current_buffer_data_list.emplace_back(v, i, get_color_fill_VBO(), GL_FILL);
            break;
        case GL_LINE:
            current_buffer_data_list.emplace_back(v, i, get_color_line_VBO(), GL_LINE);
            break;
        case GL_POINT:
            current_buffer_data_list.emplace_back(v, i, get_color_point_VBO(), GL_POINT);
        }
    }
}

void Mesh3D::clear_polygon_modes(void) {
    polygon_modes.clear();
    make_data_lists();
}

void Mesh3D::enable_polygon_modes(int mode) {
    if (mode == GL_FILL && chess_enabled) {
        chess_enabled = false;
    }
    polygon_modes.insert(mode);
    make_data_lists();
}

void Mesh3D::disable_polygon_modes(int mode) {
    polygon_modes.erase(mode);
    make_data_lists();
}

void Mesh3D::enable_chess_mode(bool b) {
    if (b) {
        polygon_modes.erase(GL_FILL);
    }
    chess_enabled = b;
    make_data_lists();
}

void Mesh3D::init_color(unsigned n_vertices) {
    color_fill.assign(n_vertices, {0.25, 0.5, 0.75});
    color_line.assign(n_vertices, {1.0, 0.0, 0.0});
    color_point.assign(n_vertices, {0.0, 1.0, 0.0});
    color_chess_a.assign(n_vertices, {0.75, 0.25, 0.0});
    color_chess_b.assign(n_vertices, {0.25, 0.75, 0.0});
}

void Mesh3D::init_vertex_buffer(VertexBuffer*& vb, const std::vector<Tupla3f>& v) {
    if (!vb) {
        update_vertex_buffer(vb, v.size()*sizeof(Tupla3f), v.data());
    }
}

void Mesh3D::init_index_buffer(IndexBuffer*& ib, const std::vector<Tupla3u>& v) {
    if (!ib) {
        update_index_buffer(ib, v.size()*3, v.data());
    }
}

void Mesh3D::update_vertex_buffer(VertexBuffer*& vb, GLsizeiptr size, const GLvoid* data) {
    if (vb) {
        delete vb;
    }
    vb = new VertexBuffer(size, data);
}

void Mesh3D::update_index_buffer(IndexBuffer*& ib, GLsizei count, const GLvoid* data) {
    if (ib) {
        delete ib;
    }
    ib = new IndexBuffer(count, data);
}

VertexBuffer& Mesh3D::get_vertices_VBO(void) {
    init_vertex_buffer(vertices_VBO, vertices);
    return *vertices_VBO;
}

IndexBuffer& Mesh3D::get_indices_VBO(void) {
    init_index_buffer(indices_VBO, indices);
    return *indices_VBO;
}

VertexBuffer& Mesh3D::get_color_fill_VBO(void) {
    init_vertex_buffer(color_fill_VBO, color_fill);
    return *color_fill_VBO;
}

VertexBuffer& Mesh3D::get_color_line_VBO(void) {
    init_vertex_buffer(color_line_VBO, color_line);
    return *color_line_VBO;
}

VertexBuffer& Mesh3D::get_color_point_VBO(void) {
    init_vertex_buffer(color_point_VBO, color_point);
    return *color_point_VBO;
}

std::list<Mesh3D::BufferedData> Mesh3D::get_chess_buffer_list(VertexBuffer& vertices, IndexBuffer& indices) {
    init_vertex_buffer(color_chess_a_VBO, color_chess_a);
    init_vertex_buffer(color_chess_b_VBO, color_chess_b);

    std::list<Mesh3D::BufferedData> l;
    int mid = indices.get_num_indices()/2;
    const int& count = mid;

    l.emplace_back(vertices, indices, *color_chess_a_VBO, GL_FILL);
    l.back().set_face_indices_offset(0, count);

    l.emplace_back(vertices, indices, *color_chess_b_VBO, GL_FILL);
    l.back().set_face_indices_offset(mid, count);

    return l;
}

std::list<Mesh3D::RawData> Mesh3D::get_chess_raw_list(void) const {

}