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
    void revolution_surface_make_topology(const std::vector<Tupla3f>& rv, int num_instances, int midpoint);
    void revolution_surface_make_geometry(std::vector<Tupla3f>& rv, int num_instances);

    void covers_extract_pole(std::vector<Tupla3f>& rv, std::vector<Tupla3f>::iterator it, Tupla3f& pole);
    void covers_extract_poles(std::vector<Tupla3f>& rv, Tupla3f& south, Tupla3f& north);
    void covers_make_topology(int shared_vertice_index, int num_instances, int height_offset, int midpoint, int midpoint_offset, bool clockwise);
    void covers_make_south(const Tupla3f& south, int num_instances, int midpoint, int offset);
    void covers_make_north(const Tupla3f& north, int num_instances, int height, int midpoint, int offset);

protected:
    void make_revolution_surface(std::vector<Tupla3f> revolution_coordinates, int num_instances, bool make_south_cover=true, bool make_north_cover=true);
    RevolutionObject();

public:
    RevolutionObject(const std::string& ifile, int num_instances, bool make_south_cover=true, bool make_north_cover=true);
    RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool make_south_cover=true, bool make_north_cover=true);
};

#endif /* MOSHI3D_REVOLUTION_OBJECT_H_ */