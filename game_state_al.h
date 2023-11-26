#ifndef GAME_STATE_AL_H
#define GAME_STATE_AL_H

/*ESTADO DEL DISPLAY*/
#define NUMBER_OF_GAME_MODES 3

enum game_state {CLOSE_DISPLAY, MENU, GAME_SEL, HIGHSCORE, GAME};
enum difficulty {EASY  = 1, MEDIUM, HARD};

/************** ESTRUCTURAS ***************/

typedef struct
{
    unsigned int difficulty;
    bool mirrored;
    bool blanking;
    bool no_empty;
}game_mode_t;

typedef char window_state_t;
 
#endif // GAME_STATE_AL_H