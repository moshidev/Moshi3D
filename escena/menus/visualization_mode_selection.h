/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MENUS_VISUALIZATION_MODE_SELECTION_H_
#define MOSHI3D_MENUS_VISUALIZATION_MODE_SELECTION_H_

#include "visualization_ilumination.h"
#include "menu.h"

class VisualizationModeSelection : public Menu {
    VisualizationModeSelectionIlumination ilumination;

protected:
    virtual bool handler(Escena& e, unsigned char tecla, int x, int y);

public:
    VisualizationModeSelection(Menu* parent)
    : Menu{parent}, ilumination{this}
    {   }
};

#endif /* MOSHI3D_MENUS_VISUALIZATION_MODE_SELECTION_H_ */