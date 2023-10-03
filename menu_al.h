
#ifndef TETRIS_P1_INTERFAZ_AL_H
#define TETRIS_P1_INTERFAZ_AL_H

/*HEADERS*/
#include "inicializacion_al.h"

/*DEFINICIONES*/

typedef struct
{
    bool play;
    bool highscore;
    bool window;
}menu_state_t;


/*PROTOTIPOS*/
menu_state_t p_menu(element_t *elem);

#endif //TETRIS_P1_INTERFAZ_AL_H
