/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MESH3D_H_
#define MOSHI3D_MESH3D_H_

#include <set>
#include <list>
#include <memory>
#include "_aux.h"
#include "vertex_buffer.hpp"
#include "index_buffer.h"
#include "renderizable.h"
#include "material.h"
#include "texture.h"

class Mesh3D : public Renderizable{
public:
    struct Data;
    class BufferedData;
    class RawData;

    Mesh3D(const Mesh3D& m) = delete;
    virtual ~Mesh3D() = 0;

    void draw(const Renderer& r) const;

    /* Permite la visualización simultánea de cualquier combinación que se quiera de GL_FILL, GL_LINE y GL_POINT*/
    /* Si se selecciona GL_FILL y el modo ajedrez o el sombreado está activado lo desactiva */
    void clear_polygon_modes(void);
    void enable_polygon_modes(int mode);
    void disable_polygon_modes(int mode);
    inline const std::set<int>& get_polygon_modes(void) const { return polygon_modes; }

    /* Habilita o deshabilita la visualización del modo ajedrez. Si GL_FILL o el sombreado está activado lo desactiva. */
    void enable_chess_mode(bool b);
    inline bool is_chess_mode_enabled(void) const { return chess_enabled; }

    /* Habilita o deshabilita el modo con sombreado. Si GL_FILL o el modo ajedrez está activado lo desactiva */
    void enable_shaded_mode(bool b);
    inline bool is_shade_mode_enabled(void) const { return shaded_enabled; }

    /* Métodos get para obtener la información a renderizar */
    inline const std::list<Data>& get_data_list(void) const { return current_data_list; }
    inline void set_material(const Material& m) { material = m; }

protected:
    Mesh3D();

    /* Inicializa los distintos vectores de colores a su valor por defecto */
    void init_color(unsigned n_vertices);
    /* Inicializa la lista de normales a los vértices y a las caras */
    virtual void init_normal_vectors(void);
    template<typename _T>
    void init_vertex_buffer(VertexBuffer<_T>& vb);
    void init_index_buffer(IndexBuffer& ib);


    void compute_normal_faces(std::vector<Tupla3f>& nf_dst, const std::vector<Tupla3u>& indices);
    void sum_normal_faces_to_vertices_normals(const std::vector<Tupla3f>& nf, const std::vector<Tupla3u>& indices);
    void normalize_vertices_normals(void);

    /* Crea la estructura de los datos a exportar para renderizar. Lo almacena en current_[buffered,raw]_data_list */
    virtual void make_current_data_list(void);
    std::list<Data> mklist_polygon_mode(IndexBuffer& ib);
    std::list<Data> mklist_chess_mode(IndexBuffer& ib);
    std::list<Data> mklist_shaded_mode(IndexBuffer& ib, const Material& m);

    void make_current_data_lists(void);

    bool chess_enabled{false};
    bool shaded_enabled{false};
    std::set<int> polygon_modes;

    VertexBuffer<Tupla3f> vertices;
    VertexBuffer<Tupla3f> vertices_normal;
    IndexBuffer indices;
    VertexBuffer<Tupla3f> color_fill;
    VertexBuffer<Tupla3f> color_line;
    VertexBuffer<Tupla3f> color_point;
    VertexBuffer<Tupla3f> color_chess_a;
    VertexBuffer<Tupla3f> color_chess_b;
    Material material;
    std::shared_ptr<const Texture> texture;

    std::list<Data> current_data_list;
};

struct Mesh3D::Data {
    const VertexBuffer<Tupla3f>& vertices;
    const VertexBuffer<Tupla3f>& vertices_normals;

    const IndexBuffer& face_indices;
    unsigned indices_offset;
    unsigned indices_count;

    const VertexBuffer<Tupla3f>* color {nullptr};
    const Material* material {nullptr};
    
    bool affected_by_light;
    const int polygon_mode;
    
    Data() = delete;
    Data(const Data& d) = delete;

    inline void set_face_indices_offset(unsigned offset, unsigned count) {
        indices_offset = offset; indices_count = count;
    }

    Data(const VertexBuffer<Tupla3f>& vertices, const VertexBuffer<Tupla3f>& vertices_normals, const IndexBuffer& face_indices, int polygon_mode, const VertexBuffer<Tupla3f>& color, const Material& material)
    : Data{vertices, vertices_normals, face_indices, polygon_mode}
    {
        this->color = &color;
        this->material = &material;
    }

