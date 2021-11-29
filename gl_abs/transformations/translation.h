/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_TRANSLATION_H_
#define MOSHI3D_TRANSLATION_H_

#include "transformation.h"
#include <functional>

class Translation : public Transformation {
    Tupla3f translation_val;
    Translation& multiply_member_data(float val);

public:
    Translation() = delete;
    Translation(const Tupla3f& t);

    void set(const Tupla3f& t);
    void sum(const Tupla3f& t);
    virtual void apply(void) const;

    inline const Tupla3f& get(void) const { return translation_val; }

    friend Translation operator+(const Translation& lr, const Translation& rt);
    friend Translation operator-(const Translation& lr, const Translation& rt);
    friend Translation interpolation(const Translation& lr, const Translation& rt, float percentaje, const std::function<float(float)>& f);
};

#endif /* MOSHI3D_TRANSLATION_H_ */