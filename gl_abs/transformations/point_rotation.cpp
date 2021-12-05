#include "point_rotation.h"

PointRotation::PointRotation(float angle_rad, const Tupla3f&  vec_rot, const Tupla3f&  point)
:Rotation::Rotation{angle_rad, vec_rot}, point{point}
{   }

void PointRotation::apply(float angle_rad, const Tupla3f& rot_vec, const Tupla3f& point) {
    constexpr float rad_deg_equiv = 180/M_PI;
    glTranslatef(-point[0], -point[1], -point[2]);
    glRotatef(angle_rad*rad_deg_equiv, rot_vec[0], rot_vec[1], rot_vec[2]);
    glTranslatef(+point[0], +point[1], +point[2]);
}

void PointRotation::set(float angle_rad, const Tupla3f&  vec_rot, const Tupla3f&  point) {
    Rotation::set(angle_rad, vec_rot);
    this->point = point;
}

void PointRotation::sum(float angle_rad, const Tupla3f&  vec_rot, const Tupla3f&  point) {
    Rotation::sum(angle_rad, vec_rot);
    this->point = this->point + point;
}

void PointRotation::sum(const Tupla3f&  point) {
    this->point = this->point + point;
}

void PointRotation::apply(void) const {
    PointRotation::apply(angle_rad, rot_vec, point);
}

PointRotation& PointRotation::multiply_member_data(float val) {
    angle_rad *= val;
    rot_vec = rot_vec * val;
    point = point * val;
    if (val != 0) {
        normalize_variables();
    }
    return *this;
}

PointRotation operator+(const PointRotation& lr, const PointRotation& rt) {
    PointRotation ret{lr};
    ret.sum(rt.angle_rad, rt.rot_vec, rt.point);
    return ret;
}

PointRotation operator-(const PointRotation& lr, const PointRotation& rt) {
    PointRotation ret{lr};
    ret.sum(-rt.angle_rad, -rt.rot_vec, -rt.point);
    return ret;
}

PointRotation interpolation(const PointRotation& lr, const PointRotation& rt, float percentaje, const std::function<float(float)>& f) {
    PointRotation _lr{lr}, _rt{rt};
    return _lr.multiply_member_data(1-f(percentaje)) + _rt.multiply_member_data(f(percentaje));
}