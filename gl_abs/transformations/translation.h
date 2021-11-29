/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_TRANSLATION_H_
#define MOSHI3D_TRANSLATION_H_

#include "transformation.h"

class Translation : public Transformation {
    Tupla3f translation;

public:
    Translation() = delete;
    Translation(const Tupla3f& t);

    void set(const Tupla3f& t);
    void sum(const Tupla3f& t);
    virtual void apply(void) const;

    inline const Tupla3f& get(void) const { return translation; }
};

#endif /* MOSHI3D_TRANSLATION_H_ */