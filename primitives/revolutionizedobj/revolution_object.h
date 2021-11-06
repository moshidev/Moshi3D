/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_REVOLUTION_OBJECT_H_
#define MOSHI3D_REVOLUTION_OBJECT_H_

#include <string>
#include <vector>
#include "mesh.h"

class RevolutionObject : public Mesh3D {
public:
    RevolutionObject(const std::string& ifile, int num_instances, bool make_covers=true);
    RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool make_covers=true);
    
    virtual void enable_covers_visibility(bool b);
    inline bool are_covers_visible(void) const { return covers_enabled; }

protected:
    RevolutionObject();

    IndexBuffer cover_south_VBO;
    IndexBuffer cover_north_VBO;
    std::vector<Tupla3u> cover_south;
    std::vector<Tupla3u> cover_north;
    std::vector<std::pair<IndexBuffer&, std::vector<Tupla3u>&>> covers;
    bool covers_enabled {false};
    bool has_covers {false};

    void make_revolution_surface(std::vector<Tupla3f> revolution_coordinates, int num_instances, bool make_covers=true);
    virtual void make_current_buffer_data_list(void);

private:
    void revolution_surface_make_topology(const std::vector<Tupla3f>& rv, int num_instances);
    void revolution_surface_make_geometry(std::vector<Tupla3f>& rv, int num_instances);

    void covers_extract_pole(std::vector<Tupla3f>& rv, std::vector<Tupla3f>::iterator it, Tupla3f& pole);
    void covers_extract_poles(std::vector<Tupla3f>& rv, Tupla3f& south, Tupla3f& north);

    void covers_make_topology(std::vector<Tupla3u>& ci, int shared_vertice_index, int num_instances, int height_offset, bool clockwise);
    void covers_make_south(const Tupla3f& south, int num_instances);
    void covers_make_north(const Tupla3f& north, int num_instances, int height);
};

#endif /* MOSHI3D_REVOLUTION_OBJECT_H_ */