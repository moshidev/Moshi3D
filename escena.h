#ifndef _ESCENA_H
#define _ESCENA_H

#include "cubo.h"
#include "ejes.h"
#include "malla.h"
#include "tetraedro.h"

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
    Cubo *cubo {nullptr};           
    Tetraedro *tetraedro {nullptr}; 

  public:
    Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int new_width, int new_height);

    void dibujar();

    bool teclaPulsada(unsigned char tecla1, int x, int y);
    void teclaEspecial(int tecla1, int x, int y);
};

#endif /* _ESCENA_H */