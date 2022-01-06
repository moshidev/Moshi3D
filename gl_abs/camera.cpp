#include "camera.h"

Camera::Camera(Type type, float top, float right, float near, float far)
:type{type}, top{top}, right{right}, near{near}, far{far}
{   }

void rotate(const Tupla3f& r) {
    
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