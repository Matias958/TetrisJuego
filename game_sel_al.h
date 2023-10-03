
#ifndef GAME_SEL_AL_H
#define GAME_SEL_AL_H

#include "inicializacion_al.h"

typedef struct
{
    unsigned int difficulty;
    bool mirrored;
    bool blanking;
    bool no_empty;
    bool start;
    bool window;
}game_mode_t;

game_mode_t p_game_mode(element_t *elem);

#endif /* GAME_SEL_AL_H */

