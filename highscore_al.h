#ifndef HIGHSCORE_AL_H
#define HIGHSCORE_AL_H

/************** HEADERS ***************/
#include "highscore.h"
#include "element_al.h"
#include "game_state.h"

/************** PROTOTIPOS ***************/

/*P_HIGHSCORE()
* Función encargada del manejo y creación de la pantalla de highscore.
* Recibe: punteros a una estructura element_t, una highscore_t y una window_state_t.
* Devuelve: -
*/
void p_highscore(element_t *elem, highscore_t *highscore, window_state_t *state);

#endif //HIGHSCORE_AL_H
