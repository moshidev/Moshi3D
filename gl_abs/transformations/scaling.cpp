#include "scaling.h"

Scaling::Scaling(const Tupla3f& factor)
:scale_factor_val{factor}
{   }

void Scaling::apply(const Tupla3f& factor) {
    glScalef(factor[0], factor[1], factor[2]);
}

void Scaling::set(const Tupla3f& factor) {
    this->scale_factor_val = factor;
}

void Scaling::mul(const Tupla3f& factor) {
    this->scale_factor_val(0) *= factor(0);
    this->scale_factor_val(1) *= factor(1);
    this->scale_factor_val(2) *= factor(2);
}

void Scaling::apply(void) const {
    Scaling::apply(scale_factor_val);
}

Scaling& Scaling::multiply_member_data(float val) {
    scale_factor_val = scale_factor_val * val;
    return *this;
}

Scaling operator+(const Scaling& ls, const Scaling& rs) {
    Scaling ret{ls};
    ret.scale_factor_val = ls.scale_factor_val + rs.scale_factor_val;
    return ret;
}

Scaling operator-(const Scaling& ls, const Scaling& rs) {
    Scaling ret{ls};
    ret.scale_factor_val = ls.scale_factor_val - rs.scale_factor_val;
    return ret;
}

Scaling interpolation(const Scaling& ls, const Scaling& rs, float percentaje, const std::function<float(float)>& f) {
    Scaling lls{ls}, rrs{rs};
    return lls.multiply_member_data(1-f(percentaje)) + rrs.multiply_member_data(f(percentaje));
}