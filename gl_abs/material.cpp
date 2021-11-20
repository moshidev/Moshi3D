#include "material.h"

Material Material::def;

Material::Material(Tupla4f diffuse, Tupla4f especular, Tupla4f ambient, float shiness)
:diffuse{diffuse}, especular{especular}, ambient{ambient}, shiness{shiness}
{   }

void Material::set_current(void) const {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat*)&ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat*)&diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat*)&ambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

const Material& Material::get_default(void) {
    return def;
}