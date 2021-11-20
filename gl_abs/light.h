/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_LIGHT_H_
#define MOSHI3D_LIGHT_H_

#include "_aux.h"

class Light {
public:
    Light() = delete;
    Light(const Light& l) = delete;
    virtual ~Light() = 0;

    inline bool is_active(void) { return glIsEnabled(id); }
    inline void activate(bool t) { t ? glEnable(id) : glDisable(id); }

    void apply(void);
    inline void set_color_ambient(const Tupla4f& c) { color_ambient = c; }
    inline void set_color_diffuse(const Tupla4f& c) { color_diffuse = c; }
    inline void set_color_specular(const Tupla4f& c) { color_specular = c; }

    static int num_available_ids(void);
    static inline void enable_lighting(bool t) { t ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING); }
    static bool is_lighting_enabled(void) { return glIsEnabled(GL_LIGHTING); }

protected:
    GLenum id;
    Tupla4f position;
    Tupla4f color_ambient;
    Tupla4f color_diffuse;
    Tupla4f color_specular;

    Light(Tupla4f position, Tupla4f color_ambient={0, 0, 0, 1.0}, Tupla4f color_diffuse={1, 1, 1, 1.0}, Tupla4f color_specular={1, 1, 1, 1.0});
    void apply_light_color(void);
    void apply_light_position(void);

private:
    static std::vector<GLenum> ids_available;
    static std::vector<GLenum> ids_in_use;

    static void init_static_data(void);

    static GLenum get_new_id(void);
    static void free_id(GLenum id);
};

#endif /* MOSHI3D_LIGHT_H_ */