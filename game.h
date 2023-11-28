#ifndef GAME_H
#define GAME_H

/************** HEADERS ***************/

#include "rules.h"
#include "game_state.h"

/************** PROTOTIPOS ***************/

/*JUGARTETRIS()
 * Función encargada de ir moviendo las piezas en base a los comandos enviados y llamar a las
 * funciones necesarias para que se ejecute correctamente el juego.
 * Recibe: Un char al movimiento que se realizo, una estructura bloque_t con la pieza con la
 * que se esta jugando; la matris de juego y un int con el puntaje actual.
 * Devuelve: Un bool indicando si pudo hacer el movimiento correctamente o no.
 */
bool playTetris(char movement, piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], int *score, game_mode_t gameMode);

void createBoardforNotEmpty(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]);

void initPiece(void);

int getNextPiece(void);

#endif