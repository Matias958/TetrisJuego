#ifndef RULES_H
#define RULES_H

/************** HEADERS ***************/

#include <stdlib.h>
#include <stdbool.h>
#include "pieces.h"

/************** MACROS ***************/

#define IZQUIERDA -1
#define DERECHA 1
#define BIEN 0
#define MAL 1

#define FINAL_DEL_ARREGLO -1

#define LARGO_TABLERO 18
#define ANCHO_TABLERO 12
 

/************** PROTOTIPOS ***************/

/*BLOQUE_T()
 * Funcion encargada de crear y devolver la estructura de una pieza
 * Recibe: -
 * Devuelve: estructura bloque_t con la pieza creada
 */
bloque_t Crear_Pieza (void);

/*GIRAR_PIEZA()
 * Funcion encargada de rotar una pieza
 * Recibe: estructura bloque_t * con la pieza a girar y char matris [][12]
 * con tablero del juego.
 * Devuelve: -
 */
void Girar_Pieza(bloque_t* pieza, char matris [][12]);

/*CHOQUE()
 * Función encargada de comprobar si una pieza choco contra un borde
 * Recibe: char matris[][12] con tablero del juego y bloque_t * con la pieza
 * Devuelve: int que indica si hubo o no un choque
 */
int  choque (char matris[][12], bloque_t * pieza);

/*MOVER_PIEZA()
 * Funcion encargada de mover a los lados la pieza
 * Recibe: bloque_t * con la pieza a mover, int con la dirección de movimiento,
 * char matris[][12] con el tablero de juego
 * Devuelve: -
 */
void Mover_Pieza (bloque_t* pieza, int direccion, char matris[][12]);

/* BAJAR_PIEZA()
 * Funcion encargada de mover una pieza hacia abajo
 * Recibe: bloque_t * pieza a bajar, char matris[][12]
 * tablero del juego
 * Devuelve: un bool, flag en caso de no poder bajar, false es que no pudo 
 * realizar el movimiento
 */
bool Bajar_Pieza(bloque_t* pieza, char matris[][12]);

/* ESTACIONAR()
 * Función encargada de guardar una pieza en su posición final
 * Recibe: bloque_t * con lapieza a "estacionar", char matris [][12]
 * tablero del juego actual
 * Devuelve: char que indica si se estaciono la pieza por fuera de la 
 * matris del juego
 */
char Estacionar (bloque_t* pieza, char matris[][12]);

/* BORRARFILA()
 * Función encargada de borrar las filas que se completaron
 * Recibe: char tablero[18][12] con el tablero actual, un char filas_tetris[18] con
 * las filas del tablero y un bool * donde se guarda si se consiguió hacer tetris.
 * Devuelve: un int con el puntaje que suma, dependiendo de la cantidad de filas
 * que se borraron (considerando el caso de "hacer TETRIS", elimnar 4 filas de un movimiento)
 */

int borrarFila (char matris[18][12], char filas_tetris[18], bool *tetris);

/* WALL_KICK()
 * Función encargada de comprobar si al girar una pieza esta choca contra un borde y
 * si esto sucede la acomoda
 * Recibe: bloque_t pieza a "estacionar", char matris [][12]
 * tablero del juego actual
 * Devuelve: un int que indica si logro solucionar el choque
 */
int wall_kick(bloque_t *pieza, char matris[][12]);

/* INICIALIZARTIEMPO()
* Función encargada de inicializar el timer
* Recibe: -
* Devuelve: -
*/
void inicializarTiempo(void);

/* TIEMPO_TRANSCURRIDO()
* Función encargada de devolver el tiempo transcurrido
* Recibe: double con el timestep
* Devuelve: booleano que indica si pudo obtener el tiempo transcurrido
*/
bool tiempo_transcurrido(double timestep);

#endif 
