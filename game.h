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

#endif