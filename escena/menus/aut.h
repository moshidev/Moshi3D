/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MENUS_AUT_H_
#define MOSHI3D_MENUS_AUT_H_

#include "menu.h"

class Aut : public Menu {
    int df {0};

protected:
    virtual bool handler(Escena& e, unsigned char tecla, int x, int y);

public:
    Aut(Menu* parent)
    : Menu{parent}
    {   }
};
#endif /* MOSHI3D_MENUS_AUT_H_ */