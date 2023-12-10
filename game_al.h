/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: game_al.h
*Descripcion: módulo encargado del aspecto grafico y la interfaz del juego
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#ifndef GAME_AL_H
#define GAME_AL_H

/************** HEADERS ***************/
#include "element_al.h"
#include "game_state.h"
#include "highscore.h"

/************** PROTOTIPOS ***************/

/*playGame()
 * Funcion encargada de manejar todo el juego
 * Recibe: elem (puntero a la estructura con todos los punteros de allegro), 
 *       mode (estructura que maneja la dificultad del juego)
 *			 state (puntero a la estructura del estado del display), 
 *       y highscore (puntero a la estructura que almacena los puntajes mas altos).
 * Devuelve: --
 */
void playGame(element_t *elem, game_mode_t mode, window_state_t *state, highscore_t *highscore);

#endif // GAME_AL_H
