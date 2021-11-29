/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_SCALING_H_
#define MOSHI3D_SCALING_H_

#include "transformation.h"

class Scaling : public Transformation {
    Tupla3f factor;

public:
    Scaling() = delete;
    Scaling(const Tupla3f& factor);

    void set(const Tupla3f& factor);
    void mul(const Tupla3f& factor);
    void apply(void) const;

    inline const Tupla3f& get(void) const { return factor; }
};

#endif /* MOSHI3D_SCALING_H_ */