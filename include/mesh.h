/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MESH3D_H_
#define MOSHI3D_MESH3D_H_

#include <set>
#include "_aux.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

class Renderer;

class Mesh3D {
  public:
    Mesh3D();
    virtual ~Mesh3D() = 0;

    virtual void draw(const Renderer& r);

    inline const GLvoid* get_vertices_data(void) const { return vertices.data(); }
    inline const GLvoid* get_color_solid_data(void) const { return color_solid.data(); }
    inline const GLvoid* get_color_line_data(void) const { return color_line.data(); }
    inline const GLvoid* get_color_point_data(void) const { return color_point.data(); }
    inline const GLvoid* get_indices_data(void) const { return indices.data(); }
    inline GLsizei get_indices_count(void) const { return 3*indices.size(); }

    const VertexBuffer& get_vertices_VBO(void);
    const VertexBuffer& get_color_solid_VBO(void);
    const VertexBuffer& get_color_line_VBO(void);
    const VertexBuffer& get_color_point_VBO(void);
    const IndexBuffer& get_indices_VBO(void);

    inline void clear_polygon_modes(void) { polygon_modes.clear(); }
    inline void enable_polygon_modes(int mode) { polygon_modes.insert(mode); }
    inline void disable_polygon_modes(int mode) { polygon_modes.erase(mode); }
    inline const std::set<int>& get_polygon_modes(void) const { return polygon_modes; }

  protected:
    void init_color(unsigned n_vertices);
    void calcular_normales(); // calcula tabla de normales de vértices (práctica 3)

    std::vector<Tupla3f> vertices;
    std::vector<Tupla3u> indices;
    std::vector<Tupla3f> color_solid;

  private:
    std::vector<Tupla3f> color_line;
    std::vector<Tupla3f> color_point;

    VertexBuffer* vertices_VBO {nullptr};
    VertexBuffer* color_solid_VBO {nullptr};
    VertexBuffer* color_line_VBO {nullptr};
    VertexBuffer* color_point_VBO {nullptr};
    IndexBuffer* indices_VBO {nullptr};

    std::set<int> polygon_modes;
};

#endif /* MOSHI3D_MESH3D_H_ */