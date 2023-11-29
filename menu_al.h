#ifndef MENU_AL_H
#define MENU_AL_H

/************** HEADERS ***************/

#include "element_al.h"
#include "game_state.h"

/************** PROTOTIPOS ***************/

/* SHOW_MENU
* Función encargada de mostrar e inicializar la pantalla del menu de inicio.
* Recibe: puntero a una estructura element_t y una window_state_t
* Devuelve: -
*/
void showMenu(element_t *elem, window_state_t *state);

#endif // MENU_AL_H
