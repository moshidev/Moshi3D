/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MESH3D_H_
#define MOSHI3D_MESH3D_H_

#include <set>
#include <list>
#include "_aux.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

class Renderer;

class Mesh3D {
  public:
    class BufferedData;
    class RawData;
    
    Mesh3D();
    virtual ~Mesh3D() = 0;

    virtual void draw(const Renderer& r);

    /* Permite la visualización simultánea de cualquier combinación que se quiera de GL_FILL, GL_LINE y GL_POINT*/
    /* Si se selecciona GL_FILL y el modo ajedrez está activado lo desactiva */
    void clear_polygon_modes(void);
    void enable_polygon_modes(int mode);
    void disable_polygon_modes(int mode);
    inline const std::set<int>& get_polygon_modes(void) const { return polygon_modes; }

    /* Habilita o deshabilita la visualización del modo ajedrez. Si GL_FILL está activado lo desactiva. */
    void enable_chess_mode(bool b);
    inline bool is_chess_mode_enabled(void) const { return chess_enabled; }

    /* Métodos get para obtener la información a renderizar */
    inline const std::list<BufferedData>& get_buffer_data_list(void) { return current_buffer_data_list; }
    inline const std::list<RawData>& get_raw_data_list(void) const { return current_raw_data_list; }

  protected:
    /* Inicializa los distintos vectores de colores a su valor por defecto */
    void init_color(unsigned n_vertices);

    /* Limpia e establece (actualiza) la lista de información a renderizar */
    virtual void make_data_lists(void);

    std::list<BufferedData> get_chess_buffer_list(VertexBuffer& vertices, IndexBuffer& indices);
    std::list<RawData> get_chess_raw_list(void) const;

    VertexBuffer& get_vertices_VBO(void);
    IndexBuffer& get_indices_VBO(void);
    VertexBuffer& get_color_fill_VBO(void);
    VertexBuffer& get_color_line_VBO(void);
    VertexBuffer& get_color_point_VBO(void);

    void init_vertex_buffer(VertexBuffer*& vb, const std::vector<Tupla3f>& v);
    void init_index_buffer(IndexBuffer*& ib, const std::vector<Tupla3u>& v);
    void update_vertex_buffer(VertexBuffer*& vb, GLsizeiptr size, const GLvoid* data);
    void update_index_buffer(IndexBuffer*& ib, GLsizei count, const GLvoid* data);

    void calcular_normales(void); // calcula tabla de normales de vértices (práctica 3)

    bool chess_enabled;
    std::set<int> polygon_modes;

    std::vector<Tupla3f> vertices;
    std::vector<Tupla3u> indices;

    std::list<BufferedData> current_buffer_data_list;
    std::list<RawData> current_raw_data_list;

  private:
    std::vector<Tupla3f> color_fill;
    std::vector<Tupla3f> color_line;
    std::vector<Tupla3f> color_point;
    std::vector<Tupla3f> color_chess_a;
    std::vector<Tupla3f> color_chess_b;

    VertexBuffer* vertices_VBO {nullptr};
    IndexBuffer* indices_VBO {nullptr};
    VertexBuffer* color_fill_VBO {nullptr};
    VertexBuffer* color_line_VBO {nullptr};
    VertexBuffer* color_point_VBO {nullptr};
    VertexBuffer* color_chess_a_VBO {nullptr};
    VertexBuffer* color_chess_b_VBO {nullptr};
};

class Mesh3D::BufferedData {
    VertexBuffer& vertices;
    IndexBuffer& face_indices;
    VertexBuffer& color;
    unsigned indices_offset;
    unsigned indices_count;
    int polygon_mode;

public:
    BufferedData(VertexBuffer& vertices, IndexBuffer& faces, VertexBuffer& color, int polygon_mode)
        :vertices{vertices}, face_indices{faces}, color{color},
         indices_offset{0}, indices_count{faces.get_num_indices()},
         polygon_mode{polygon_mode}
    {}

    inline const VertexBuffer& get_vertices(void) const { return vertices; }

    inline const IndexBuffer& get_indices(void) const { return face_indices; }
    inline unsigned get_indices_offset(void) const { return indices_offset; }
    inline unsigned get_indices_count(void) const { return indices_count; }
    inline void set_face_indices_offset(unsigned offset, unsigned count) { indices_offset = offset; indices_count = count; }

    inline const VertexBuffer& get_color(void) const { return color; }

    inline int get_polygon_mode(void) const { return polygon_mode; }
};

class Mesh3D::RawData {
    std::vector<Tupla3f>& vertices_data;
    std::vector<Tupla3f>& color_data;
    std::vector<Tupla3u>& face_indices_data;
    unsigned indices_offset;
    unsigned indices_size;
    int polygon_mode;

public:
    RawData(std::vector<Tupla3f>& vertices, std::vector<Tupla3f>& color, std::vector<Tupla3u>& faces, int polygon_mode);
    int get_polygon_mode(void);

    inline const std::vector<Tupla3f>& get_vertices_data(void) const {return vertices_data; }

    inline const std::vector<Tupla3u>& get_indices_data(void) const { return face_indices_data; };
    inline unsigned get_indices_offset(void) const { return indices_offset; }
    inline unsigned get_indices_size(void) const { return indices_size; }

    inline const std::vector<Tupla3f>& get_color_data(void) const { return color_data; }
};

#endif /* MOSHI3D_MESH3D_H_ */