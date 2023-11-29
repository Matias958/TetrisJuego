#ifndef GAME_H
#define GAME_H

/************** HEADERS ***************/

#include "rules.h"
#include "game_state.h"

/************** PROTOTIPOS ***************/

/* PLAY_TETRIS()
 * Función encargada de ir moviendo las piezas en base a los comandos enviados y llamar a las
 * funciones necesarias para que se ejecute correctamente el juego.
 * Recibe: Un char al movimiento que se realizo, una estructura piece_t con la pieza con la
 * que se esta jugando; la matriz de juego, un puntero a int donde se guarda puntaje actual y
 * una estructura game_mode_t indicando modo y dificultad elegido.
 * Devuelve: Un bool indicando si pudo hacer el movimiento correctamente o no.
 */
bool playTetris(char movement, piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], int *score, game_mode_t gameMode);

/*CREATE_BOARD_FOR_NOT_EMPTY()
 * Función encargada de crear un tablero con piezas preinicializadas para el modo "not_empty".
 * Recibe: la matriz de juego.
 * Devuelve: -
 */
void createBoardforNotEmpty(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]);

/*INIT_PIECE()
 * Función encargada de inicializar una pieza.
 * Recibe: -
 * Devuelve: -
 */
void initPiece(void);

/*GET_NEXT_PIECE()
 * Función encargada de obtener el tipo de una pieza ya creada.
 * Recibe: -
 * Devuelve: un int con el tipo de pieza
 */
int getNextPiece(void);

#endif //GAME_H