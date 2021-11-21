#include "escena.h"
#include "menu.h"

Menu::Menu()
:current_menu{&Menu::mainmenu}
{}

bool Menu::update(Escena& e, unsigned char tecla, int x, int y) {
    return (this->*current_menu)(e, tecla, x, y);
}

bool Menu::mainmenu(Escena& e, unsigned char tecla, int x, int y) {
    switch (tecla)
    {
    case 'O':
        std::cout << "Entramos al menú selección de objeto" << std::endl;
        current_menu = &Menu::object_selection;
        break;
    case 'V':
        std::cout << "Entramos al menú selección de modo de visualización" << std::endl;
        current_menu = &Menu::visualization_mode_selection;
        break;
    case 'D':
        std::cout << "Entramos al menú selección de modo de dibujado" << std::endl;
        current_menu = &Menu::render_mode_selection;
        break;
    case 'Q':
        std::cout << "Presionada la letra Q -> finalizamos programa" << std::endl;
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

bool Menu::object_selection(Escena& e, unsigned char tecla, int x, int y) {
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
        current_menu = &Menu::mainmenu;
        break;
    default:
        std::cout << "Opciones disponibles:\n";
        std::cout << "'C': Visualizamos/ocultamos el cubo.\n";
        std::cout << "'T': Visualizamos/ocultamos el tetraedro.\n";
        std::cout << "'Q': Volvemos al menú principal." << std::endl;
        submenu_lights.update(e, tecla, x, y);
        break;
    }

    return false;
}

bool Menu::visualization_mode_selection(Escena& e, unsigned char tecla, int x, int y) {
    switch (tecla)
    {
    case 'P':
        std::cout << "Activamos/desactivamos visualización en modo puntos" << std::endl;
        e.render_points(!e.is_rendering_points());
        break;
    case 'L':
        std::cout << "Activamos/desactivamos visualización en modo líneas" << std::endl;
        e.render_lines(!e.is_rendering_lines());
        break;
    case 'S':
        std::cout << "Activamos/desactivamos visualización en modo sólido" << std::endl;
        e.render_solid(!e.is_rendering_solid());
        break;
    case 'A':
        std::cout << "Activamos/desactivamos visualización en modo ajedrez" << std::endl;
        e.render_chess(!e.is_rendering_chess());
        break;
    case 'T':
        std::cout << "Habilitamos la visualización de tapas" << std::endl;
        e.render_covers(true);
        break;
    case 'G':
        std::cout << "Deshabilitamos la visualización de tapas" << std::endl;
        e.render_covers(false);
        break;
    case 'O':
        std::cout << "Activamos/desactivamos el sombreado" << std::endl;
        Light::enable_lighting(true);
        e.render_shaded(!e.is_rendering_shaded());
        break;
    case 'I':
        std::cout << "Activamos/desactivamos la iluminación" << std::endl;
        Light::enable_lighting(!Light::is_lighting_enabled());
        break;
    case 'Z':
        std::cout << "Activamos GL_SMOOTH" << std::endl;
        glShadeModel(GL_SMOOTH);
        break;
    case 'X':
        std::cout << "Activamos GL_FLAT" << std::endl;
        glShadeModel(GL_FLAT);
        break;
    case 'C':
        std::cout << "Activamos visualización RGB si el objeto lo soporta" << std::endl;
        std::cout << "SIN IMPLEMENTAR" << std::endl;
        break;
    case 'Q':
        std::cout << "Salimos del modo selección de modo de visualización" << std::endl;
        current_menu = &Menu::mainmenu;
        break;
    default:
        std::cout << "Opciones disponibles:\n";
        std::cout << "'P': Activamos/desactivamos visualización en modo puntos.\n";
        std::cout << "'L': Activamos/desactivamos visualización en modo líneas.\n";
        std::cout << "'S': Activamos/desactivamos visualización en modo sólido.\n";
        std::cout << "'A': Activamos/desactivamos visualización en modo ajedrez.\n";
        std::cout << "'O': Activamos/desactivamos visualización en modo sombreado.\n";
        std::cout << "'I': Activamos/desactivamos la iluminación.\n";
        std::cout << "'C': Activamos visualización RGB si el objeto lo soporta.\n";
        std::cout << "'T': Habilitamos la visualización de tapas.\n";
        std::cout << "'G': Deshabilitamos la visualización de tapas.\n";
        std::cout << "'Q': Volvemos al menú principal." << std::endl;
        break;
    }

    return false;
}

bool Menu::render_mode_selection(Escena& e, unsigned char tecla, int x, int y) {
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
        current_menu = &Menu::mainmenu;
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