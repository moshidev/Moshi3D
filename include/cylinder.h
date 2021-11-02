/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_CYLINDER_H_
#define MOSHI3D_CYLINDER_H_

#include "revolution_object.h"

class Cylinder : public RevolutionObject {
public:
    Cylinder(int num_vertices_side_face, int num_instances, float height, float radius, bool make_south_cover=true, bool make_north_cover=true);
};

#endif /* MOSHI3D_CYLINDER_H_ */