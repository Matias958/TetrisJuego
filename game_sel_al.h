/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: game_sel_al.h
*Descripcion: aspecto gráfico de la selección del
* modo de juego y la dificultad.
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#ifndef GAME_SEL_AL_H
#define GAME_SEL_AL_H

/************** HEADERS ***************/
#include "element_al.h"
#include "game_state.h"

/************** PROTOTIPOS ***************/

/*showGameModeSel()
 * Función de mostrar el aspecto gráfico de la selección del modo
 * de juego y la dificultad del mismo
 * Recibe: elem (elementos de Allegro), state (estructura que contiene
 * el estado de la ventana - game_state -: CLOSE_DISPLAY, MENU,
 * GAME_SEL, HIGHSCORE o GAME) y gameMode (estructura que almacena
 * la dificultad -EASY, MEDIUM o HARD- y los modos de juego activos).
 * Devuelve: -
 */
void showGameModeSel(element_t *elem, window_state_t *state, game_mode_t *gameMode);

#endif // GAME_SEL_AL_H
