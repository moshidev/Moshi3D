/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MENU_H_
#define MOSHI3D_MENU_H_

#include "submenu_luces.h"

class Escena;

class Menu {
    bool mainmenu(Escena& e, unsigned char tecla, int x, int y);
    bool object_selection(Escena& e, unsigned char tecla, int x, int y);
    bool visualization_mode_selection(Escena& e, unsigned char tecla, int x, int y);
    bool render_mode_selection(Escena& e, unsigned char tecla, int x, int y);

    SubmenuLuces submenu_lights;
    bool (Menu::*current_menu)(Escena& e, unsigned char tecla, int x, int y);
public:
    Menu();

    bool update(Escena& e, unsigned char tecla, int x, int y);
};

#endif /* MOSHI3D_MENU_H_ */