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
    void revolution_surface_make_topology(const std::vector<Tupla3f>& rv, int num_instances);
    void revolution_surface_make_geometry(const std::vector<Tupla3f>& rv, int num_instances);
    void make_revolution_surface(std::vector<Tupla3f> revolution_coordinates, int num_instances);

    public:
    RevolutionObject(const std::string& ifile, int num_instances, bool upper_surface=true, bool lower_surface=true);
    RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool upper_surface=true, bool lower_surface=true);
};

#endif /* MOSHI3D_REVOLUTION_OBJECT_H_ */