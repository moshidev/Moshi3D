/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_MENUS_MAIN_MENU_H_
#define MOSHI3D_MENUS_MAIN_MENU_H_

#include "menu.h"
#include "visualization_mode_selection.h"
#include "render_mode_selection.h"
#include "object_selection.h"
#include "manual.h"

class MainMenu : public Menu {
    VisualizationModeSelection visual;
    RenderModeSelection render;
    ObjectSelection object;
    Manual manual;

protected:
    virtual bool handler(Escena& e, unsigned char tecla, int x, int y);

public:
    MainMenu()
    : Menu{this}, visual{this}, render{this}, object{this}, manual{this}
    {   }
};

#endif /* MOSHI3D_MENUS_MAIN_MENU_H_ */