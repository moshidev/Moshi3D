#include "escena.h"
#include "_aux.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "mesh.h" // objetos: Cubo y otros....
#include <vector>
#include "translation.h"
#include "rotation.h"

Escena::Escena()
{
    renderer = &buffered_renderer;
    front_plane = 50.0;
    back_plane = 2000.0;
    observer_distance = 4 * front_plane;
    observer_angle_x = 0.0;
    observer_angle_y = 0.0;

    ejes.changeAxisSize(5000);

    cubo = new Cube();
    tetraedro = new Tetrahedron();
    lata = new RevolutionObject("resources/lata-pcue.ply", 40);
    peon_blanco = new RevolutionObject("resources/peon.ply", 40);
    peon_negro = new RevolutionObject("resources/peon.ply", 40);
    necoarc = new ObjPLY("resources/necoarc.ply");
    cilindro = new Cylinder(5, 90, 1, 1);
    cono = new Cone(5, 90, 1, 1);
    esfera = new Sphere(50, 50, 1);

    objeto_actual = cubo;
}

Escena::~Escena() {
    delete cubo;
    delete tetraedro;
    delete lata;
    delete peon_blanco;
    delete peon_negro;
    delete cilindro;
    delete necoarc;
    delete cono;
    delete esfera;
    delete directional_light_0;
    delete positional_light_0;
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana,
// por tanto sí puede ejecutar ordenes de OpenGL) Principalmemnte, inicializa
// OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height)
{
    static Material blanco_difuso{{1, 1, 1, 1}, {0, 0, 0, 1}, {0.5, 0.5, 0.5, 1}, 64};  // src: http://devernay.free.fr/cours/opengl/materials.html
    static Material negro_brillo{{0.1, 0.1, 0.1, 1}, {1, 1, 1, 1}, {0.5, 0.5, 0.5, 1}, 128};
    glClearColor(1.0, 1.0, 1.0, 1.0); // se indica cual sera el color para
                                      // limpiar la ventana	(r,v,a,al)

    glEnable(GL_DEPTH_TEST); // se habilita el z-bufer

	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE); // <- the root of all evil
	glShadeModel(GL_SMOOTH);

    window_width = UI_window_width / 10;
    window_height = UI_window_height / 10;

    change_projection(float(UI_window_width) / float(UI_window_height));
    glViewport(0, 0, UI_window_width, UI_window_height);

    revobjects.push_back(lata);
    revobjects.push_back(cono);
    revobjects.push_back(peon_blanco);
    revobjects.push_back(peon_negro);
    revobjects.push_back(cilindro);
    revobjects.push_back(esfera);
    objects.push_back(cubo);
    objects.push_back(tetraedro);
    objects.push_back(necoarc);
    objects.insert(objects.end(), revobjects.begin(), revobjects.end());

    directional_light_0 = new DirectionalLight({M_PI_4/3, -M_PI_4/3});
    positional_light_0 = new PositionalLight({0,0,0});
    directional_lights.push_back(directional_light_0);
    lights.push_back(positional_light_0);
    lights.insert(lights.begin(), directional_lights.begin(), directional_lights.end());

    for (auto l : lights) {
        l->activate(true);
    }
    peon_blanco->set_material(blanco_difuso);
    peon_negro->set_material(negro_brillo);
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
    DirectionalLight d({0,0}, {0,0,0,1}, {1,0,0,1}, {1,0,0,1});
    PositionalLight p({1,1,0}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1});
    Translation t({0, 4, 0});

    //hm.test_and_touch(0, *objeto_actual);

    bool prev_light_status = Light::is_lighting_enabled();
    Light::enable_lighting(false);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
    change_observer();
    ejes.draw();
    glScalef(50.0, 50.0, 50.0);

    glPointSize(10);
    glLineWidth(1.25);
    Light::enable_lighting(prev_light_status);

    for (auto l : lights) {
        if (l->is_active()) {
            l->apply();
        }
    }
    
    /*if (objeto_actual != nullptr) {
        glPushMatrix();
            t.apply();
            //r.apply();
            objeto_actual->draw(*renderer);
        glPopMatrix();
    }

    int i = 0;
    glPushMatrix();
        glTranslatef(0, 0, 0);
        for (auto o : revobjects) {
            glPushMatrix();
                glTranslatef(-5+i*2, 0, 0);
                o->draw(*renderer);
            glPopMatrix();
            i++;
        }
    glPopMatrix();

    i = 0;
    glPushMatrix();
        glTranslatef(0, 0, -3);
        for (auto o : objects) {
            glPushMatrix();
                glTranslatef(-5+i*3, 0, 0);
                o->draw(*renderer);
            glPopMatrix();
            i++;
        }
    glPopMatrix();*/
    static float time_point = 0;
    time_point += 0.1;
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
        //observer_distance /= 1.2;
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

Light* Escena::get_light(int n) {
    if (n < lights.size() && n >= 0) {
        return lights[n];
    }
    return nullptr;
}

DirectionalLight* Escena::get_directional_light(int n) {
    Light* l = get_light(n);
    if (l) {
        auto it = std::find(directional_lights.begin(), directional_lights.end(), l);
        if (it != directional_lights.end()) {
            return *it;
        }
    }
    return nullptr;
}

static void enable_polygon_mode(bool t, std::vector<Mesh3D*>& objects, int mode) {
    if (t) {
        for (auto obj : objects) {
            obj->enable_polygon_modes(mode);
        }
    }
    else {
        for (auto obj : objects) {
            obj->disable_polygon_modes(mode);
        }
    }
}

void Escena::render_points(bool t) {
    enable_polygon_mode(t, objects, GL_POINT);
}

void Escena::render_lines(bool t) {
    enable_polygon_mode(t, objects, GL_LINE);
}

void Escena::render_solid(bool t) {
    enable_polygon_mode(t, objects, GL_FILL);
}

void Escena::render_chess(bool t) {
    for (auto obj : objects) {
        obj->enable_chess_mode(t);
    }
}

void Escena::render_covers(bool t) {
    for (auto rv : revobjects) {
        rv->enable_covers_visibility(t);
    }   
}

void Escena::render_shaded(bool t) {
    for (auto obj : objects) {
        obj->enable_shaded_mode(t);
    }
}