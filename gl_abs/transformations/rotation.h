/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_ROTATION_H_
#define MOSHI3D_ROTATION_H_

#include "transformation.h"

class Rotation : public Transformation {
    Tupla2f polar_coordinates;
    Tupla3f rotation_point;
    void normalize_variables(void);

public:
    Rotation() = delete;
    Rotation(const Tupla2f& polar_coor);
    Rotation(const Tupla2f& polar_coor, const Tupla3f& rotation_point);
    static void apply(float angle_rad, const Tupla3f& rot_vec);
    static void apply(const Tupla2f& polar_coor);
    static void apply(const Tupla2f& polar_coor, const Tupla3f& rotation_point);

    void set(const Tupla2f& polar_coor, const Tupla3f& rotation_point);
    void set(const Tupla2f& polar_coor);
    void set(const Tupla3f& rotation_point);
    void sum(const Tupla2f& polar_coor, const Tupla3f& rotation_point);
    void sum(const Tupla2f& polar_coor);
    void sum(const Tupla3f& rotation_point);
    virtual void apply(void) const;

    inline const Tupla2f& get_angle(void) const { return polar_coordinates; }
    inline const Tupla3f& get_point(void) const { return rotation_point; }

    friend Rotation operator+(const Rotation& lr, const Rotation& rt);
    friend Rotation interpolation(const Rotation& lr, const Rotation& rt, float percentaje, const std::function<float(float)>& f);
};

#endif /* MOSHI3D_ROTATION_H_ */