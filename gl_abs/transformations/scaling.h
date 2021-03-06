/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_SCALING_H_
#define MOSHI3D_SCALING_H_

#include "transformation.h"

class Scaling : public Transformation {
    Tupla3f scale_factor_val;
    Scaling& multiply_member_data(float val);

public:
    Scaling() = delete;
    Scaling(const Tupla3f& factor);

    static void apply(const Tupla3f& factor);

    void set(const Tupla3f& factor);
    void mul(const Tupla3f& factor);
    void apply(void) const;

    inline const Tupla3f& get(void) const { return scale_factor_val; }

    friend Scaling operator+(const Scaling& lr, const Scaling& rt);
    friend Scaling operator-(const Scaling& lr, const Scaling& rt);
    friend Scaling interpolation(const Scaling& lr, const Scaling& rt, float percentaje, const std::function<float(float)>& f);
};

#endif /* MOSHI3D_SCALING_H_ */