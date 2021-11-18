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

    void enable(void);
    void disable(void);
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

    //Light(Tupla4f position, Tupla4f color_ambient={0.25, 0.5, 0.75, 1}, Tupla4f color_diffuse={0.75, 0.25, 0.5, 1}, Tupla4f color_specular={0.5, 0.75, 0.25, 1});
    Light(Tupla4f position, Tupla4f color_ambient={0, 0, 0, 1}, Tupla4f color_diffuse={1, 1, 1, 1}, Tupla4f color_specular={1, 1, 1, 1});
    void set_light_color(void);
    void set_light_position(void);

private:
    static std::vector<GLenum> ids_available;
    static std::vector<GLenum> ids_in_use;

    static void init_static_data(void);

    static GLenum get_new_id(void);
    static void free_id(GLenum id);
};

#endif /* MOSHI3D_LIGHT_H_ */