/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_TRANSFORMATION_H_
#define MOSHI3D_TRANSFORMATION_H_

#include "_aux.h"

class Transformation {
public:
    virtual void apply(void) const = 0;

    inline static void load_identity(void) { glLoadIdentity(); }
    inline static void push_matrix(void) { glPushMatrix(); }
    inline static void pop_matrix(void) { glPopMatrix(); }
};

#endif /* MOSHI3D_TRANSFORMATION_H_ */