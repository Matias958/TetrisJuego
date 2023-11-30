/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: highscore_al.h
*Descripcion: aspecto gráfico en la muestra de
*           puntajes altos en Allegro
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#ifndef HIGHSCORE_AL_H
#define HIGHSCORE_AL_H

/************** HEADERS ***************/
#include "highscore.h"
#include "element_al.h"
#include "game_state.h"


/************** PROTOTIPOS ***************/

/*showHighScores()
* Función encargada de mostrar el TOP 5 historico del presente juego
* Recibe: elem (estructura que contiene los elementos de Allegro), highscore 
* (información actual del TOP5) y state (estructura que contiene el estado de 
* la ventana - game_state -: CLOSE_DISPLAY, MENU, GAME_SEL, HIGHSCORE o GAME).
* Devuelve: -
*/
void showHighScores(element_t *elem, highscore_t *highscore, window_state_t *state);

#endif
