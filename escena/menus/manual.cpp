#include "manual.h"
#include "escena.h"

static void decrement(Escena& e, int df) {
    switch (df)
    {
    case 0:
        e.get_chipmunk()->decrement_animation_man();
        break;
    case 1:
        e.get_chipmunk()->decrement_animation_man_body();
        break;
    case 2:
        e.get_chipmunk()->decrement_animation_man_ears();
        break;
    case 3:
        e.get_chipmunk()->decrement_animation_man_legs();
        break;
    case 4:
        e.get_chipmunk()->decrement_animation_man_tail();
        break;
    }
}

static void increment(Escena& e, int df) {
    switch (df)
    {
    case 0:
        e.get_chipmunk()->increment_animation_man();
        break;
    case 1:
        e.get_chipmunk()->increment_animation_man_body();
        break;
    case 2:
        e.get_chipmunk()->increment_animation_man_ears();
        break;
    case 3:
        e.get_chipmunk()->increment_animation_man_legs();
        break;
    case 4:
        e.get_chipmunk()->increment_animation_man_tail();
        break;
    }
}

bool Manual::handler(Escena& e, unsigned char tecla, int x, int y) {
    switch (tecla)
    {
    case '+':
        std::cout << "Aumentamos grado libertad manual para " << df << std::endl;
        increment(e, df);
        break;
    case '-':
        std::cout << "Disminuímos grado libertad manual para " << df << std::endl;
        decrement(e, df);
        break;
    case 'Q':
        std::cout << "\n +++ Salimos del modo manual +++ " << std::endl;
        parent->set_default_menu();
        parent->update(e, 0, x, y);
        break;
    default:
        if (tecla >= '0' && tecla <= '9') {
            if (tecla > '4') {
                std::cout << "No hay grado de libertad para " << tecla << std::endl;
            }
            else {
                std::cout << "Seleccionamos el grado de libertad " << tecla << std::endl;
                df = tecla - '0';
            }
        }
        else {
            std::cout << "Opciones disponibles:\n";
            std::cout << "[ 0-9 ] - Seleccionar grado de libertad. 0 para todo el cuerpo." << std::endl;
            std::cout << "[ + ] - Aumentamos grado libertad manual.\n";
            std::cout << "[ - ] - Disminuímos grado libertad manual.\n";
            std::cout << "[ Q ] - Volvemos al menú principal." << std::endl;
        }
        break;
    }

    return false;
}