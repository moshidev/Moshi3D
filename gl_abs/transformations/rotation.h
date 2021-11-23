/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_ROTATION_H_
#define MOSHI3D_ROTATION_H_

#include "transformation.h"

class Rotation : public Transformation {
protected:
    float angle_rad;
    float angle_deg;
    Tupla3f rot_vec;

    void normalize_variables(void);

public:
    Rotation() = delete;
    Rotation(float angle_rad, const Tupla3f& rot_vec);

    void set(float angle_rad, const Tupla3f& rot_vec);
    void sum(float angle_rad, const Tupla3f& rot_vec);
    void sum(float angle_rad);
    void sum(const Tupla3f& rot_vec);
    virtual void apply(void) const;

    inline float get_angle(void) const { return angle_rad; }
    inline const Tupla3f& get_rot_vec(void) const { return rot_vec; }
    Rotation get_sum(float angle_rad, const Tupla3f& rot_vec) const;
    Rotation get_sum(float angle_rad) const;
    Rotation get_sum(const Tupla3f& rot_vec) const;
};

#endif /* MOSHI3D_ROTATION_H_ */