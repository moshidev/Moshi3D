/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_SUBMENU_LIGHTS_H_
#define MOSHI3D_SUBMENU_LIGHTS_H_

class Escena;
class DirectionalLight;

class SubmenuLuces {
    bool main_select_lights(Escena& e, unsigned char tecla, int x, int y);
    bool modify_alpha(Escena& e, unsigned char tecla, int x, int y);
    bool modify_beta(Escena& e, unsigned char tecla, int x, int y);

    DirectionalLight* last_directional_light{nullptr};
    bool (SubmenuLuces::*current_menu)(Escena& e, unsigned char tecla, int x, int y);
public:
    SubmenuLuces();

    bool update(Escena& e, unsigned char tecla, int x, int y);
};

#endif /* MOSHI3D_SUBMENU_LIGHTS_H_ */