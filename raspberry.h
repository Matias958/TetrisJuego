/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: raspberry.h
*Descripcion: Manejo de funciones para la raspberry.
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#ifndef RASPBERRY_H
#define RASPBERRY_H

/************** HEADERS ***************/
#include "rules.h"
#include "game.h"
#include "highscore.h"
#include "game_state.h"
#include "score_ras.h"

/************** MACROS ***************/

// Definición de los movimientos
#define UP 'w'
#define RIGHT_RAS 'd'
#define LEFT_RAS 'a'
#define DOWN 's'
#define BUTTON ' '
#define WAIT '.'
#define LONG_PRESS '0'

/************** PROTOTIPOS ***************/

/*JOYSTICK()
* Función encargada de analizar el estado del joystick.
* Recibe: un puntero a char donde se va a guardar el estado del joystick.
* Devuelve: Un bool que indica si logro recolectar algun estado valido (true) o no (false).
*/
bool joystick(char* direction);

/*SHOW_DISPLAY()
* Función encargada de ir actualizando la pantalla.
* Recibe: Una matriz con el tablero de juego.
* Devuelve: -
*/
void showDisplay(char matrix[][WIDTH_OF_BOARD], int pieceType);

/*INIT()
* Función encargada de inicializar la pantalla con la palabra "tetris" y esperar hasta
* que se presione el botón del joystick para empezar el juego.
* Recibe: puntero a estado de la ventana
* Devuelve: -
*/
void init(window_state_t *state);

/*playGame_ras()
 * Funcion encargada de manejar todo el juego
 * Recibe: elem (puntero a la estructura con todos los punteros de allegro), mode (estructura que maneja la dificultad del juego)
 *			state (puntero a la estructura del estado del display), y highscore (puntero a la estructura que almacena los puntajes mas altos)
 * Devuelve: puntaje obtenido en el juego
 */
int playGame_ras(game_mode_t mode, highscore_t *highscore,  window_state_t * state); 

void tetrisAnimation(char rows_tetris[HEIGHT_OF_BOARD]);

/*game_over()
 * Función encargada de imprimir una "END" en la pantalla y esperar a que se presione el boton
 * (nueva partida) o se mueva hacia abajo el joystick (salir juego)
 * Recibe: puntero estado de la ventana
 * Devuelve:-
 */

void game_over(window_state_t *state);

void gameModeSel_ras(window_state_t *state, game_mode_t *gameMode);

void wait(float time);

void showHighScores(highscore_t *highscore, window_state_t *state);


#endif //RASPBERRY_H