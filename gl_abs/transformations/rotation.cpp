#include "rotation.h"

Rotation::Rotation(float angle_rad, const Tupla3f& rot_vec)
:angle_rad{angle_rad}, rot_vec{rot_vec}
{
    normalize_variables();
}

void Rotation::normalize_variables(void) {
    angle_rad = angle_rad > 2*M_PI ? angle_rad-M_PI : angle_rad;
    angle_rad = angle_rad < -2*M_PI ? angle_rad+M_PI : angle_rad;
    rot_vec = rot_vec.normalized();
    angle_deg = angle_rad*180/M_PI;
}

Rotation& Rotation::multiply_member_data(float val) {
    rot_vec = rot_vec * val;
    angle_rad = angle_rad * val;
    normalize_variables();
    return *this;
}

void Rotation::set(float angle_rad, const Tupla3f& rot_vec) {
    this->angle_rad = angle_rad;
    this->rot_vec = rot_vec;
    normalize_variables();
}

void Rotation::sum(float angle_rad, const Tupla3f& rot_vec) {
    sum(angle_rad);
    sum(rot_vec);
}

void Rotation::sum(float angle_rad) {
    this->angle_rad += angle_rad;
    normalize_variables();
}

void Rotation::sum(const Tupla3f& rot_vec) {
    this->rot_vec = this->rot_vec + rot_vec;
    normalize_variables();
}

void Rotation::apply(void) const {
    glRotatef(angle_deg, rot_vec(0), rot_vec(1), rot_vec(2));
}

Rotation operator+(const Rotation& lr, const Rotation& rt) {
    Rotation ret{lr};
    ret.sum(rt.angle_rad, rt.rot_vec);
    return ret;
}

Rotation operator-(const Rotation& lr, const Rotation& rt) {
    Rotation ret{lr};
    ret.sum(-rt.angle_rad, -rt.rot_vec);
    return ret;
}

Rotation interpolation(const Rotation& lr, const Rotation& rt, float percentaje, const std::function<float(float)>& f) {
    return lr + (rt - lr).multiply_member_data(f(percentaje));
}
