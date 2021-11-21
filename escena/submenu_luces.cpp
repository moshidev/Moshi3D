#include "submenu_luces.h"
#include "escena.h"
#include <iostream>
#include <vector>

SubmenuLuces::SubmenuLuces()
:current_menu{&SubmenuLuces::main_select_lights}
{   }

bool SubmenuLuces::update(Escena& e, unsigned char tecla, int x, int y) {
    return (this->*current_menu)(e, tecla, x, y);
}

bool SubmenuLuces::main_select_lights(Escena& e, unsigned char tecla, int x, int y) {
    switch(tecla) {
    case 'A':
        if (last_directional_light) {
            std::cout << "Podemos modificar ahora alpha con las teclas '<' y '>'" << std::endl;
            current_menu = &SubmenuLuces::modify_alpha;
        }
        else {
            std::cout << "La última luz pulsada no es direccional" << std::endl;
        }
        break;
    case 'B':
        if (last_directional_light) {
            std::cout << "Podemos modificar ahora beta con las teclas '<' y '>'" << std::endl;
            current_menu = &SubmenuLuces::modify_beta;
        }
        else {
            std::cout << "La última luz pulsada no es direccional" << std::endl;
        }
        break;
    default:
        if (tecla >= '0' && tecla <= '9') {
            Light* l = e.get_light(tecla-'0');
            if (l) {
                std::cout << "Activamos/Desactivamos la luz número " << tecla << std::endl;
                l->activate(!l->is_active());
                last_directional_light = e.get_directional_light(tecla-'0');
                if (last_directional_light) {
                    std::cout << "(es direccional)" << std::endl;
                }
            }
            else {
                std::cout << "No existe la luz con índice " << tecla << std::endl;
            }
        }
        else {
            std::cout << "[0-9]: Activar/Desactivar luz" << std::endl;
            std::cout << "A: Modificar alpha (si la luz seleccionada con anterioridad es direccional)" << std::endl;
            std::cout << "B: Modificar beta (si la luz seleccionada con anterioridad es direccional)" << std::endl;
        }
        break;
    }

    return true;
}

bool SubmenuLuces::modify_alpha(Escena& e, unsigned char tecla, int x, int y) {
    switch (tecla)
    {
    case '<':
        last_directional_light->increment_alpha(-M_PI_4/8);
        break;
    case '>':
        last_directional_light->increment_alpha(+M_PI_4/8);
        break;
    default:
        current_menu = &SubmenuLuces::main_select_lights;
        return main_select_lights(e, tecla, x, y);
    }
    return true;
}

bool SubmenuLuces::modify_beta(Escena& e, unsigned char tecla, int x, int y) {
    switch (tecla)
    {
    case '<':
        last_directional_light->increment_beta(-M_PI_4/8);
        break;
    case '>':
        last_directional_light->increment_beta(+M_PI_4/8);
        break;
    default:
        current_menu = &SubmenuLuces::main_select_lights;
        return main_select_lights(e, tecla, x, y);
    }
    return true;
}