/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MESH3D_H_
#define MOSHI3D_MESH3D_H_

#include <set>
#include "_aux.h"
#include "color.h"

class Renderer;

class Mesh3D {
  public:
    virtual void draw(const Renderer& r);
    void set_color_chess(void);
    void set_color_plain(void);

    static GLuint create_VBO(GLuint target, GLsizeiptr size, const void* data, GLuint usage=GL_STATIC_DRAW);

    inline const GLvoid* get_vertices_data(void) const { return vertices.data(); }
    inline const GLvoid* get_indices_data(void) const { return indices.data(); }
    inline const GLvoid* get_color_data(void) const { return color.get_data(); }
    inline GLuint get_color_shade_mode(void) const { return color.get_shade_mode(); }
    inline GLsizei get_indices_size(void) const { return 3*indices.size(); }
    inline size_t get_num_vertices(void) const { return vertices.size(); }

    /**
     * @brief returns a GL_ARRAY_BUFFER VBO id with the data inside vertices. The first call
     * to this function will allocate a new VBO for this data.
     * @warning the VBO_id returned should never be deallocated or modified.
     */
    GLuint get_vertices_VBO_id(void);

    /**
     * @brief returns a GL_ELEMENT_ARRAY_BUFFER id with the data inside indices. The first call
     * to this function will allocate a new VBO for this data.
     * @warning the VBO_id returned should never be deallocated or modified.
     */
    GLuint get_indices_VBO_id(void);

    /**
     * @brief returns a GL_ELEMENT_ARRAY_BUFFER id with the data inside color. The first call
     * to this function will allocate a new VBO for this data.
     * @warning the VBO_id returned should never be deallocated or modified.
     */
    inline GLuint get_color_VBO_id(void) { return color.get_VBO_id(); }

    inline void clear_polygon_modes(void) { polygon_modes.clear(); }
    inline void enable_polygon_modes(int mode) { polygon_modes.insert(mode); }
    inline void disable_polygon_modes(int mode) { polygon_modes.erase(mode); }
    inline const std::set<int>& get_polygon_modes(void) const { return polygon_modes; }

  protected:
    void calcular_normales(); // calcula tabla de normales de vértices (práctica 3)

    std::vector<Tupla3f> vertices;
    std::vector<Tupla3u> indices;
    Color color;

  private:
    GLuint vertices_VBO_id {0};
    GLuint indices_VBO_id {0};
    std::set<int> polygon_modes;

  public:
    Mesh3D();
    virtual ~Mesh3D() = 0;
};

#endif /* MOSHI3D_MESH3D_H_ */