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

protected:
    RevolutionObject();
    virtual void init_normal_vectors(void);

    IndexBufferObject cover_south_IB;
    IndexBufferObject cover_north_IB;
    std::vector<Tupla3u> cover_south;
    std::vector<Tupla3u> cover_north;
    std::vector<Tupla3f> cover_south_normal;
    std::vector<Tupla3f> cover_north_normal;
    bool render_cover_south {true};
    bool render_cover_north {true};
    bool force_cover_south {false};
    bool force_cover_north {false};

    void make_revolution_surface(std::vector<Tupla3f> revolution_coordinates, int num_instances, bool make_cover_south, bool make_cover_north, int axis=1);
    virtual void make_current_buffered_data_list(void);
    virtual void make_current_raw_data_list(void);

private:
    void revolution_surface_make_topology(const std::vector<Tupla3f>& rv, int num_instances);
    void revolution_surface_make_geometry(std::vector<Tupla3f>& rv, int num_instances, int eje);

    void covers_extract_pole(std::vector<Tupla3f>& rv, std::vector<Tupla3f>::iterator it, Tupla3f& pole, int axis);
    void covers_extract_poles(std::vector<Tupla3f>& rv, Tupla3f& south, Tupla3f& north, int axis);

    void covers_make_topology(std::vector<Tupla3u>& ci, int shared_vertice_index, int num_instances, int height_offset, bool clockwise);
    void covers_make_south(const Tupla3f& south, int num_instances);
    void covers_make_north(const Tupla3f& north, int num_instances, int height);
};

#endif /* MOSHI3D_REVOLUTION_OBJECT_H_ */