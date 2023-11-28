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
#define WIDE_OF_BOARD 12
 

/************** PROTOTIPOS ***************/

/*createPiece()
 * Funcion encargada de crear y devolver la estructura de una pieza
 * Recibe: no recibe parámetros
 * Devuelve: estructura bloque_t con la pieza creada
 */
piece_t createPiece (void);

/*turnPiece()
 * Funcion encargada de rotar una pieza
 * Recibe: estructura bloque_t * con la pieza a girar y char matris [][12]
 * con tablero del juego.
 * Devuelve: -
 */
void turnPiece(piece_t* piece, char matrix [HEIGHT_OF_BOARD][WIDE_OF_BOARD]);

/*CHOQUE()
 * Función encargada de comprobar si una pieza choco contra un borde
 * Recibe: char matris[][12] con tablero del juego y bloque_t * con la pieza
 * Devuelve: int que indica si hubo o no un choque
 */
int  collision (char matrix[HEIGHT_OF_BOARD][WIDE_OF_BOARD], piece_t * piece);

/*MOVER_PIEZA()
 * Funcion encargada de mover a los lados la pieza
 * Recibe: bloque_t * con la pieza a mover, int con la dirección de movimiento,
 * char matris[][12] con el tablero de juego
 * Devuelve: -
 */
void movePiece (piece_t* piece, int direction, char matrix[HEIGHT_OF_BOARD][WIDE_OF_BOARD]);

/* BAJAR_PIEZA()
 * Funcion encargada de mover una pieza hacia abajo
 * Recibe: bloque_t * pieza a bajar, char matris[][12]
 * tablero del juego
 * Devuelve: un bool, flag en caso de no poder bajar, false es que no pudo 
 * realizar el movimiento
 */
bool movePieceDown(piece_t* piece, char matrix[HEIGHT_OF_BOARD][WIDE_OF_BOARD]);

/* ESTACIONAR()
 * Función encargada de guardar una pieza en su posición final
 * Recibe: bloque_t * con la pieza a "estacionar", char matris [][12]
 * tablero del juego actual
 * Devuelve: char que indica si se estaciono la pieza por fuera de la 
 * matris del juego
 */
char parkPiece (piece_t* piece, char matrix[HEIGHT_OF_BOARD][WIDE_OF_BOARD]);

/* BORRARFILA()
 * Función encargada de borrar las filas que se completaron
 * Recibe: char tablero[18][12] con el tablero actual, un char filas_tetris[18] con
 * las filas del tablero y un bool * donde se guarda si se consiguió hacer tetris.
 * Devuelve: un int con el puntaje que suma, dependiendo de la cantidad de filas
 * que se borraron (considerando el caso de "hacer TETRIS", elimnar 4 filas de un movimiento)
 */

int deleteLine (char matrix[HEIGHT_OF_BOARD][WIDE_OF_BOARD], char linesOfMatrix[18], bool *isTetris);

/* WALL_KICK()
 * Función encargada de comprobar si al girar una pieza esta choca contra un borde y
 * si esto sucede la acomoda
 * Recibe: bloque_t pieza a "estacionar", char matris [][12]
 * tablero del juego actual
 * Devuelve: un int que indica si logro solucionar el choque
 */
int wallKick(piece_t *piece, char matrix[HEIGHT_OF_BOARD][12]);

/* INICIALIZARTIEMPO()
* Función encargada de inicializar el timer
* Recibe: -
* Devuelve: -
*/
void initTime(void);

/* TIEMPO_TRANSCURRIDO()
* Función encargada de devolver el tiempo transcurrido
* Recibe: double con el timestep
* Devuelve: booleano que indica si pudo obtener el tiempo transcurrido
*/
bool checkElapsedTime(double timestep);

#endif 
