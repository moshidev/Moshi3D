/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_SPHERE_H_
#define MOSHI3D_SPHERE_H_

#include "revolution_object.h"

class Sphere : public RevolutionObject {
public:
    Sphere(int num_vertices_side_face, int num_instances, float radius);

    inline void enable_covers_visibility(bool b) {};
};

#endif /* MOSHI3D_SPHERE_H_ */