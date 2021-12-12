/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MENUS_MANUAL_H_
#define MOSHI3D_MENUS_MANUAL_H_

#include "menu.h"

class Manual : public Menu {
    int df {0};

protected:
    virtual bool handler(Escena& e, unsigned char tecla, int x, int y);

public:
    Manual(Menu* parent)
    : Menu{parent}
    {   }
};
#endif /* MOSHI3D_MENUS_MANUAL_H_ */