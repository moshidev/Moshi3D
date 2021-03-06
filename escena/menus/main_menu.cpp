#include "main_menu.h"
#include "escena.h"

bool MainMenu::handler(Escena& e, unsigned char tecla, int x, int y) {
    switch (tecla)
    {
    case 'O':
        std::cout << "\n +++ Entramos al menú selección de objeto +++ " << std::endl;
        current_menu = &object;
        current_menu->update(e, 0, x, y);
        break;
    case 'V':
        std::cout << "\n +++ Entramos al menú selección de modo de visualización +++ " << std::endl;
        current_menu = &visual;
        current_menu->update(e, 0, x, y);
        break;
    case 'D':
        std::cout << "\n +++ Entramos al menú selección de modo de dibujado +++ " << std::endl;
        current_menu = &render;
        current_menu->update(e, 0, x, y);
        break;
    case 'M':
        std::cout << "\n +++ Entramos al menú animación manual +++ " << std::endl;
        e.set_chipmunk_automatic_animation(false);
        current_menu = &manual;
        current_menu->update(e, 0, x, y);
        break;
    case 'A':
        std::cout << "Activamos animación automática." << std::endl;
        e.set_chipmunk_automatic_animation(true);
        current_menu = &aut;
        current_menu->update(e, 0, x, y);
        break;
    case 'Q':
        std::cout << "\n +++ Presionada la letra Q -> finalizamos programa +++ " << std::endl;
        return true;
        break;
    default:
        std::cout << "Opciones disponibles:\n";
        std::cout << "[ O ] - Menú selección de objeto.\n";
        std::cout << "[ V ] - Menú selección de modo de visualización.\n";
        std::cout << "[ D ] - Menú selección de modo de dibujado.\n";
        std::cout << "[ M ] - Menú selección animación manual.\n";
        std::cout << "[ A ] - Menú selección animación automática.\n";
        std::cout << "[ Q ] - Salimos del programa." << std::endl;
        break;
    }

    return false;
}