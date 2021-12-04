/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_POINT_ROTATION_H_
#define MOSHI3D_POINT_ROTATION_H_

#include "rotation.h"

class PointRotation : public Rotation {
    Tupla3f point;  /// Representa la distancia con respecto al origen (|punto-origen|)
    PointRotation& multiply_member_data(float val);

public:
    PointRotation() = delete;
    PointRotation(float angle_rad, const Tupla3f&  vec_rot, const Tupla3f&  point);

    void set(float angle_rad, const Tupla3f&  vec_rot, const Tupla3f&  point);
    void sum(float angle_rad, const Tupla3f&  vec_rot, const Tupla3f&  point);
    void sum(const Tupla3f&  point);
    void apply(void) const;

    friend PointRotation operator+(const PointRotation& lr, const PointRotation& rt);
    friend PointRotation operator-(const PointRotation& lr, const PointRotation& rt);
    friend PointRotation interpolation(const PointRotation& lr, const PointRotation& rt, float percentaje, const std::function<float(float)>& f);
};

#endif /* MOSHI3D_POINT_ROTATION_H_ */