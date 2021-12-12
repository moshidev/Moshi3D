/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MENUS_RENDER_MODE_SELECTION_H_
#define MOSHI3D_MENUS_RENDER_MODE_SELECTION_H_

#include "menu.h"

class RenderModeSelection : public Menu {
protected:
    virtual bool handler(Escena& e, unsigned char tecla, int x, int y);

public:
    RenderModeSelection(Menu* parent)
    : Menu{parent}
    {   }
};

#endif /* MOSHI3D_MENUS_RENDER_MODE_SELECTION_H_ */