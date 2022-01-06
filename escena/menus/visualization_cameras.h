/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MENUS_VISUALIZATION_MODE_SELECTION_CAMERASH_
#define MOSHI3D_MENUS_VISUALIZATION_MODE_SELECTION_CAMERASH_

#include "menu.h"

class VisualizationModeSelectionCameras : public Menu {

protected:
    virtual bool handler(Escena& e, unsigned char tecla, int x, int y);

public:
    VisualizationModeSelectionCameras(Menu* parent)
    : Menu{parent}
    {   }
};

#endif /* MOSHI3D_MENUS_VISUALIZATION_MODE_SELECTION_CAMERASH_ */