#include "rotation.h"

static constexpr float deg_rad_equiv = 180/M_PI;

void Rotation::normalize_variables(void) {
    if (polar_coordinates[0] >= 2*M_PI || polar_coordinates[0] <= -2*M_PI) {
        polar_coordinates[0] = fmod(polar_coordinates[0], 2*M_PI);
    }
    if (polar_coordinates[1] >= 2*M_PI || polar_coordinates[1] <= -2*M_PI) {
        polar_coordinates[1] = fmod(polar_coordinates[1], 2*M_PI);
    }
}

Rotation& Rotation::multiply_member_data(float val) {
    polar_coordinates = polar_coordinates * val;
    rotation_point = rotation_point * val;
    normalize_variables();
    return *this;
}

Rotation::Rotation(const Tupla2f& polar_coor)
:polar_coordinates{polar_coor}, rotation_point{Tupla3f{0,0,0}}
{
    normalize_variables();
}

Rotation::Rotation(const Tupla2f& polar_coor, const Tupla3f& rotation_point)
:polar_coordinates{polar_coor}, rotation_point{rotation_point}
{
   normalize_variables();
}

/* static methods */

void Rotation::apply(float angle_rad, const Tupla3f& rot_vec) {
    glRotatef(angle_rad*deg_rad_equiv, rot_vec[0], rot_vec[1], rot_vec[2]);
}

void Rotation::apply(const Tupla2f& polar_coor) {
    apply(polar_coor[0], {1,0,0});
    apply(polar_coor[1], {0,1,0});
}

void Rotation::apply(const Tupla2f& polar_coordinates, const Tupla3f& rotation_point) {
    const auto& p = rotation_point;
    glTranslatef(-p[0], -p[1], -p[2]);
    apply(polar_coordinates);
    glTranslatef(+p[0], +p[1], +p[2]);
}

/* end static methods */

void Rotation::set(const Tupla2f& polar_coor, const Tupla3f& rotation_point) {
    set(polar_coor);
    set(rotation_point);
}

void Rotation::set(const Tupla2f& polar_coordinates) {
    this->polar_coordinates = polar_coordinates;
    normalize_variables();
}

void Rotation::set(const Tupla3f& rotation_point) {
    this->rotation_point = rotation_point;
}

void Rotation::sum(const Tupla2f& polar_coor, const Tupla3f& rotation_point) {
    sum(polar_coor);
    sum(rotation_point);
}

void Rotation::sum(const Tupla2f& polar_coordinates) {
    this->polar_coordinates = this->polar_coordinates + polar_coordinates;
    normalize_variables();
}

void Rotation::sum(const Tupla3f& rotation_point) {
    this->rotation_point = this->rotation_point + rotation_point;
}

void Rotation::apply(void) const {
    Rotation::apply(polar_coordinates, rotation_point);
}

Rotation operator+(const Rotation& lr, const Rotation& rt) {
    Rotation ret{lr};
    ret.sum(rt.polar_coordinates, rt.rotation_point);
    return ret;
}

Rotation interpolation(Rotation lr, Rotation rt, float percentaje, const std::function<float(float)>& f) {
    return lr.multiply_member_data(1-f(percentaje)) + rt.multiply_member_data(f(percentaje));
}