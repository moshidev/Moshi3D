/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MENU_H_
#define MOSHI3D_MENU_H_

#include <iostream>

class Escena;

class Menu {
protected:
    Menu* parent;
    Menu* current_menu;
    Menu(Menu* parent);

    virtual bool handler(Escena& e, unsigned char tecla, int x, int y) = 0;
    
public:
    bool update(Escena& e, unsigned char tecla, int x, int y);
    inline void set_default_menu(void) { current_menu = this; };
};

#endif /* MOSHI3D_MENU_H_ */