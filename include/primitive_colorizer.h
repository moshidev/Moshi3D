/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_PRIMITIVE_COLORIZER_H_
#define MOSHI3D_PRIMITIVE_COLORIZER_H_

#include "malla.h"
#include "cube.h"
#include "tetraedro.h"
#include "tuplasg.h"

#define PC_BLACK Tupla3f{0,0,0}
#define PC_RED   Tupla3f{1,0,0}
#define PC_GREEN Tupla3f{0,1,0}

class PrimitiveColorizer {
    public:
        static void plain_color(Malla3D& m, const Tupla3f& color=PC_BLACK);

        static void chess(Tetraedro& t, const Tupla3f& color_a=PC_RED, const Tupla3f& color_b=PC_GREEN);
        static void chess(Cube& c, const Tupla3f& color_a=PC_RED, const Tupla3f& color_b=PC_GREEN);
        
        static void rgb_cube(Cube& c);
};

#undef PC_BLACK
#undef PC_RED
#undef PC_GREEN

#endif /* MOSHI3D_PRIMITIVE_COLORIZER_H_ */