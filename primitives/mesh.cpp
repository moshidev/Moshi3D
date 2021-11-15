/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer.h"
#include "mesh.h"
#include "_aux.h"
#include <iostream>

Mesh3D::Mesh3D() {}

Mesh3D::~Mesh3D() {}

void Mesh3D::draw(const Renderer& r) {
    r.render(*this);
}

void Mesh3D::clear_polygon_modes(void) {
    polygon_modes.clear();
    make_current_data_lists();
}

void Mesh3D::enable_polygon_modes(int mode) {
    if (mode == GL_FILL && chess_enabled) {
        chess_enabled = false;
    }
    polygon_modes.insert(mode);
    make_current_data_lists();
}

void Mesh3D::disable_polygon_modes(int mode) {
    polygon_modes.erase(mode);
    make_current_data_lists();
}

void Mesh3D::enable_chess_mode(bool b) {
    if (b) {
        polygon_modes.erase(GL_FILL);
    }
    chess_enabled = b;
    make_current_data_lists();
}

void Mesh3D::make_current_data_lists(void) {
    make_current_buffered_data_list();
    make_current_raw_data_list();
}

void Mesh3D::make_current_buffered_data_list(void) {
    auto& list = current_buffered_data_list;

    list.clear();
    if (mklist_buffered_polygon_mode(get_vertices_VB(), get_indices_IB()).size() > 0) {
        list.splice(list.begin(), mklist_buffered_polygon_mode(get_vertices_VB(), get_indices_IB()));
    }
    if (mklist_buffered_chess_mode(get_vertices_VB(), get_indices_IB()).size() > 0) {
        list.splice(list.begin(), mklist_buffered_chess_mode(get_vertices_VB(), get_indices_IB()));
    }
}

void Mesh3D::make_current_raw_data_list(void) {
    auto& list = current_raw_data_list;

    list.clear();
    if (mklist_raw_polygon_mode(vertices, indices).size() > 0) {
        list.splice(list.begin(), mklist_raw_polygon_mode(vertices, indices));
    }
    if (mklist_raw_chess_mode(vertices, indices).size() > 0) {
        list.splice(list.begin(), mklist_raw_chess_mode(vertices, indices));
    }
    
}

std::list<Mesh3D::BufferedData> Mesh3D::mklist_buffered_polygon_mode(VertexBuffer& vb, IndexBuffer& ib) {
    std::list<Mesh3D::BufferedData> list;
    for (const auto& m : polygon_modes) {
        switch (m)
        {
        case GL_FILL:
            list.emplace_back(vb, ib, get_color_fill_VB(), GL_FILL);
            break;
        case GL_LINE:
            list.emplace_back(vb, ib, get_color_line_VB(), GL_LINE);
            break;
        case GL_POINT:
            list.emplace_back(vb, ib, get_color_point_VB(), GL_POINT);
        }
    }
    return list;
}

std::list<Mesh3D::BufferedData> Mesh3D::mklist_buffered_chess_mode(VertexBuffer& vb, IndexBuffer& ib) {
    std::list<Mesh3D::BufferedData> list;
    if (chess_enabled) {
        init_vertex_buffer(color_chess_a_VB, color_chess_a);
        init_vertex_buffer(color_chess_b_VB, color_chess_b);
        int mid = ib.get_num_indices()/2;
        const int& count = mid;

        list.emplace_back(vb, ib, color_chess_a_VB, GL_FILL);
        list.back().set_face_indices_offset(0, count);
        list.emplace_back(vb, ib, color_chess_b_VB, GL_FILL);
        list.back().set_face_indices_offset(mid, count);
    }

    return list;
}

std::list<Mesh3D::RawData> Mesh3D::mklist_raw_polygon_mode(const std::vector<Tupla3f>& v, const std::vector<Tupla3u>& i) {
    std::list<Mesh3D::RawData> l;
    for (const auto& m : polygon_modes) {
        switch (m)
        {
        case GL_FILL:
            l.emplace_back(v, i, color_fill, GL_FILL);
            break;
        case GL_LINE:
            l.emplace_back(v, i, color_line, GL_LINE);
            break;
        case GL_POINT:
            l.emplace_back(v, i, color_point, GL_POINT);
        }
    }
    return l;
}

std::list<Mesh3D::RawData> Mesh3D::mklist_raw_chess_mode(const std::vector<Tupla3f>& v, const std::vector<Tupla3u>& i) {
    std::list<Mesh3D::RawData> l;
    if (chess_enabled) {
        int mid = i.size()*3/2;
        const int& count = mid;
        l.emplace_back(v, i, color_chess_a, GL_FILL);
        l.back().set_face_indices_offset(0, mid);
        l.emplace_back(v, i, color_chess_b, GL_FILL);
        l.back().set_face_indices_offset(mid, count);
    }
    return l;
}

void Mesh3D::init_color(unsigned n_vertices) {
    color_fill.assign(n_vertices, {0.25, 0.5, 0.75});
    color_line.assign(n_vertices, {1.0, 0.0, 0.0});
    color_point.assign(n_vertices, {0.0, 1.0, 0.0});
    color_chess_a.assign(n_vertices, {0.75, 0.25, 0.0});
    color_chess_b.assign(n_vertices, {0.25, 0.75, 0.0});
}

void Mesh3D::init_normals(void) {
    for (const auto& f : indices) {
        Tupla3f a = vertices[f[1]] - vertices[f[0]];
        Tupla3f b = vertices[f[2]] - vertices[f[0]];
        nf.emplace_back(a.cross(b).normalized());
    }
    nv.resize(vertices.size());
    for (const auto& f : indices) {
        nv[f[0]] = nv[f[0]] + nf[f[0]];
        nv[f[1]] = nv[f[1]] + nf[f[1]];
        nv[f[2]] = nv[f[2]] + nf[f[2]];
    }
    for (auto& v : nv) {
        v = v.normalized();
    }
}

void Mesh3D::init_vertex_buffer(VertexBuffer& vb, const std::vector<Tupla3f>& v) {
    if (!vb.usable()) {
        vb.set_data(v.size()*sizeof(Tupla3f), v.data());
    }
}

void Mesh3D::init_index_buffer(IndexBuffer& ib, const std::vector<Tupla3u>& v) {
    if (!ib.usable()) {
        ib.set_indices(v.size()*3, v.data());
    }
}

VertexBuffer& Mesh3D::get_vertices_VB(void) {
    init_vertex_buffer(vertices_VB, vertices);
    return vertices_VB;
}

IndexBuffer& Mesh3D::get_indices_IB(void) {
    init_index_buffer(indices_IB, indices);
    return indices_IB;
}

VertexBuffer& Mesh3D::get_color_fill_VB(void) {
    init_vertex_buffer(color_fill_VB, color_fill);
    return color_fill_VB;
}

VertexBuffer& Mesh3D::get_color_line_VB(void) {
    init_vertex_buffer(color_line_VB, color_line);
    return color_line_VB;
}

VertexBuffer& Mesh3D::get_color_point_VB(void) {
    init_vertex_buffer(color_point_VB, color_point);
    return color_point_VB;
}