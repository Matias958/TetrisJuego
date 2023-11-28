#ifndef GAME_STATE_H
#define GAME_STATE_H

/*ESTADO DEL DISPLAY*/
#define NUMBER_OF_GAME_MODES 3

enum game_state
{
    CLOSE_DISPLAY,
    MENU,
    GAME_SEL,
    HIGHSCORE,
    GAME
};
enum difficulty
{
    EASY = 1,
    MEDIUM,
    HARD
};

/************** ESTRUCTURAS ***************/

typedef struct
{
    unsigned int difficulty;
    bool mirrored;
    bool blinking;
    bool notEmpty;
} game_mode_t;

typedef char window_state_t;

#endif // GAME_STATE_H