#include "menu.h"

Menu::Menu(Menu* parent)
: parent{parent}, current_menu{this}
{   }

bool Menu::update(Escena& e, unsigned char tecla, int x, int y) {
    if (current_menu == this) {
        return handler(e, tecla, x, y);
    }
    else {
        return current_menu->update(e, tecla, x, y);
    }
}