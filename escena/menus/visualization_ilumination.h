/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MENUS_VISUALIZATION_MODE_SELECTION_ILUMINATIONH_
#define MOSHI3D_MENUS_VISUALIZATION_MODE_SELECTION_ILUMINATIONH_

#include "directional_light.h"
#include "menu.h"

class VisualizationModeSelectionIlumination : public Menu {
    bool modify_alpha(Escena& e, unsigned char tecla, int x, int y);
    bool modify_beta(Escena& e, unsigned char tecla, int x, int y);
    bool mainmenu(Escena& e, unsigned char tecla, int x, int y);
    
    DirectionalLight* last_directional_light{nullptr};
    bool (VisualizationModeSelectionIlumination::*current_submenu)(Escena& e, unsigned char tecla, int x, int y);

protected:
    virtual bool handler(Escena& e, unsigned char tecla, int x, int y);

public:
    VisualizationModeSelectionIlumination(Menu* parent)
    : Menu{parent}, current_submenu{&VisualizationModeSelectionIlumination::mainmenu}
    {   }
};

#endif /* MOSHI3D_MENUS_VISUALIZATION_MODE_SELECTION_ILUMINATIONH_ */