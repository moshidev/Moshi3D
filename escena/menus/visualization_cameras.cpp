#include "visualization_cameras.h"
#include "escena.h"

bool VisualizationModeSelectionCameras::handler(Escena& e, unsigned char tecla, int x, int y) {
    switch(tecla)
    {
    case 'Q':
        std::cout << "\n +++ Salimos del submenú de iluminación +++ " << std::endl;
        parent->set_default_menu();
        parent->update(e, 0, x, y);
        break;
    default:
        if (tecla >= '0' && tecla <= '9') {
            Camera* c = e.get_camera(tecla-'0');
            if (c) {
                std::cout << "Activamos/Desactivamos la cámara número " << tecla << std::endl;
                e.set_camera(tecla-'0');
            }
            else {
                std::cout << "No existe la cámara con índice " << tecla << std::endl;
            }
        }
        else {
            std::cout << "[ 0-9 ] - Utilizar cámara" << std::endl;
            std::cout << "[ Q ] - Volver al menú anterior" << std::endl;
        }
        break;
    }

    return false;
}