/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer.h"
#include "mesh.h"
#include "_aux.h"

Mesh3D::Mesh3D()
:material{Material::get_default()}
{}

Mesh3D::~Mesh3D() {}

void Mesh3D::draw(const Renderer& r) const {
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

template<typename _T>
void Mesh3D::init_vertex_buffer(VertexBuffer<_T>& vb) {
    if (!vb.usable()) {
        vb.set_vb_data();
    }
}

void Mesh3D::init_index_buffer(IndexBuffer& ib) {
    if (!ib.usable()) {
        ib.set_ib_data();
    }
}

void Mesh3D::make_current_data_lists(void) {
    init_vertex_buffer<Tupla3f>(vertices);
    init_vertex_buffer<Tupla3f>(vertices_normal);
    init_vertex_buffer<Tupla3f>(color_fill);
    init_vertex_buffer<Tupla3f>(color_line);
    init_vertex_buffer<Tupla3f>(color_point);
    init_vertex_buffer<Tupla3f>(color_chess_a);
    init_vertex_buffer<Tupla3f>(color_chess_b);
    init_index_buffer(indices);
    make_current_data_list();
}

void Mesh3D::make_current_data_list(void) {
    auto& cl = current_data_list;
    cl.clear();
    cl.splice(cl.begin(), mklist_polygon_mode(indices));
    cl.splice(cl.begin(), mklist_chess_mode(indices));
    cl.splice(cl.begin(), mklist_shaded_mode(indices, material));
}

std::list<Mesh3D::Data> Mesh3D::mklist_polygon_mode(IndexBuffer& ib) {
    std::list<Mesh3D::Data> list;
    for (const auto& mode : polygon_modes) {
        switch (mode)
        {
        case GL_FILL:
            list.emplace_back(vertices, vertices_normal, ib, GL_FILL, color_fill);
            break;
        case GL_LINE:
            list.emplace_back(vertices, vertices_normal, ib, GL_LINE, color_line);
            break;
        case GL_POINT:
            list.emplace_back(vertices, vertices_normal, ib, GL_POINT, color_point);
        }
    }
    return list;
}

std::list<Mesh3D::Data> Mesh3D::mklist_chess_mode(IndexBuffer& ib) {
    std::list<Mesh3D::Data> list;
     if (chess_enabled) {
        int mid = ib.data.size()*3/2;
        const int& count = mid;
        list.emplace_back(vertices, vertices_normal, ib, GL_FILL, color_chess_a);
        list.back().set_face_indices_offset(0, mid);

        list.emplace_back(vertices, vertices_normal, ib, GL_FILL, color_chess_b);
        list.back().set_face_indices_offset(mid, count);
    }
    return list;
}

std::list<Mesh3D::Data> Mesh3D::mklist_shaded_mode(IndexBuffer& ib, const Material& m) {
    std::list<Mesh3D::Data> list;
    if (shaded_enabled) {
        list.emplace_back(vertices, vertices_normal, ib, GL_FILL, m);
        if (texture) {
            init_vertex_buffer<Tupla2f>(texture->texture_coordinates);
            list.back().set_texture(*texture);
        }
    }
    return list;
}

void Mesh3D::init_normal_vectors(void) {
    std::vector<Tupla3f> indices_normal;
    compute_normal_faces(indices_normal, indices.data);
    sum_normal_faces_to_vertices_normals(indices_normal, indices.data);
    normalize_vertices_normals();  
}

void Mesh3D::init_color(unsigned n_vertices) {
    color_fill.data.assign(n_vertices, {0.25, 0.5, 0.75});
    color_line.data.assign(n_vertices, {1.0, 0.0, 0.0});
    color_point.data.assign(n_vertices, {0.0, 1.0, 0.0});
    color_chess_a.data.assign(n_vertices, {0.75, 0.25, 0.0});
    color_chess_b.data.assign(n_vertices, {0.25, 0.75, 0.0});
}

void Mesh3D::compute_normal_faces(std::vector<Tupla3f>& indices_normal, const std::vector<Tupla3u>& indices) {
    indices_normal.clear();
    for (auto& f : indices) {
        Tupla3f a = vertices.data[f(1)] - vertices.data[f(0)];
        Tupla3f b = vertices.data[f(2)] - vertices.data[f(0)];
        indices_normal.emplace_back(a.cross(b).normalized());
    }
}

void Mesh3D::sum_normal_faces_to_vertices_normals(const std::vector<Tupla3f>& indices_normal, const std::vector<Tupla3u>& indices) {
    vertices_normal.data.resize(vertices.data.size(), {0,0,0});
    int i = 0;
    for (auto& f : indices) {
        vertices_normal.data[f(0)] = vertices_normal.data[f(0)] + indices_normal[i];
        vertices_normal.data[f(1)] = vertices_normal.data[f(1)] + indices_normal[i];
        vertices_normal.data[f(2)] = vertices_normal.data[f(2)] + indices_normal[i];
        i++;
    }
}

void Mesh3D::normalize_vertices_normals(void) {
    for (auto& v : vertices_normal.data) {
        v = v.normalized();
    }
}