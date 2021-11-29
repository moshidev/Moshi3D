#include "scaling.h"

Scaling::Scaling(const Tupla3f& factor)
:factor{factor}
{   }

void Scaling::set(const Tupla3f& factor) {
    this->factor = factor;
}

void Scaling::mul(const Tupla3f& factor) {
    this->factor(0) *= factor(0);
    this->factor(1) *= factor(1);
    this->factor(2) *= factor(2);
}

void Scaling::apply(void) const {
    glScalef(factor(0), factor(1), factor(2));
}