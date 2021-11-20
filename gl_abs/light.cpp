#include <stdexcept>
#include "light.h"

Light::Light(Tupla4f position, Tupla4f color_ambient, Tupla4f color_diffuse, Tupla4f color_specular)
:position{position}, color_ambient{color_ambient}, color_diffuse{color_diffuse}, color_specular{color_specular}
{
    if (Light::num_available_ids() <= 0) {
        throw std::domain_error("At Light class Constructor: not enough free GL_LIGHTi IDs.");
    }
    id = Light::get_new_id();
}

Light::~Light() {
    glDisable(id);
    Light::free_id(id);
}

void Light::apply(void) {
    apply_light_color();
    apply_light_position();
}

void Light::apply_light_color(void) {
    glLightfv(id, GL_AMBIENT, (GLfloat*)&color_ambient);
    glLightfv(id, GL_DIFFUSE, (GLfloat*)&color_diffuse);
    glLightfv(id, GL_SPECULAR, (GLfloat*)&color_specular);
}

void Light::apply_light_position(void) {
    glLightfv(id, GL_POSITION, (GLfloat*)&position);
}

/*** static members ***/

std::vector<GLenum> Light::ids_available;
std::vector<GLenum> Light::ids_in_use;

void Light::init_static_data(void) {
    if (ids_in_use.empty() && ids_available.empty()) {
        int max_lights;
        glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
        for (int i = max_lights-1; i >= 0; i--) {
            ids_available.push_back(GL_LIGHT0+i);
        }
    }
}

int Light::num_available_ids(void) {
    init_static_data();
    return ids_available.size();
}

GLenum Light::get_new_id(void) {
    init_static_data();
    ids_in_use.push_back(ids_available.back());
    ids_available.pop_back();
    return ids_in_use.back();
}

void Light::free_id(GLenum id) {
    auto it = std::find(ids_in_use.begin(), ids_in_use.end(), id);
    if (it != ids_in_use.end()) {
        ids_available.push_back(*it);
        ids_in_use.erase(it);
    }
}
