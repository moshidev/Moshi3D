/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_CONE_H_
#define MOSHI3D_CONE_H_

#include "revolution_object.h"

class Cone : public RevolutionObject {
public:
    Cone(int num_vertices_side_face, int num_instances, float height, float radius);
};

#endif /* MOSHI3D_CONE_H_ */