/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: game_state.h
*Descripcion: estructuras y macros para el manejo
*          del estado del juego
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#ifndef GAME_STATE_H
#define GAME_STATE_H

/************** MACROS ***************/

#define NUMBER_OF_GAME_MODES 3

/************** ESTRUCTURAS ***************/

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

/*game_mode_t
* Estructura que almacena la dificultad y los modos de juego
* activos.
* NOTA: difficulty puede tomar valores de difficulty: EASY,
* MEDIUM o HARD.
*/
typedef struct
{
    unsigned int difficulty;
    bool mirrored;
    bool blinking;
    bool notEmpty;
} game_mode_t;


/*window_state_t
* Estructura que almacena el estado del display:
*    -CLOSE_DISPLAY
*    -MENU
*    -GAME_SEL
*    -HIGHSCORE
*    -GAME
*/
typedef char window_state_t;

#endif // GAME_STATE_H