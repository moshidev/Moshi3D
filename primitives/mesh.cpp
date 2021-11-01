/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#include "renderer.h"
#include "mesh.h"
#include "_aux.h"
#include <iostream>

Mesh3D::Mesh3D() {
    enable_polygon_modes(GL_FILL);
}

Mesh3D::~Mesh3D() {
    if (vertices_VBO) {
        delete vertices_VBO;
    }
    if (color_solid_VBO) {
        delete color_solid_VBO;
    }
    if (color_line_VBO) {
        delete color_line_VBO;
    }
    if (color_point_VBO) {
        delete color_point_VBO;
    }
    if (indices_VBO) {
        delete indices_VBO;
    }
}

void Mesh3D::init_color(unsigned n_vertices) {
    color_solid.assign(n_vertices, {0.25, 0.5, 0.75});
    color_line.assign(n_vertices, {1.0, 0.0, 0.0});
    color_point.assign(n_vertices, {0.0, 1.0, 0.0});
}

void Mesh3D::draw(const Renderer& r) {
    r.render(*this);
}

const VertexBuffer& Mesh3D::get_vertices_VBO(void) {
    if (vertices_VBO == nullptr) {
        vertices_VBO = new VertexBuffer(sizeof(Tupla3f)*vertices.size(), vertices.data());
    }
    return *vertices_VBO;
}

const VertexBuffer& Mesh3D::get_color_solid_VBO(void) {
    if (color_solid_VBO == nullptr) {
        color_solid_VBO = new VertexBuffer(sizeof(Tupla3f)*color_solid.size(), color_solid.data());
    }
    return *color_solid_VBO;
}

const VertexBuffer& Mesh3D::get_color_line_VBO(void) {
    if (color_line_VBO == nullptr) {
        color_line_VBO = new VertexBuffer(sizeof(Tupla3f)*color_line.size(), color_line.data());
    }
    return *color_line_VBO;
}

const VertexBuffer& Mesh3D::get_color_point_VBO(void) {
    if (color_point_VBO == nullptr) {
        color_point_VBO = new VertexBuffer(sizeof(Tupla3f)*color_point.size(), color_point.data());
    }
    return *color_point_VBO;
}

const IndexBuffer& Mesh3D::get_indices_VBO(void) {
    if (indices_VBO == nullptr) {
        indices_VBO = new IndexBuffer(3*indices.size(), indices.data());
    }
    return *indices_VBO;
}