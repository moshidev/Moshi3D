#ifndef _ESCENA_H
#define _ESCENA_H

#include "cube.h"
#include "menu.h"
#include "ejes.h"
#include "mesh.h"
#include "tetrahedron.h"
#include "revolution_object.h"
#include "cylinder.h"
#include "cone.h"
#include "sphere.h"
#include "objply.h"
#include "renderer.h"
#include "renderer_immediate.h"
#include "renderer_buffered.h"
#include <vector>

class Escena {
    // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat observer_distance;
    GLfloat observer_angle_x;
    GLfloat observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat window_width;
    GLfloat window_height;
    GLfloat front_plane;
    GLfloat back_plane;

    // Transformación de cámara
    void change_projection(const float ratio_xy);
    void change_observer();

    void clear_window();

    // Objetos de la escena
    Ejes ejes;
    Cube* cubo {nullptr};           
    Tetrahedron* tetraedro {nullptr};
    RevolutionObject* lata {nullptr};
    RevolutionObject* peon {nullptr};
    Cylinder* cilindro {nullptr};
    Cone* cono {nullptr};
    Sphere* esfera {nullptr};
    ObjPLY* necoarc {nullptr};
    Mesh3D* objeto_actual {nullptr};

    // Renderizadores
    RendererImmediate immediate_renderer;
    RendererBuffered buffered_renderer;
    Renderer* renderer;

    Menu menu;

    std::vector<RevolutionObject*> revobjects;
    std::vector<Mesh3D*> objects;
  public:
    
    Escena();
    ~Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int new_width, int new_height);

    void dibujar();

    inline void set_buffered_draw(void) { renderer = &buffered_renderer; }
    inline void set_immediate_draw(void) { renderer = &immediate_renderer; }

    void render_points(bool t);
    void render_lines(bool t);
    void render_solid(bool t);
    void render_chess(bool t);

    inline bool is_rendering_points(void) { return objeto_actual->get_polygon_modes().find(GL_POINT) != objeto_actual->get_polygon_modes().end();}
    inline bool is_rendering_lines(void) { return objeto_actual->get_polygon_modes().find(GL_LINE) != objeto_actual->get_polygon_modes().end();}
    inline bool is_rendering_solid(void) { return objeto_actual->get_polygon_modes().find(GL_FILL) != objeto_actual->get_polygon_modes().end();}
    inline bool is_rendering_chess(void) { return objeto_actual->is_chess_mode_enabled(); }

    inline void enable_cube(bool t) { objeto_actual = t ? cubo : nullptr; }
    inline void enable_tetrahedron(bool t) { objeto_actual = t ? tetraedro : nullptr; }

    inline bool is_cube_enabled(void) { return cubo != nullptr && cubo == objeto_actual; }
    inline bool is_tetrahedron_enabled(void) { return tetraedro != nullptr && tetraedro == objeto_actual; }

    void render_covers(bool t);

    bool teclaPulsada(unsigned char tecla1, int x, int y);
    void teclaEspecial(int tecla1, int x, int y);
};

#endif /* _ESCENA_H */