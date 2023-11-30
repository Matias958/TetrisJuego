
#ifndef GAME_SEL_AL_H
#define GAME_SEL_AL_H

/************** HEADERS ***************/
#include "element_al.h"
#include "game_state.h"

/************** PROTOTIPOS ***************/

/*SHOW_GAME_MODE_SEL()
 * Función encargada de crear y mostrar la pantalla que permite seleccionar el modo de juego.
 * Recibe: Punteros a una estructura element_t, una window_state_t y una game_mode_t
 * Devuelve: -
 */
void showGameModeSel(element_t *elem, window_state_t *state, game_mode_t *gameMode);

#endif // GAME_SEL_AL_H
