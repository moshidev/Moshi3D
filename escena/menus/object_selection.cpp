#include "object_selection.h"
#include "escena.h"

bool ObjectSelection::handler(Escena& e, unsigned char tecla, int x, int y) {
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
        std::cout << "\n +++ Salimos del modo selección de objeto +++ " << std::endl;
        parent->set_default_menu();
        parent->update(e, 0, x, y);
        break;
    default:
        std::cout << "Opciones disponibles:\n";
        std::cout << "[ C ] - Visualizamos/ocultamos el cubo.\n";
        std::cout << "[ T ] - Visualizamos/ocultamos el tetraedro.\n";
        std::cout << "[ Q ] - Volvemos al menú principal." << std::endl;
        break;
    }

    return false;
}