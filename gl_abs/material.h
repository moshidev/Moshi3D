/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MATERIAL_H_
#define MOSHI3D_MATERIAL_H_

#include "_aux.h"

class Material {
public:
    Material(Tupla4f diffuse={0.50754, 0.50754, 0.50754, 1.0}, Tupla4f especular={0.508273, 0.508273, 0.508273, 1.0}, Tupla4f ambient={0.19225, 0.19225, 0.19225, 1.0}, float shiness=51.2);

    void set_current(void) const;

    static const Material& get_default(void);

private:
    Tupla4f diffuse;
    Tupla4f especular;
    Tupla4f ambient;
    float shiness;

    static Material def;
};

#undef _MDEF_

#endif /* MOSHI3D_MATERIAL_H_ */