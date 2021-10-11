#include "escena.h"
#include "_aux.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "malla.h" // objetos: Cubo y otros....
#include "immediate_renderer.h"
#include "buffered_renderer.h"
#include "primitive_colorizer.h"

static bool menu_principal(Escena& e, unsigned char tecla, int x, int y);
static bool menu_seleccion_objeto(Escena& e, unsigned char tecla, int x, int y);
static bool menu_seleccion_modo_visualizacion(Escena& e, unsigned char tecla, int x, int y);
static bool menu_seleccion_modo_dibujado(Escena& e, unsigned char tecla, int x, int y);

Escena::Escena()
: menu_actual{menu_principal}, renderer{&immediate_renderer}
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
    glShadeModel(GL_FLAT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FLAT);
    
    if (objeto_actual != nullptr) {
        if (objeto_actual == cube) {    // TODO: hacer refactor de PrimitiveColorizer
            PrimitiveColorizer::chess(*(Cube*)objeto_actual);
        }
        else {
            PrimitiveColorizer::chess(*(Tetraedro*)objeto_actual);
        }
        objeto_actual->draw(renderer);
    }
}

bool menu_principal(Escena& e, unsigned char tecla, int x, int y) {
    switch (tecla)
    {
    case 'O':
        std::cout << "Entramos al menú selección de objeto" << std::endl;
        e.menu_actual = menu_seleccion_objeto;
        break;
    case 'V':
        std::cout << "Entramos al menú selección de modo de visualización" << std::endl;
        e.menu_actual = menu_seleccion_modo_visualizacion;
        break;
    case 'D':
        std::cout << "Entramos al menú selección de modo de dibujado" << std::endl;
        e.menu_actual = menu_seleccion_modo_dibujado;
        break;
    case 'Q':
        std::cout << "Presionada la letra Q -> programa finalizado" << std::endl;
        return true;
        break;
    default:
        std::cout << "Opciones disponibles:\n";
        std::cout << "'O': Menú selección de objeto.\n";
        std::cout << "'V': Menú selección de modo de visualización.\n";
        std::cout << "'D': Menú selección de modo de dibujado." << std::endl;
        break;
    }

    return false;
}

bool menu_seleccion_objeto(Escena& e, unsigned char tecla, int x, int y) {
    switch (tecla)
    {
    case 'C':
        std::cout << "Visualizamos/ocultamos el cubo" << std::endl;
        e.enable_cube(!e.is_cube_enabled());
        break;
    case 'T':
        std::cout << "Visualizamos/ocultamos el tetraedro" << std::endl;
        e.enable_tetrahedron(!e.is_tetrahedron_enabled());
        break;
    case 'Q':
        std::cout << "Salimos del modo selección de objeto" << std::endl;
        e.menu_actual = menu_principal;
        break;
    default:
        std::cout << "Opciones disponibles:\n";
        std::cout << "'C': Visualizamos/ocultamos el cubo.\n";
        std::cout << "'T': Visualizamos/ocultamos el tetraedro.\n";
        std::cout << "'Q': Volvemos al menú principal." << std::endl;
        break;
    }

    return false;
}

bool menu_seleccion_modo_visualizacion(Escena& e, unsigned char tecla, int x, int y) {
    std::cout << "Sin implementar!!!" << std::endl;
    e.menu_actual = menu_principal;
    return false;
}

bool menu_seleccion_modo_dibujado(Escena& e, unsigned char tecla, int x, int y) {
    switch (tecla)
    {
    case '1':
        std::cout << "Visualizamos objetos usando glDrawElements" << std::endl;
        e.set_immediate_draw();
        break;
    case '2':
        std::cout << "Visualizamos objetos usando VBOs" << std::endl;
        e.set_buffered_draw();
        break;
    case 'Q':
        std::cout << "Salimos del modo selección de objeto" << std::endl;
        e.menu_actual = menu_principal;
        break;
    default:
        std::cout << "Opciones disponibles:\n";
        std::cout << "'1': Visualizamos objetos usando glDrawElements.\n";
        std::cout << "'2': Visualizamos objetos usando VBOs.\n";
        std::cout << "'Q': Volvemos al menú principal." << std::endl;
        break;
    }

    return false;
}

bool Escena::teclaPulsada(unsigned char tecla, int x, int y)
{
    tecla = toupper(tecla);
    return menu_actual(*this, tecla, x, y);
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