#include "escena.h"
#include "_aux.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "mesh.h" // objetos: Cubo y otros....
#include <vector>
#include "translation.h"
#include "rotation.h"
#include "chipmunk.h"
#include "room.h"
#include "rectangle.h"
#include "camera.h"

Escena::Escena()
{
    renderer = &buffered_renderer;
    front_plane = 50.0;
    back_plane = 2000.0;

    ejes.changeAxisSize(5000);

    cubo = new Cube();
    tetraedro = new Tetrahedron();
    lata = new RevolutionObject("resources/lata-pcue.ply", 40);
    lata_x = new RevolutionObject("resources/lata-pcueX.ply", 40, true, true, 0);
    lata_z = new RevolutionObject("resources/lata-pcueZ.ply", 40, true, true, 2);
    peon_blanco = new RevolutionObject("resources/peon.ply", 40);
    peon_negro = new RevolutionObject("resources/peon.ply", 40);
    necoarc = new ObjPLY("resources/necoarc.ply");
    cilindro = new Cylinder(5, 90, 1, 1);
    cono = new Cone(90, 180 , 1, 1);
    esfera = new Sphere(50, 50, 1);

    objeto_actual = lata_z;
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
    delete chipmunk;
    delete bouncy_ball;
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana,
// por tanto sí puede ejecutar ordenes de OpenGL) Principalmemnte, inicializa
// OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height)
{
    static Material blanco_difuso{{1, 1, 1, 1}, {0, 0, 0, 1}, {0.5, 0.5, 0.5, 1}, 64};  // src: http://devernay.free.fr/cours/opengl/materials.html
    static Material negro_brillo{{0, 0, 0, 1}, {0.1, 0.1, 0.1, 1}, {0, 0, 0, 1}, 128};
    glClearColor(1.0, 1.0, 1.0, 1.0); // se indica cual sera el color para
                                      // limpiar la ventana	(r,v,a,al)

    glEnable(GL_DEPTH_TEST); // se habilita el z-bufer

	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE); // <- the root of all evil
	glShadeModel(GL_SMOOTH);

    window_width = UI_window_width / 10;
    window_height = UI_window_height / 10;

    glViewport(0, 0, UI_window_width, UI_window_height);

    std::shared_ptr<Sphere> bball_sphere = std::make_shared<Sphere>(60, 60, 1);
    std::shared_ptr<PositionalLight> bball_light = std::make_shared<PositionalLight>(Tupla3f{0,0,0}, Tupla4f{1,1,1,1}, Tupla4f{0.8,0.8,0.2,1}, Tupla4f{0,0,0,0});
    lights.push_back(bball_light.get());
    tex_123 = std::make_shared<TextureObject>("resources/text-123.jpg");
    bball_sphere->set_material(blanco_difuso);
    bball_sphere->set_texture(tex_123);
    bball_sphere->enable_shaded_mode(true);
    bball_light->activate(true);
    //bball_light->set_color_ambient(Tupla4f{1,1,1,1});

    chipmunk = new Chipmunk();
    bouncy_ball = new BouncyBall(bball_sphere, bball_light);
    chipmunk->multiply_speed_factor(2);

    revobjects.push_back(lata);
    revobjects.push_back(lata_x);
    revobjects.push_back(lata_z);
    revobjects.push_back(cono);
    revobjects.push_back(peon_blanco);
    revobjects.push_back(peon_negro);
    revobjects.push_back(cilindro);
    revobjects.push_back(esfera);
    objects.push_back(cubo);
    objects.push_back(tetraedro);
    objects.push_back(necoarc);
    objects.insert(objects.end(), revobjects.begin(), revobjects.end());

    proj_final = std::make_unique<ProjFinal>();

    directional_light_0 = new DirectionalLight({M_PI_4/3, -M_PI_4/3});
    directional_light_1 = new DirectionalLight({M_PI, 0});
    directional_light_2 = new DirectionalLight({0, M_PI/2});
    directional_light_3 = new DirectionalLight({0, M_PI*3/2});
    positional_light_0 = new PositionalLight({0,0,0});
    directional_lights.push_back(directional_light_0);
    lights.insert(lights.begin(), directional_lights.begin(), directional_lights.end());

    for (auto l : lights) {
        l->activate(true);
    }

    camera_0 = std::make_unique<Camera>(Camera::kPerspective, window_width*2, window_height*2, front_plane, back_plane);
    camera_1 = std::make_unique<Camera>(Camera::kPerspective, window_width*4, window_height*4, front_plane, back_plane);
    camera_2 = std::make_unique<Camera>(Camera::kOrthographic, window_width*2, window_height*2, front_plane, back_plane);
    cameras.push_back(camera_0.get());
    cameras.push_back(camera_1.get());
    cameras.push_back(camera_2.get());

    for (auto c : cameras) {
        c->set_eye({200,200,400});
        c->set_at({0,0,0});
    }

    tex_wood = std::make_shared<TextureObject>("resources/text-madera.jpg");
    tex_cola_can = std::make_shared<TextureObject>("resources/text-lata-1.jpg");
    cubo->set_texture(tex_wood);

    peon_blanco->set_material(blanco_difuso);
    peon_negro->set_material(negro_brillo);

    Light::enable_lighting(true);
    this->render_shaded(true);

    cono->set_texture(tex_cola_can);
    lata->set_texture(tex_cola_can);

    menu.update(*this, 0, 0, 0);
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************
void Escena::dibujar()
{
    bool prev_light_status = Light::is_lighting_enabled();
    Light::enable_lighting(false);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cameras[current_camera]->observe();
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

    if (objeto_actual != nullptr) {
        Transformation::push_matrix();
            Translation::apply({0,4,0});
            objeto_actual->draw(*renderer);
        Transformation::pop_matrix();
    }

    if (new_scene_enabled) {
        proj_final->apply_lights();
        proj_final->draw(*renderer);
    }
    else {
        Transformation::push_matrix();
            Translation::apply({2,1,0});
            bouncy_ball->apply_lights();
            bouncy_ball->draw(*renderer);
            Translation::apply({0,-1,0});
            cubo->draw(*renderer);
        Transformation::pop_matrix();
        Transformation::push_matrix();
            Translation::apply({-2,0,0});
            Rotation::apply({0,M_PI_2*3/2,0});
            cono->draw(*renderer);
        Transformation::pop_matrix();
        chipmunk->draw(*renderer);

        Transformation::push_matrix();
            Translation::apply({0,0,-4});
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
            glPopMatrix();
        Transformation::pop_matrix();
    }
    
}

bool Escena::teclaPulsada(unsigned char tecla, int x, int y)
{
    return menu.update(*this, toupper(tecla), x, y);
}
//**************************************************************************

void Escena::teclaEspecial(int tecla1, int x, int y)
{
    float d = 12;
    switch (tecla1) {
    case GLUT_KEY_LEFT:
        cameras[current_camera]->displace_firstperson({-d, 0, 0});
        break;
    case GLUT_KEY_RIGHT:
        cameras[current_camera]->displace_firstperson({+d, 0, 0});
        break;
    case GLUT_KEY_UP:
        cameras[current_camera]->displace_firstperson({0, 0, +d});
        break;
    case GLUT_KEY_DOWN:
        cameras[current_camera]->displace_firstperson({0, 0, -d});
        break;
    case GLUT_KEY_F1:
        cameras[current_camera]->displace_firstperson({0, +d, 0});
        break;
    case GLUT_KEY_F2:
        cameras[current_camera]->displace_firstperson({0, -d, 0});
        break;
    case GLUT_KEY_PAGE_UP:
        cameras[current_camera]->zoom(1.2);
        cameras[current_camera]->project();
        break;
    case GLUT_KEY_PAGE_DOWN:
        cameras[current_camera]->zoom(1.0/1.2);
        cameras[current_camera]->project();
        break;
    }
    
}

void Escena::mouse_clicked(int button, int status, int x, int y) {
    constexpr int button_right = 0;
    constexpr int status_clicked = 0, status_released = 1;
    if (button == button_right) {
        if (status == status_clicked) {
            mouse_last_coordinates = Tupla2u{x, y};
        }
        else if (status == status_released) {
            if (!mouse_displaced_since_click) {
                select_object(x, y);
            }
            mouse_displaced_since_click = false;
        }
    }
}

void Escena::mouse_displaced(int x, int y) {
    mouse_displaced_since_click = true;
    float angle_x_axis = ((float)mouse_last_coordinates[1]-y)/window_height * M_PI_4 / 2;
    float angle_y_axis = ((float)mouse_last_coordinates[0]-x)/window_width * M_PI_4/ 2;
    cameras[current_camera]->rotate_eye(Tupla3f{angle_x_axis, angle_y_axis, 0});
    mouse_last_coordinates = Tupla2u{x, y};
}

void Escena::select_object(int x, int y) {
    
}

//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int new_width, int new_height)
{
    window_width = new_width / 10;
    window_height = new_height / 10;
    cameras[current_camera]->top = window_height/2;
    cameras[current_camera]->right = window_width/2;
    cameras[current_camera]->observe();
    cameras[current_camera]->project();
    
    glViewport(0, 0, new_width, new_height);
}

void Escena::animar_modelo_jerarquico(void) {
    if (chipmunk_aut_anim) {
        chipmunk->increment_animation_aut();
        bouncy_ball->increment_animation_aut();
        proj_final->increment_animation_aut();
    }
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

Camera* Escena::get_camera(int n) {
    if (n < cameras.size() && n >= 0) {
        return cameras[n];
    }
    return nullptr;
}

void Escena::set_camera(int n) {
    if (n < cameras.size() && n >= 0) {
        current_camera = n;
    }
    cameras[current_camera]->project();
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
    auto f = [t] (Mesh3D& obj) { t ? obj.enable_polygon_modes(GL_POINT) : obj.disable_polygon_modes(GL_POINT); };
    chipmunk->apply_to_meshes(f);
    bouncy_ball->apply_to_meshes(f);
    proj_final->apply_to_meshes(f);
}

void Escena::render_lines(bool t) {
    enable_polygon_mode(t, objects, GL_LINE);
    auto f = [t] (Mesh3D& obj) { t ? obj.enable_polygon_modes(GL_LINE) : obj.disable_polygon_modes(GL_LINE); };
    chipmunk->apply_to_meshes(f);
    bouncy_ball->apply_to_meshes(f);
    proj_final->apply_to_meshes(f);
}

void Escena::render_solid(bool t) {
    enable_polygon_mode(t, objects, GL_FILL);
    auto f = [t] (Mesh3D& obj) { t ? obj.enable_polygon_modes(GL_FILL) : obj.disable_polygon_modes(GL_FILL); };
    chipmunk->apply_to_meshes(f);
    bouncy_ball->apply_to_meshes(f);
    proj_final->apply_to_meshes(f);
}

void Escena::render_chess(bool t) {
    for (auto obj : objects) {
        obj->enable_chess_mode(t);
    }
    auto f = [t] (Mesh3D& obj) { obj.enable_chess_mode(t); };
    chipmunk->apply_to_meshes(f);
    bouncy_ball->apply_to_meshes(f);
    proj_final->apply_to_meshes(f);
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
    auto f = [t] (Mesh3D& obj) { obj.enable_shaded_mode(t); };
    chipmunk->apply_to_meshes(f);
    bouncy_ball->apply_to_meshes(f);
    proj_final->apply_to_meshes(f);
}