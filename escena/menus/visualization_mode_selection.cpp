#include "visualization_mode_selection.h"
#include "escena.h"

bool VisualizationModeSelection::handler(Escena& e, unsigned char tecla, int x, int y) {
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
        if (Light::is_lighting_enabled()) {
            std::cout << "\n +++ Entramos al submenú de iluminación +++ " << std::endl;
            current_menu = &ilumination;
            current_menu->update(e, 0, x, y);
        }
        break;
    case 'Z':
        std::cout << "Activamos GL_SMOOTH" << std::endl;
        glShadeModel(GL_SMOOTH);
        break;
    case 'X':
        std::cout << "Activamos GL_FLAT" << std::endl;
        glShadeModel(GL_FLAT);
        break;
    case 'Q':
        std::cout << "\n +++ Salimos del modo selección de modo de visualización +++ " << std::endl;
        parent->set_default_menu();
        parent->update(e, 0, x, y);
        break;
    default:
        std::cout << "Opciones disponibles:\n";
        std::cout << "[ P ] - Activamos/desactivamos visualización en modo puntos.\n";
        std::cout << "[ L ] - Activamos/desactivamos visualización en modo líneas.\n";
        std::cout << "[ S ] - Activamos/desactivamos visualización en modo sólido.\n";
        std::cout << "[ A ] - Activamos/desactivamos visualización en modo ajedrez.\n";
        std::cout << "[ O ] - Activamos/desactivamos visualización en modo sombreado.\n";
        std::cout << "[ I ] - Activamos/desactivamos la iluminación.\n";
        std::cout << "[ C ] - Activamos visualización RGB si el objeto lo soporta.\n";
        std::cout << "[ T ] - Habilitamos la visualización de tapas.\n";
        std::cout << "[ G ] - Deshabilitamos la visualización de tapas.\n";
        std::cout << "[ Q ] - Volvemos al menú principal." << std::endl;
        break;
    }

    return false;
}