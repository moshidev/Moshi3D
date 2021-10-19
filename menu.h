/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MENU_H_
#define MOSHI3D_MENU_H_

class Escena;

class Menu {
    bool (Menu::*current_menu)(Escena& e, unsigned char tecla, int x, int y);

    bool menu_main(Escena& e, unsigned char tecla, int x, int y);
    bool menu_object_selection(Escena& e, unsigned char tecla, int x, int y);
    bool menu_visualization_mode_selection(Escena& e, unsigned char tecla, int x, int y);
    bool menu_render_mode_selection(Escena& e, unsigned char tecla, int x, int y);

public:
    Menu();

    bool update(Escena& e, unsigned char tecla, int x, int y);
};

#endif /* MOSHI3D_MENU_H_ */