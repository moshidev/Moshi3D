#include "escena.h"
#include "_aux.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "malla.h" // objetos: Cubo y otros....

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

    cubo = new Cubo(100);
    tetraedro = new Tetraedro(100);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
    change_observer();
    ejes.draw();
    //cubo->draw();
    //tetraedro->draw();

    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué
    // objeto se ha de visualizar y hacer cubo.draw()
    // o
    // tetraedro.draw()
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
    using namespace std;
    cout << "Tecla pulsada: '" << tecla << "'" << endl;
    bool salir = false;
    switch (toupper(tecla)) {
    case 'Q':
        if (modoMenu != NADA) {
            modoMenu = NADA;
        }
        else {
            salir = true;
        }
        break;
    case 'O':
        // ESTAMOS EN MODO SELECCION DE OBJETO
        modoMenu = SELOBJETO;
        break;
    case 'V':
        // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
        modoMenu = SELVISUALIZACION;
        break;
    case 'D':
        // ESTAMOS EN MODO SELECCION DE DIBUJADO
        modoMenu = SELDIBUJADO;
        break;
        // COMPLETAR con los diferentes opciones de teclado
    }
    return salir;
}
//**************************************************************************

void Escena::teclaEspecial(int tecla1, int x, int y)
{
    switch (tecla1) {
    case GLUT_KEY_LEFT:
        observer_angle_y--;
        break;
    case GLUT_KEY_RIGHT:
        observer_angle_y++;
        break;
    case GLUT_KEY_UP:
        observer_angle_x--;
        break;
    case GLUT_KEY_DOWN:
        observer_angle_x++;
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
