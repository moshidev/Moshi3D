#include "translation.h"

Translation::Translation(const Tupla3f& t)
:translation_val{t}
{   }

void Translation::apply(const Tupla3f& t) {
    glTranslatef(t[0], t[1], t[2]);
}

void Translation::set(const Tupla3f& t) {
    translation_val = t;
}

void Translation::sum(const Tupla3f& t) {
    translation_val = translation_val + t;
}

void Translation::apply(void) const {
    Translation::apply(translation_val);
}

Translation& Translation::multiply_member_data(float val) {
    translation_val = translation_val * val;
    return *this;
}

Translation operator+(const Translation& lt, const Translation& rt) {
    Translation ret{lt};
    ret.sum(rt.translation_val);
    return ret;
}

Translation operator-(const Translation& lt, const Translation& rt) {
    Translation ret{lt};
    ret.sum(-rt.translation_val);
    return ret;
}

Translation interpolation(const Translation& lt, const Translation& rt, float percentaje, const std::function<float(float)>& f) {
    return lt + (rt-lt).multiply_member_data(f(percentaje));
}