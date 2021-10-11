#include "escena.h"
#include "_aux.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "malla.h" // objetos: Cubo y otros....
#include "immediate_renderer.h"
#include "buffered_renderer.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    front_plane = 50.0;
    back_plane = 2000.0;
    observer_distance = 4 * front_plane;
    observer_angle_x = 0.0;
    observer_angle_y = 0.0;

    ejes.changeAxisSize(5000);

    cube = new Cube(100);
    tetrahedron = new Tetraedro(100);
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
    BufferedRenderer renderer;
    static int i = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
    change_observer();
    ejes.draw();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glShadeModel(GL_FLAT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FLAT);

    float colores[8*3];
    float chess[8*3];
    for (int i = 0; i < 8; i++) {
        colores[i*3] = 1.0 * (i & 0x1);
        colores[i*3+1] = 1.0 * ((i & 0x2) >> 1);
        colores[i*3+2] = 1.0 * ((i & 0x4) >> 2);
    }
    for (int i = 0; i < 8; i+=2) {
        chess[i*3] = 1;
        chess[i*3+1] = 0;
        chess[i*3+2] = 0;
        chess[i*3+3] = 0;
        chess[i*3+4] = 1;
        chess[i*3+5] = 0;
    }
    std::vector<Tupla3f> c;
    c.resize(8);
    for (int i = 0; i < 8; i++) {
        c[i] = {1.0 * (i & 0x1), 1.0 * ((i & 0x2) >> 1), 1.0 * ((i & 0x4) >> 2)};
    }
    std::swap(c[4], c[5]);
    std::swap(c[6], c[7]);
    
    cube->set_color_array(c);
    cube->draw(renderer);
    //tetrahedron->draw(renderer);
    
    //tetrahedron->draw(renderer);
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada(unsigned char tecla, int x, int y)
{
    
    return false;
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
