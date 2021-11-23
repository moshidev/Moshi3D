#include "translation.h"

Translation::Translation(const Tupla3f& t)
:translation{t}
{   }

void Translation::set(const Tupla3f& t) {
    translation = t;
}

void Translation::sum(const Tupla3f& t) {
    translation = translation + t;
}

void Translation::apply(void) const {
    glTranslatef(translation[0], translation[1], translation[2]);
}

Translation Translation::get_sum(const Tupla3f& t) const {
    Translation obj(*this);
    obj.sum(t);
    return obj;
}