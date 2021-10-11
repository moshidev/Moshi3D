/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "_aux.h"

class Renderer;

class Malla3D {
  public:
    virtual void draw(const Renderer& r);

    static GLuint create_VBO(GLuint target, GLsizeiptr size, const void* data, GLuint usage=GL_STATIC_DRAW);

    inline const GLvoid* get_vertices_data(void) const { return vertices.data(); }
    inline const GLvoid* get_indices_data(void) const { return indices.data(); }
    inline const GLvoid* get_color_data(void) const { return color.data(); }
    inline GLsizei get_indices_size(void) const { return 3*indices.size(); }

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
    GLuint get_color_VBO_id(void);

  protected:
    void calcular_normales(); // calcula tabla de normales de vértices (práctica 3)

    std::vector<Tupla3f> vertices;
    std::vector<Tupla3u> indices;
    std::vector<Tupla3f> color;

  private:
    GLuint vertices_VBO_id {0};
    GLuint indices_VBO_id {0};
    GLuint color_VBO_id {0};

  public:
    virtual ~Malla3D() = 0;
    
    void set_color_array(const std::vector<Tupla3f>& c);
};

#endif