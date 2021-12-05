#include "rotation.h"

void Rotation::normalize_variables(void) {

}

Rotation::Rotation(const Tupla2f& polar_coor)
:polar_coordinates{polar_coor}, rotation_point{{0,0,0}}
{
    normalize_variables();
}

Rotation::Rotation(const Tupla2f& polar_coor, const Tupla3f& rotation_point)
:polar_coordinates{polar_coor}, rotation_point{rotation_point}
{
   normalize_variables();
}

void Rotation::apply(float angle_rad, const Tupla3f& rot_vec) {

}

void Rotation::apply(const Tupla2f& polar_coor) {
    
}

void Rotation::set(const Tupla2f& polar_coor, const Tupla3f& rotation_point) {
    set(polar_coor);
    set(rotation_point);
}

void Rotation::set(const Tupla2f& polar_coor) {

}

void Rotation::set(const Tupla3f& rotation_point) {

}

void Rotation::sum(const Tupla2f& polar_coor, const Tupla3f& rotation_point) {
    set(polar_coor);
    set(rotation_point);
}

void Rotation::sum(const Tupla2f& polar_coor) {

}

void Rotation::sum(const Tupla3f& rotation_point) {

}

void Rotation::apply(void) const {
    Rotation::apply(polar_coordinates, rotation_point);
}

Rotation operator+(const Rotation& lr, const Rotation& rt) {
    Rotation ret{lr};
    ret.sum(rt.polar_coordinates, rt.rotation_point);
    return ret;
}

Rotation interpolation(const Rotation& lr, const Rotation& rt, float percentaje, const std::function<float(float)>& f) {

}