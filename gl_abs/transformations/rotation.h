/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_ROTATION_H_
#define MOSHI3D_ROTATION_H_

#include "transformation.h"

class Rotation : public Transformation {
    Rotation& multiply_member_data(float val);
    
protected:
    float angle_rad;
    Tupla3f rot_vec;

    void normalize_variables(void);

public:
    Rotation() = delete;
    Rotation(float angle_rad, const Tupla3f& rot_vec);
    static void apply(float angle_rad, const Tupla3f& rot_vec);
    static void apply(float angle_rad_alpha, float angle_rad_beta);
    static void apply(const Tupla2f& polar_coor);

    void set(float angle_rad, const Tupla3f& rot_vec);
    void sum(float angle_rad, const Tupla3f& rot_vec);
    void sum(float angle_rad);
    void sum(const Tupla3f& rot_vec);
    virtual void apply(void) const;

    inline float get_angle(void) const { return angle_rad; }
    inline const Tupla3f& get_rot_vec(void) const { return rot_vec; }

    friend Rotation operator+(const Rotation& lr, const Rotation& rt);
    friend Rotation interpolation(const Rotation& lr, const Rotation& rt, float percentaje, const std::function<float(float)>& f);
};

#endif /* MOSHI3D_ROTATION_H_ */