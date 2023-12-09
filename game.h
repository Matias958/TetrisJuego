/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: game.h
*Descripcion: módulo encargado de jugar al Tetris
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#ifndef GAME_H
#define GAME_H

/************** HEADERS ***************/

#include "rules.h"
#include "game_state.h"

/************** PROTOTIPOS ***************/

/*playTetris()
 * Función encargada de ir moviendo las piezas en base a los comandos enviados y llamar a las
 * Recibe: movimiento ( movimiento a realizar en el tablero), piece (puntero a una pieza), matrix (el tablero donde se esta rotando)
 *			score (puntero al puntaje del jugador), y gameMode (estructura del la dificultad del juego).
 * Devuelve: Un bool indicando si pudo hacer el movimiento correctamente o no.
 */
bool playTetris(char movement, piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], int *score, game_mode_t gameMode);

/*createBoardforNotEmpty()
 * Funcion encargada de llenar el tablero con piezas
 * Recibe: matrix (tablero del juego a llenar)
 * Devuelve: --
 */
void createBoardforNotEmpty(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]);

/*initPiece()
 * Funcion encargada inicializar la siguiente pieza
 * Recibe: --
 * Devuelve: --
 */
void initPiece(void);

/*getNextPiece()
 * Funcion encargada de decir que pieza es la siguiente
 * Recibe: --
 * Devuelve: el tipo de la siguiente pieza
 */
int getNextPiece(void);

/*hold()
* Funcion encargada de holdear una pieza.
* Recibe: pieza 
* Devuelve: un bool si se puedo holdear la pieza pieza o no
*/
bool hold(piece_t* piece);

/*getNextPiece()
 * Funcion encargada de decir que pieza es la almacenada
 * Recibe: --
 * Devuelve: el tipo de la siguiente pieza
 */
int getHoldPiece(void);

/*canHold()
 * Funcion encargada de decir si se puede holdear una pieza o no
 * Recibe: --
 * Devuelve: booleano si se puede holdear una pieza o no
 */
bool canHold(void);

#endif