#include "escena.h"
#include "_aux.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "malla.h" // objetos: Cubo y otros....

Escena::Escena()
: renderer{&immediate_renderer}
{
    front_plane = 50.0;
    back_plane = 2000.0;
    observer_distance = 4 * front_plane;
    observer_angle_x = 0.0;
    observer_angle_y = 0.0;

    ejes.changeAxisSize(5000);

    cube = new Cube(100);
    tetrahedron = new Tetrahedron(100);
    cube->set_color_rgb_cube();
    objeto_actual = cube;
    // crear los objetos de la escena....
    // .......completar: ...
    // .....
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana,
// por tanto sí puede ejecutar ordenes de OpenGL) Principalmemnte, inicializa
// OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height)
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // se indica cual sera el color para
                                      // limpiar la ventana	(r,v,a,al)

    glEnable(GL_DEPTH_TEST); // se habilita el z-bufer

    window_width = UI_window_width / 10;
    window_height = UI_window_height / 10;

    change_projection(float(UI_window_width) / float(UI_window_height));
    glViewport(0, 0, UI_window_width, UI_window_height);
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
    static int i = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
    change_observer();
    ejes.draw();

    glShadeModel(GL_FLAT);
    glPointSize(10);
    
    if (objeto_actual != nullptr) {
        objeto_actual->draw(*renderer);
    }
}

bool Escena::teclaPulsada(unsigned char tecla, int x, int y)
{
    return menu.update(*this, toupper(tecla), x, y);
}
//**************************************************************************

void Escena::teclaEspecial(int tecla1, int x, int y)
{
    int mult = 4;
    switch (tecla1) {
    case GLUT_KEY_LEFT:
        observer_angle_y-=mult;
        break;
    case GLUT_KEY_RIGHT:
        observer_angle_y+=mult;
        break;
    case GLUT_KEY_UP:
        observer_angle_x-=mult;
        break;
    case GLUT_KEY_DOWN:
        observer_angle_x+=mult;
        break;
    case GLUT_KEY_PAGE_UP:
        observer_distance *= 1.2;
        break;
    case GLUT_KEY_PAGE_DOWN:
        observer_distance /= 1.2;
        break;
    }

    // std::cout << observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection(const float ratio_xy)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float wx = float(window_height) * ratio_xy;
    glFrustum(-wx, wx, -window_height, window_height, front_plane, back_plane);
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int new_width, int new_height)
{
    window_width = new_width / 10;
    window_height = new_height / 10;
    change_projection(float(new_height) / float(new_width));
    glViewport(0, 0, new_width, new_height);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -observer_distance);
    glRotatef(observer_angle_y, 0.0, 1.0, 0.0);
    glRotatef(observer_angle_x, 1.0, 0.0, 0.0);
}