    Data(const VertexBuffer<Tupla3f>& vertices, const VertexBuffer<Tupla3f>& vertices_normals, const IndexBuffer& face_indices, int polygon_mode, const VertexBuffer<Tupla3f>& color)
    : Data{vertices, vertices_normals, face_indices, polygon_mode}
    {
        this->color = &color;
        affected_by_light = false;
    }

    Data(const VertexBuffer<Tupla3f>& vertices, const VertexBuffer<Tupla3f>& vertices_normals, const IndexBuffer& face_indices, int polygon_mode, const Material& material)
    : Data{vertices, vertices_normals, face_indices, polygon_mode}
    {
        this->material = &material;
    }

private:
    Data(const VertexBuffer<Tupla3f>& vertices, const VertexBuffer<Tupla3f>& vertices_normals, const IndexBuffer& face_indices, int polygon_mode)
    : vertices{vertices}, vertices_normals{vertices_normals}, face_indices{face_indices},
        indices_offset{0}, indices_count{face_indices.get_num_indices()},
        affected_by_light{true}, polygon_mode{polygon_mode}
    {   }
};

/**
 * BufferedData contiene la información necesaria para renderizar un objeto usando
 * VBOs
 */
class Mesh3D::BufferedData {
    const VertexBufferObject& vertices;
    const IndexBufferObject& face_indices;
    const VertexBufferObject& color;
    const VertexBufferObject& vertices_normals;
    const Material& material;
    bool affected_by_light{true};
    unsigned indices_offset;
    unsigned indices_count;
    int polygon_mode;

public:
    BufferedData(const VertexBufferObject& vertices, const IndexBufferObject& faces, const VertexBufferObject& color, const VertexBufferObject& vertices_normals, const Material& m, int polygon_mode)
        :vertices{vertices}, face_indices{faces}, color{color},
         vertices_normals{vertices_normals}, material{m},
         indices_offset{0}, indices_count{faces.get_num_indices()},
         polygon_mode{polygon_mode}
    {}

    inline const VertexBufferObject& get_vertices(void) const { return vertices; }
    inline const VertexBufferObject& get_vertices_normals(void) const { return vertices_normals; }

    inline const IndexBufferObject& get_indices(void) const { return face_indices; }
    inline unsigned get_indices_offset(void) const { return indices_offset; }
    inline unsigned get_indices_count(void) const { return indices_count; }
    inline void set_face_indices_offset(unsigned offset, unsigned count) { indices_offset = offset; indices_count = count; }

    inline const VertexBufferObject& get_color(void) const { return color; }
    inline const Material& get_material(void) const { return material; }

    inline int get_polygon_mode(void) const { return polygon_mode; }
    inline bool get_affected_by_light(void) const { return affected_by_light; }
    inline void set_affected_by_light(bool t) { affected_by_light = t; }
};


/**
 * RawData contiene la información necesaria para renderizar un objeto usando
 * glDrawElements
 */
class Mesh3D::RawData {
    const std::vector<Tupla3f>& vertices_data;
    const std::vector<Tupla3u>& face_indices_data;
    const std::vector<Tupla3f>& color_data;
    const std::vector<Tupla3f>& vertices_normals_data;
    const Material& material;
    bool affected_by_light{true};
    int polygon_mode;
    unsigned indices_count;
    unsigned indices_offset;    

public:
    RawData(const std::vector<Tupla3f>& vertices, const std::vector<Tupla3u>& faces, const std::vector<Tupla3f>& color, const std::vector<Tupla3f>& vertices_normals, const Material& m, int polygon_mode)
        :vertices_data{vertices}, face_indices_data{faces}, color_data{color},
         vertices_normals_data{vertices_normals}, material{m},
         polygon_mode{polygon_mode}, indices_count{(unsigned)faces.size()*3}, indices_offset{0}
    {}

    inline const std::vector<Tupla3f>& get_vertices_data(void) const {return vertices_data; }
    inline const std::vector<Tupla3f>& get_vertices_normals_data(void) const { return vertices_normals_data; }

    inline const std::vector<Tupla3u>& get_indices_data(void) const { return face_indices_data; };
    inline unsigned get_indices_offset(void) const { return indices_offset; }
    inline unsigned get_indices_count(void) const { return indices_count; }
    inline void set_face_indices_offset(unsigned offset, unsigned count) { indices_offset = offset; indices_count = count; }

    inline const std::vector<Tupla3f>& get_color_data(void) const { return color_data; }
    inline const Material& get_material(void) const { return material; }

    inline int get_polygon_mode(void) const { return polygon_mode; }
    inline bool get_affected_by_light(void) const { return affected_by_light; }
    inline void set_affected_by_light(bool t) { affected_by_light = t; }
};

#endif /* MOSHI3D_MESH3D_H_ */