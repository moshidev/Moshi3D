#ifndef _ESCENA_H
#define _ESCENA_H

#include "cube.h"
#include "ejes.h"
#include "malla.h"
#include "tetraedro.h"
#include "renderer.h"
#include "immediate_renderer.h"
#include "buffered_renderer.h"

typedef enum { NADA, SELOBJETO, SELVISUALIZACION, SELDIBUJADO } menu;

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

    menu modoMenu = NADA;

    // Objetos de la escena
    Ejes ejes;
    Cube *cube {nullptr};           
    Tetraedro *tetrahedron {nullptr};
    Malla3D* objeto_actual {nullptr};

    // Renderizadores
    ImmediateRenderer immediate_renderer;
    BufferedRenderer buffered_renderer;
    Renderer* renderer;

  public:
    bool (*menu_actual)(Escena& e, unsigned char tecla, int x, int y);
    
    Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int new_width, int new_height);

    void dibujar();

    inline void set_buffered_draw(void) { renderer = &buffered_renderer; }
    inline void set_immediate_draw(void) { renderer = &immediate_renderer; }

    void render_points(bool t);
    void render_lines(bool t);
    void render_solid(bool t);
    void render_chess(bool t);

    inline void enable_cube(bool t) { objeto_actual = t ? cube : nullptr; }
    inline void enable_tetrahedron(bool t) { objeto_actual = t ? tetrahedron : nullptr; }

    inline bool is_cube_enabled(void) { return cube != nullptr && cube == objeto_actual; }
    inline bool is_tetrahedron_enabled(void) { return tetrahedron != nullptr && tetrahedron == objeto_actual; }

    bool teclaPulsada(unsigned char tecla1, int x, int y);
    void teclaEspecial(int tecla1, int x, int y);
};

#endif /* _ESCENA_H */