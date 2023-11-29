#ifndef RULES_H
#define RULES_H

/************** HEADERS ***************/

#include <stdlib.h>
#include <stdbool.h>
#include "pieces.h"

/************** MACROS ***************/

#define LEFT -1
#define RIGHT 1
#define SUCCESS 0
#define FAIL 1

#define END_OF_ARRAY -1

#define HEIGHT_OF_BOARD 18
#define WIDTH_OF_BOARD 12

/************** PROTOTIPOS ***************/

/*CREATE_PIECE()
 * Funcion encargada de crear y devolver la estructura de una pieza
 * Recibe: -
 * Devuelve: estructura piece_t con la pieza creada
 */
piece_t createPiece(void);

/*TURN_PIECE()
 * Funcion encargada de rotar una pieza
 * Recibe: puntero a piece_t con la pieza a girar y una matriz con el tablero del juego.
 * Devuelve: -
 */
void turnPiece(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]);

/*COLLISION()
 * Función encargada de comprobar si una pieza chocó contra un borde
 * Recibe: una matriz con el tablero del juego y un puntero a piece_t con la pieza
 * Devuelve: int que indica si hubo o no un choque
 */
int collision(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], piece_t *piece);

/*MOVE_PIECE()
 * Funcion encargada de mover a los lados la pieza.
 * Recibe: puntero a piece_t con la pieza a mover, int con la dirección de movimiento y
 * una matriz con el tablero de juego.
 * Devuelve: -
 */
void movePiece(piece_t *piece, int direction, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]);

/* MOVE_PIECE_DOWN()
 * Funcion encargada de mover una pieza hacia abajo
 * Recibe: puntero a piece_t con la pieza a bajar, una matriz con el tablero del juego
 * Devuelve: un flag en caso de no poder bajar, false es que no pudo realizar el movimiento
 */
bool movePieceDown(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]);

/* PARK_PIECE()
 * Función encargada de guardar una pieza en su posición final
 * Recibe: puntero a piece_t con la pieza a "estacionar", una matriz con el
 * tablero del juego actual
 * Devuelve: un char indicando si se estacionó la pieza por fuera de la matriz del juego
 */
char parkPiece(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]);

/* DELETE_LINE()
 * Función encargada de borrar las filas que se completaron
 * Recibe: una matriz con el tablero actual, una matis de char con las lineas donde ocurre el tetris
 * un puntero a un bool que va a indicar si se "hizo TETRIS", se eliminan 4 filas consecutivas de un movimiento
 * Devuelve: Puntaje que suma, dependiendo de la cantidad de filas
 * que se borraron (considerando el caso de "hacer TETRIS")
 */
int deleteLine(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], char linesOfMatrix[18], bool *isTetris);

/* WALL_KICK()
 * Función encargada de comprobar si al girar una pieza esta choca contra un borde y
 * si esto sucede la acomoda
 * Recibe: puntero a piece_t pieza a "estacionar", una matriz con el tablero del juego actual
 * Devuelve: un int que indica si logro solucionar el choque
 */
int wallKick(piece_t *piece, char matrix[HEIGHT_OF_BOARD][12]);

/* INIT_TIME()
 * Función encargada de inicializar el timer
 * Recibe: -
 * Devuelve: -
 */
void initTime(void);

/* CHECK_ELAPSED_TIME()
 * Función encargada de devolver el tiempo transcurrido
 * Recibe: double con el timestep
 * Devuelve: booleano que indica si pudo obtener el tiempo transcurrido
 */
bool checkElapsedTime(double timestep);

#endif //RULES_H
