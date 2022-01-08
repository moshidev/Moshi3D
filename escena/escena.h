#ifndef _ESCENA_H
#define _ESCENA_H

#include "cube.h"
#include "main_menu.h"
#include "ejes.h"
#include "mesh.h"
#include "tetrahedron.h"
#include "revolution_object.h"
#include "chipmunk.h"
#include "bouncy_ball.h"
#include "cylinder.h"
#include "cone.h"
#include "sphere.h"
#include "objply.h"
#include "renderer.h"
#include "renderer_immediate.h"
#include "renderer_buffered.h"
#include "directional_light.h"
#include "positional_light.h"
#include "camera.h"
#include <vector>

class Escena {

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat window_width;
    GLfloat window_height;
    GLfloat front_plane;
    GLfloat back_plane;

    std::unique_ptr<Camera> camera_0;
    std::unique_ptr<Camera> camera_1;
    std::unique_ptr<Camera> camera_2;
    std::vector<Camera*> cameras;
    int current_camera {0};

    Tupla2u mouse_last_coordinates {0,0};
    bool mouse_displaced_since_click {false};

    void clear_window();

    // Objetos de la escena
    Ejes ejes;
    Cube* cubo {nullptr};           
    Tetrahedron* tetraedro {nullptr};
    RevolutionObject* lata {nullptr};
    RevolutionObject* lata_x {nullptr};
    RevolutionObject* lata_z {nullptr};
    RevolutionObject* peon_blanco {nullptr};
    RevolutionObject* peon_negro {nullptr};
    Cylinder* cilindro {nullptr};
    Cone* cono {nullptr};
    Sphere* esfera {nullptr};
    ObjPLY* necoarc {nullptr};
    Mesh3D* objeto_actual {nullptr};
    Chipmunk* chipmunk {nullptr};
    bool chipmunk_aut_anim {false};
    BouncyBall* bouncy_ball {nullptr};
    std::shared_ptr<TextureObject> tex_123;
    std::shared_ptr<TextureObject> tex_wood;
    std::shared_ptr<TextureObject> tex_cola_can;

    // Renderizadores
    RendererImmediate immediate_renderer;
    RendererBuffered buffered_renderer;
    Renderer* renderer;

    MainMenu menu;

    // Luces
    DirectionalLight* directional_light_0 {nullptr};
    DirectionalLight* directional_light_1 {nullptr};
    DirectionalLight* directional_light_2 {nullptr};
    DirectionalLight* directional_light_3 {nullptr};
    PositionalLight* positional_light_0 {nullptr};

    // Almacenes de referencias a objetos de la escena
    std::vector<RevolutionObject*> revobjects;
    std::vector<Mesh3D*> objects;
    std::vector<Light*> lights;
    std::vector<DirectionalLight*> directional_lights;
  public:
    
    Escena();
    ~Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int new_width, int new_height);
    void animar_modelo_jerarquico(void);
    inline Chipmunk* get_chipmunk(void) { return chipmunk; }
    inline void set_chipmunk_automatic_animation(bool t) { chipmunk_aut_anim = t; }

    void dibujar();

    inline void set_buffered_draw(void) { renderer = &buffered_renderer; }
    inline void set_immediate_draw(void) { renderer = &immediate_renderer; }

    void render_points(bool t);
    void render_lines(bool t);
    void render_solid(bool t);
    void render_chess(bool t);
    void render_shaded(bool t);

    inline bool is_rendering_points(void) { return objeto_actual->get_polygon_modes().find(GL_POINT) != objeto_actual->get_polygon_modes().end();}
    inline bool is_rendering_lines(void) { return objeto_actual->get_polygon_modes().find(GL_LINE) != objeto_actual->get_polygon_modes().end();}
    inline bool is_rendering_solid(void) { return objeto_actual->get_polygon_modes().find(GL_FILL) != objeto_actual->get_polygon_modes().end();}
    inline bool is_rendering_chess(void) { return objeto_actual->is_chess_mode_enabled(); }
    inline bool is_rendering_shaded(void) { return objeto_actual->is_shade_mode_enabled(); }

    inline void enable_cube(bool t) { objeto_actual = t ? cubo : nullptr; }
    inline void enable_tetrahedron(bool t) { objeto_actual = t ? tetraedro : nullptr; }

    inline bool is_cube_enabled(void) { return cubo != nullptr && cubo == objeto_actual; }
    inline bool is_tetrahedron_enabled(void) { return tetraedro != nullptr && tetraedro == objeto_actual; }

    void render_covers(bool t);
    
    Light* get_light(int n);
    DirectionalLight* get_directional_light(int n);

    Camera* get_camera(int n);
    void set_camera(int n);

    bool teclaPulsada(unsigned char tecla1, int x, int y);
    void teclaEspecial(int tecla1, int x, int y);
    void mouse_clicked(int button, int status, int x, int y);
    void mouse_displaced(int x, int y);
};

#endif /* _ESCENA_H */