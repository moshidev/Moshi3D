/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_ROTATION_H_
#define MOSHI3D_ROTATION_H_

#include "transformation.h"

class Rotation : public Transformation {
    Tupla3f polar_coordinates;
    Tupla3f rotation_point;
    void normalize_variables(void);
    Rotation& multiply_member_data(float val);

public:
    Rotation() = delete;
    Rotation(const Tupla3f& angls_rad);
    Rotation(const Tupla3f& angls_rad, const Tupla3f& rotation_point);
    static void apply(float angle_rad, const Tupla3f& rot_vec);
    static void apply(const Tupla3f& angls_rad);
    static void apply(const Tupla3f& angls_rad, const Tupla3f& rotation_point);

    void set(const Tupla3f& angls_rad, const Tupla3f& rotation_point);
    void set_rota(const Tupla3f& angls_rad);
    void set_rotp(const Tupla3f& rotation_point);
    void sum(const Tupla3f& angls_rad, const Tupla3f& rotation_point);
    void sum_rota(const Tupla3f& angls_rad);
    void sum_rotp(const Tupla3f& rotation_point);
    virtual void apply(void) const;

    inline const Tupla3f& get_angle(void) const { return polar_coordinates; }
    inline const Tupla3f& get_point(void) const { return rotation_point; }

    friend Rotation operator+(const Rotation& lr, const Rotation& rt);
    friend Rotation interpolation(Rotation lr, Rotation rt, float percentaje, const std::function<float(float)>& f);
};

#endif /* MOSHI3D_ROTATION_H_ */