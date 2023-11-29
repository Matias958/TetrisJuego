/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: rules.h
*Descripcion: Manejo de piezas en Tetris.
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

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

/*createPiece()
 * Funcion encargada de crear y devolver la estructura de una pieza
 * Recibe: -
 * Devuelve: pieza creada
 */
piece_t createPiece(void);

/*turnPiece()
 * Funcion encargada de rotar una pieza
 * Recibe: piece (puntero a una pieza) y matrix (el tablero donde se esta rotando)
 * Devuelve: -
 */
void turnPiece(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]);

/*collision()
 * Función encargada de comprobar si una pieza choco.
 * Recibe: matrix (tablero del juego) y piece (puntero a la pieza a analizar)
 * Devuelve: int que indica si hubo o no un choque (FAIL o SUCCCESS respectivamente)
 */
int collision(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], piece_t *piece);

/*movePiece()
 * Funcion encargada de mover a los lados la pieza
 * Recibe: piece (puntero a pieza a mover), direction (dirección de movimiento: LEFT o RIGHT)
 * y matrix (el tablero de juego)
 * Devuelve: -
 */
void movePiece(piece_t *piece, int direction, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]);

/* movePieceDown()
 * Funcion encargada de mover una pieza hacia abajo
 * Recibe: piece (puntero a pieza a bajar) y matrix (tablero donde se desea bajar)
 * Devuelve: estado del movimiento (true si exitoso, false de lo contrario)
 */
bool movePieceDown(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]);

/* parkPiece()
 * Función encargada de guardar una pieza en su posición final
 * Recibe: piece (puntero a pieza a "estacionar") y matrix (tablero de juego)
 * Devuelve: char que indica si se estaciono la pieza (SUCCESS) o no (FAIL)
 */
char parkPiece(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]);

/* deleteLine()
 * Función encargada de borrar las filas que se completaron
 * Recibe: matrix (tablero de juego), linesOfMatrix (arreglo donde se colocan sucesivamente,
 *  las filas donde hubo tetris, para finalmente colocar el terminador END_OF_ARRAY) y
 * isTetris(puntero donde se devuelve si hubo tetris - true - o no -false-)
 * Devuelve: puntaje que se ha conseguido sumar
 */

int deleteLine(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], char linesOfMatrix[18], bool *isTetris);

/* wallKick()
 * Función encargada de comprobar si al girar una pieza esta choca ysi esto sucede la acomoda
 * Recibe: piece (puntero a pieza a comodar) y matrix (tablero de juego)
 * Devuelve: un int que indica si logro solucionar el choque (SUCCESS) o no (FAIL)
 */
int wallKick(piece_t *piece, char matrix[HEIGHT_OF_BOARD][12]);

/* initTime()
 * Función encargada de inicializar el timer
 * Recibe: -
 * Devuelve: -
 */
void initTime(void);

/* checkElapsedTime()
 * Función encargada de verificar si ha transcurrido un determinado tiempo tras
 * la inicialización 
 * Recibe: timeStep (tiempo a contrastar si ha transcurrido o no)
 * Devuelve: si ha transcurrido el tiempo (true) o no (false)
 */
bool checkElapsedTime(double timeStep);

#endif
