#include "camera.h"
#include <iostream>

Camera::Camera(Type type, float top, float right, float near, float far)
:type{type}, top{top}, right{right}, near{near}, far{far}
{   }

void Camera::rotate(const Tupla3f& angles, Tupla3f& v) {
    for (int i = 0; i < 3; i++) {
        const double& angle = angles[i];
        if (angle == 0) {
            continue;
        }
        double _sin = sin(angle);
        double _cos = cos(angle);
        if (i == 0)       // X axis
            v = Tupla3f{v[0], v[1]*_cos-v[2]*_sin, v[1]*_sin+v[2]*_cos};
        else if (i == 1)  // Y axis
            v = Tupla3f{v[0]*_cos+v[2]*_sin, v[1], -v[0]*_sin+v[2]*_cos};
        else                // Z axis
            v = Tupla3f{v[0]*_cos-v[1]*_sin, v[0]*_sin+v[1]*_cos, v[2]};
    }
}

void Camera::rotate_eye(const Tupla3f& angles) {
    Tupla3f at_v = at - eye;
    rotate(angles, up);
    rotate(angles, at_v);
    at = at_v + eye;
}

void Camera::rotate_at(const Tupla3f& angles) {
    Tupla3f eye_v = eye - at;
    rotate(angles, up);
    rotate(angles, eye_v);
    eye = eye_v + at;
}

void Camera::displace(const Tupla3f& d) {
    eye = eye + d;
    at = at + d;
}

void Camera::zoom(float factor) {
    float tmptop = top, tmpright = right;
    top   *= factor;
	right  *= factor;
    if (top <= 0 || right <= 0) {
        top = tmptop;
        right = tmpright;
    }
}

void Camera::observe(void) const {
    gluLookAt(eye[0], eye[1], eye[2],
                at[0], at[1], at[2],
                up[0], up[1], up[2]
    );
}

void Camera::project(void) const {
    float left = -right;
    float bottom = -top;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (type == kPerspective) {
        glFrustum(left, right, bottom, top, near, far);
    }	
	else if (type == kOrthographic) {
        glOrtho(left, right, bottom, top, near, far);
    }
}