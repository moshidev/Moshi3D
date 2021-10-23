/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_COLOR_H_
#define MOSHI3D_COLOR_H_

#include "_aux.h"

class Mesh3D;
class Cube;
class Tetrahedron;

#define PC_BLACK Tupla3f{0,0,0}
#define PC_RED   Tupla3f{1,0,0}
#define PC_GREEN Tupla3f{0,1,0}

class Color {
    std::vector<Tupla3f> color;
    GLuint color_VBO_id {0};
    GLuint shade_mode {GL_SMOOTH};

    void update_VBO(void);
public:
    /**
     * @brief returns a GL_ELEMENT_ARRAY_BUFFER id with the data inside color. The first call
     * to this function will allocate a new VBO for this data.
     * @warning the VBO_id returned should never be deallocated or modified.
     */
    GLuint get_VBO_id(void);
    inline const GLvoid* get_data(void) const { return color.data(); }

    const GLuint get_shade_mode(void) const { return shade_mode; }

    void init(const Cube& c);
    void init(const Tetrahedron& t);

    void set_chess(const Mesh3D& m, const Tupla3f& color_a=PC_RED, const Tupla3f& color_b=PC_GREEN);
    void set_plain(const Mesh3D& m, const Tupla3f& color_a=PC_BLACK);

    void set_rgb(const Cube& c);
};

#undef PC_BLACK
#undef PC_RED
#undef PC_GREEN

#endif /* MOSHI3D_COLOR_H_ */