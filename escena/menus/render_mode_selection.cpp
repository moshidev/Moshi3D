#include "render_mode_selection.h"
#include "escena.h"

bool RenderModeSelection::handler(Escena& e, unsigned char tecla, int x, int y) {
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
        std::cout << "\n +++ Salimos del modo selección de objeto +++ " << std::endl;
        parent->set_default_menu();
        parent->update(e, 0, x, y);
        break;
    default:
        std::cout << "Opciones disponibles:\n";
        std::cout << "[ 1 ] - Visualizamos objetos usando glDrawElements.\n";
        std::cout << "[ 2 ] - Visualizamos objetos usando VBOs.\n";
        std::cout << "[ Q ] - Volvemos al menú principal." << std::endl;
        break;
    }

    return false;
}