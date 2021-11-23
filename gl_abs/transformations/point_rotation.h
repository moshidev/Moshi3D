/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_POINT_ROTATION_H_
#define MOSHI3D_POINT_ROTATION_H_

#include "rotation.h"

class PointRotation : public Rotation {
    Tupla3f point;  /// Representa la distancia con respecto al origen (|punto-origen|)

public:
    PointRotation() = delete;
    PointRotation(float angle_rad, Tupla3f vec_rot, Tupla3f point);

    void set(float angle_rad, Tupla3f vec_rot, Tupla3f point);
    void sum(float angle_rad, Tupla3f vec_rot, Tupla3f point);
    void sum(Tupla3f point);
    void apply(void) const;
};

#endif /* MOSHI3D_POINT_ROTATION_H_ */