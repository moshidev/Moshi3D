/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_REVOLUTION_OBJECT_H_
#define MOSHI3D_REVOLUTION_OBJECT_H_

#include <string>
#include <vector>
#include <tuple>
#include "mesh.h"

class RevolutionObject : public Mesh3D {
public:
    RevolutionObject(const std::string& ifile, int num_instances, bool make_covers=true);
    RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool make_covers=true);
    RevolutionObject(const std::string& ifile, int num_instances, bool make_cover_south, bool make_cover_north, int eje);
    RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool make_cover_south, bool make_cover_north, int eje);
    
    virtual void enable_covers_visibility(bool b);
    inline bool are_covers_visible(void) const { return render_cover_south || render_cover_north; }
    void set_texture(const std::shared_ptr<TextureObject>& texture);

protected:
    RevolutionObject();
    virtual void init_normal_vectors(void);

    VertexBuffer<Tupla2f> texture_coordinates;
    IndexBuffer cover_south_indices;
    IndexBuffer cover_north_indices;
    bool render_cover_south {true};
    bool render_cover_north {true};
    bool force_cover_south {false};
    bool force_cover_north {false};

    void make_revolution_surface(std::vector<Tupla3f> revolution_coordinates, int num_instances, bool make_cover_south, bool make_cover_north, int axis=1);
    virtual void make_current_data_list(void);

private:
    void revolution_surface_make_topology(const std::vector<Tupla3f>& rv, int num_instances);
    void revolution_surface_make_geometry(std::vector<Tupla3f>& rv, int num_instances, int axis);
    void revolution_surface_make_texture_coordinates(const std::vector<Tupla3f>& rv, int num_instances, int axis, float low_p, float top_p);

    void covers_extract_pole(std::vector<Tupla3f>& rv, std::vector<Tupla3f>::iterator it, Tupla3f& pole, int axis);
    void covers_extract_poles(std::vector<Tupla3f>& rv, Tupla3f& south, Tupla3f& north, int axis);

    void covers_make_texture_coordinates(int min_shared_vertice_index, int num_instances, float y);
    void covers_make_topology(std::vector<Tupla3u>& ci, int min_shared_vertice_index, int num_instances, int height, int height_offset, bool clockwise);
    void covers_make_geometry(const Tupla3f& pole, int num_instances);
    void covers_make_south(const Tupla3f& south, int num_instances, int height);
    void covers_make_north(const Tupla3f& north, int num_instances, int height);
};

#endif /* MOSHI3D_REVOLUTION_OBJECT_H_ */