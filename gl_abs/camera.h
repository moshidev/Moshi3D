/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_CAMERA_H_
#define MOSHI3D_CAMERA_H_

#include "_aux.h"

class Camera {
public:
    enum Type {
        kOrthographic, kPerspective
    };
    float right;
    float top;
    float near;
    float far;

    Camera(Type type, float top, float right, float near, float far);
    void rotate(const Tupla3f& r);
    void displace(const Tupla3f& d);
    void zoom(float factor);
    void observe(void) const;
    void project(void) const;
    inline void set_projection_type(Type t) { type = t; };

private:
    Tupla3f eye{0,0,1};
    Tupla3f at{0,0,0};
    Tupla3f up{0,1,0};

    Type type;
};

#endif /* MOSHI3D_CAMERA_H_ */