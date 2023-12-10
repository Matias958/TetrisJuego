/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: raspberry.h
*Descripcion: manejo funciones para la Raspberry 
*             (manejo joystick, display y distintos menus/pantallas)
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
#define BUTTON '1'
#define WAIT '.'
#define LONG_PRESS '0'
#define LONG_DOWN ' '

/************** PROTOTIPOS ***************/

/* init()
 * Función encargada de inicializar la pantalla con la palabra "TETRIS" y esperar hasta
 * que se mueva el joystick en cualquier dirección. Luego te deja elegir entre empezar a 
 * jugar ("PLAY"), ver el highscore ("HS") o apagar la pantalla ("TRN OFF").
 * Recibe: window_state_t *state, puntero al estado de la ventana
 * Devuelve: -
 * 
 * Nota: Para cambiar opción mover hacia arriba ó abajo, para seleccionar usar el botón.
 */
void init(window_state_t *state);

/* joystick()
 * Función encargada de analizar el estado del joystick.
 * Recibe: un puntero a char donde se va a guardar el estado del joystick.
 * Devuelve: Un bool que indica si logro recolectar algun estado valido (true) o no (false).
 * 
 * Nota: estados posibles: apuntar hacia arriba, abajo, derecha, izquierda, presionar el botón,
 * mantener presionado el botón, mantener hacia abajo.
 */
bool joystick(char* direction);

/* showDisplay()
 * Función encargada de ir actualizando la pantalla durante el juego.
 * Recibe: Una matriz con el tablero de juego,un int con el tipo de pieza siguiente y uno con
 * la pieza holdeada.
 * Devuelve: -
 */
void showDisplay(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], int type, int type2);

/* gameModeSelRas()
 * Función encargada de seleccionar el modo de juego, inicializa la pantalla con la palabra "MDE
 * SEL" y espera hasta que se mueva el joystick en cualquier dirección. Luego te deja elegir los
 * diferentes modos de juego.
 * Recibe: Un puntero a window_state_t con el estado de la ventana y uno a game_mode_t con el modo
 * de juego de la partida.
 * Devuelve: -
 * 
 * Nota: Permite elegir dificultad del 1-3 ("DIF"), modo Not Empty ("NOE"), Blinking ("BLK")
 * y Mirrored ("MRR").
 * 
 * Nota: Para cambiar opción mover hacia arriba ó abajo, para seleccionar usar el botón 
 * ("X": seleccionado, "O":no seleccionado). Para empezar la partida  mover el joystick hacia
 * la derecha y para volver al menú hacia la izquierda.
 */
void gameModeSelRas(window_state_t *state, game_mode_t *gameMode);

/* playGameRas()
 * Función encargada de manejar el juego, muestra tablero de juego actual y siguiente pieza y 
 * permite realizar movimientos o ir al menu de pausa.
 * Recibe: Una estuctura game_mode_t con el modo de juego seleccionado, un puntero a highscore_t
 * con el highscore actual y un puntero a window_state_t con el estado de la ventana.
 * Devuelve: un int con el puntaje de la partida.
 * 
 * Nota: Las direcciones abajo, derecha, izquierda del joystick permiten mover la pieza en dichas
 * direcciones (invirtiendo der-izq si se encuentra en modo "Mirrored"), arriba te permite girar
 * la pieza 90°, el botón permite hacer un hold de la pieza actual y cambiarla por la holdeada 
 * anteriormente, mantener hacia abajo permite hacer "hard drop" de la pieza y mantener pulsado el
 * botón lleva al menú de pausa.
 * 
 */
int playGameRas(game_mode_t mode, highscore_t *highscore,  window_state_t * state); 

/* wait()
 * Función encargada de esperar un determinado tiempo.
 * Recibe: Un float con el tiempo en segundos a esperar.
 * Devuelve: -
 * 
 */
void wait(float time);

/* tetrisAnimation()
 * Función encargada de hacer una animación cuando se elimina una o más filas (hace parpadear esas
 * filas antes de que se borren).
 * Recibe: Un arreglo de char con las filas que se borraron
 * Devuelve: -
 * 
 */
void tetrisAnimation(char rows_tetris[HEIGHT_OF_BOARD]);

/*gameOver()
 * Función encargada de manejar el menú de game_over. Imprime "END" en la pantalla y espera a que
 * muevan el joystick. Luego permite elegir entre ir al menú inicial ("MENU") o terminar el juego/
 * apagar el display ("TRN OFF")
 * Recibe: un puntero a window_state_t con el estado de la ventana
 * Devuelve: -
 * 
 * Nota: Para cambiar opción mover hacia arriba ó abajo, para seleccionar usar el botón.
 */
void gameOver(window_state_t *state);

#endif //RASPBERRY_H