/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer.h"
#include "mesh.h"
#include "_aux.h"
#include <iostream>

Mesh3D::Mesh3D()
:material{&Material::get_default()}
{}

Mesh3D::~Mesh3D() {}

void Mesh3D::draw(const Renderer& r) {
    r.render(*this);
}

void Mesh3D::clear_polygon_modes(void) {
    polygon_modes.clear();
    make_current_data_lists();
}

void Mesh3D::enable_polygon_modes(int mode) {
    if (mode == GL_FILL) {
        chess_enabled = false;
        shaded_enabled = false;
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
        shaded_enabled = false;
    }
    chess_enabled = b;
    make_current_data_lists();
}

void Mesh3D::enable_shaded_mode(bool b) {
    if (b) {
        polygon_modes.erase(GL_FILL);
        chess_enabled = false;
    }
    shaded_enabled = b;
    make_current_data_lists();
}

void Mesh3D::make_current_data_lists(void) {
    make_current_buffered_data_list();
    make_current_raw_data_list();
}

void Mesh3D::make_current_buffered_data_list(void) {
    auto& list = current_buffered_data_list;
    std::vector<std::list<Mesh3D::BufferedData>> render_lists {
        mklist_buffered_polygon_mode(get_indices_IB()),
        mklist_buffered_chess_mode(get_indices_IB()),
        mklist_buffered_shaded_mode(get_indices_IB(), *material)
    };
    
    list.clear();
    for (auto& l : render_lists) {
        list.splice(list.begin(), l);
    }
}

void Mesh3D::make_current_raw_data_list(void) {
    auto& list = current_raw_data_list;
    std::vector<std::list<Mesh3D::RawData>> render_lists {
        mklist_raw_polygon_mode(indices),
        mklist_raw_chess_mode(indices),
        mklist_raw_shaded_mode(indices, *material)
    };

    list.clear();
    for (auto& l : render_lists) {
        list.splice(list.begin(), l);
    }
}

std::list<Mesh3D::BufferedData> Mesh3D::mklist_buffered_polygon_mode(IndexBuffer& ib) {
    const Material& m = Material::get_default();
    std::list<Mesh3D::BufferedData> list;
    for (const auto& mode : polygon_modes) {
        switch (mode)
        {
        case GL_FILL:
            list.emplace_back(get_vertices_VB(), ib, get_color_fill_VB(), get_vertices_normal_VB(), m, GL_FILL);
            break;
        case GL_LINE:
            list.emplace_back(get_vertices_VB(), ib, get_color_line_VB(), get_vertices_normal_VB(), m, GL_LINE);
            break;
        case GL_POINT:
            list.emplace_back(get_vertices_VB(), ib, get_color_point_VB(), get_vertices_normal_VB(), m, GL_POINT);
        }

        list.back().set_affected_by_light(false);
    }
    return list;
}

std::list<Mesh3D::BufferedData> Mesh3D::mklist_buffered_chess_mode(IndexBuffer& ib) {
    const Material& m = Material::get_default();
    std::list<Mesh3D::BufferedData> list;
    if (chess_enabled) {
        init_vertex_buffer(color_chess_a_VB, color_chess_a);
        init_vertex_buffer(color_chess_b_VB, color_chess_b);
        int mid = ib.get_num_indices()/2;
        const int& count = mid;

        list.emplace_back(get_vertices_VB(), ib, color_chess_a_VB, get_vertices_normal_VB(), m, GL_FILL);
        list.back().set_face_indices_offset(0, count);
        list.back().set_affected_by_light(false);

        list.emplace_back(get_vertices_VB(), ib, color_chess_b_VB, get_vertices_normal_VB(), m, GL_FILL);
        list.back().set_face_indices_offset(mid, count);
        list.back().set_affected_by_light(false);
    }

    return list;
}

std::list<Mesh3D::BufferedData> Mesh3D::mklist_buffered_shaded_mode(IndexBuffer& ib, const Material& m) {
    std::list<Mesh3D::BufferedData> list;
    if (shaded_enabled) {
        list.emplace_back(get_vertices_VB(), ib, get_color_fill_VB(), get_vertices_normal_VB(), m, GL_FILL);
    }
    return list;
}

std::list<Mesh3D::RawData> Mesh3D::mklist_raw_polygon_mode(const std::vector<Tupla3u>& i) {
    const Material& m = Material::get_default();
    std::list<Mesh3D::RawData> l;
    for (const auto& mode : polygon_modes) {
        switch (mode)
        {
        case GL_FILL:
            l.emplace_back(vertices, i, color_fill, vertices_normal, m, GL_FILL);
            break;
        case GL_LINE:
            l.emplace_back(vertices, i, color_line, vertices_normal, m, GL_LINE);
            break;
        case GL_POINT:
            l.emplace_back(vertices, i, color_point, vertices_normal, m, GL_POINT);
        }

        l.back().set_affected_by_light(false);
    }
    return l;
}

std::list<Mesh3D::RawData> Mesh3D::mklist_raw_chess_mode(const std::vector<Tupla3u>& i) {
    const Material& m = Material::get_default();
    std::list<Mesh3D::RawData> l;
    if (chess_enabled) {
        int mid = i.size()*3/2;
        const int& count = mid;
        l.emplace_back(vertices, i, color_chess_a, vertices_normal, m, GL_FILL);
        l.back().set_face_indices_offset(0, mid);
        l.back().set_affected_by_light(false);

        l.emplace_back(vertices, i, color_chess_b, vertices_normal, m, GL_FILL);
        l.back().set_face_indices_offset(mid, count);
        l.back().set_affected_by_light(false);
    }
    return l;
}

std::list<Mesh3D::RawData> Mesh3D::mklist_raw_shaded_mode(const std::vector<Tupla3u>& i, const Material& m) {
    std::list<Mesh3D::RawData> l;
    if (shaded_enabled) {
        l.emplace_back(vertices, i, color_fill, vertices_normal, m, GL_FILL);
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

void Mesh3D::compute_normal_faces(std::vector<Tupla3f>& indices_normal, const std::vector<Tupla3u>& indices) {
    indices_normal.clear();
    for (auto& f : indices) {
        Tupla3f a = vertices[f(1)] - vertices[f(0)];
        Tupla3f b = vertices[f(2)] - vertices[f(0)];
        indices_normal.emplace_back(a.cross(b).normalized());
    }
}

void Mesh3D::sum_normal_to_vertices(const std::vector<Tupla3f>& indices_normal, const std::vector<Tupla3u>& indices) {
    vertices_normal.resize(vertices.size(), {0,0,0});
    int i = 0;
    for (auto& f : indices) {
        vertices_normal[f(0)] = vertices_normal[f(0)] + indices_normal[i];
        vertices_normal[f(1)] = vertices_normal[f(1)] + indices_normal[i];
        vertices_normal[f(2)] = vertices_normal[f(2)] + indices_normal[i];
        i++;
    }
}

void Mesh3D::normalize_vertices(void) {
    for (auto& v : vertices_normal) {
        v = v.normalized();
    }
}

void Mesh3D::init_normal_vectors(void) {
    std::vector<Tupla3f> indices_normal;
    compute_normal_faces(indices_normal, indices);
    sum_normal_to_vertices(indices_normal, indices);
    normalize_vertices();  
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

VertexBuffer& Mesh3D::get_vertices_normal_VB(void) {
    init_vertex_buffer(vertices_normal_VB, vertices_normal);
    return vertices_normal_VB;
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