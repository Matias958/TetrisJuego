
#ifndef GAME_AL_H
#define GAME_AL_H

/************** HEADERS ***************/
#include "element_al.h"
#include "game_state.h"
#include "highscore.h"

/************** PROTOTIPOS ***************/

void playGame(element_t *elem, game_mode_t mode, window_state_t *state, highscore_t *highscore);

#endif // GAME_AL_H
