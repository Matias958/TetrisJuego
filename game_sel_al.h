
#ifndef GAME_SEL_AL_H
#define GAME_SEL_AL_H

/************** HEADERS ***************/
#include "element_al.h"
#include "game_state.h"

/************** PROTOTIPOS ***************/

/*P_GAME_MODE()
 * Función encargada de crear y seleccionar el modo de juego elegido.
 * Recibe: Estructura element_t; window_state_t y game_mode_t
 * Devuelve: -
 */
void showGameModeSel(element_t *elem, window_state_t *state, game_mode_t *gameMode);

#endif // GAME_SEL_AL_H
