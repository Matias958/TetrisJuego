/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
 *Titulo: score_ras.h
 *Descripcion: manejo funciones para mostrar los scores
 *             en el display de la raspberry
 *Autores: Facundo Torres
 *         Julieta Libertad Rodriguez
 *         Matias Minitti
 *         Ramiro Nieto Abascal
 */

#ifndef SCORE_RAS_H
#define SCORE_RAS_H

/************** HEADERS ***************/
#include "rules.h"
#include "highscore.h"
#include "game_state.h"

/************** PROTOTIPOS ***************/

/*scoreRas()
 * Función encargada de manejar las funciones de puntaje en la raspberry una vez finalizada la partida.
 * Recibe: un int con el puntaje y un puntero a highscore_t con el highscore
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 */
bool scoreRas(int score, highscore_t *highscore);

/*printCharacter()
 * Función encargada de imprimir un caracter en la pantalla. (No borra el display)
 * Recibe: un char con la letra, un int con el corrimiento en x y otro en y
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 *
 * Nota: Sólo imprime letras mayúsculas y número del 0-9.
 */
bool printCharacter(char letter, int i, int j);

/*printScore()
 * Función encargada de imprimir un puntaje en la pantalla.
 * Recibe: un int con el puntaje
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 * 
 * Nota: Se considera que el puntaje es un numero entero de cuatro cifras.
 */
bool printScore(int score);

/*printNum()
 * Función encargada de imprimir un numero (del 0-9) en la pantalla. (No borra el display)
 * Recibe: un int con el numero, uno con el corrimiento en x y otro en y
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 */
bool printNum(int num, int i, int j);

/*showHighScores()
 * Función encargada de mostrar los highscores actuales.
 * Recibe: un puntero a highscore_t con el highscore y uno a window_state_t con el estado de la ventana
 * Devuelve: -
 * 
 * Nota: Muestra el puesto y el nombre de los jugadores, al mover a la derecha muestra el puntaje de dicho
 * jugador y a la izquierda vuelve a los nombres. Moviendo hacia arriba o hacia abajo (estando en los 
 * puntajes o los nombres), muestra los datos de los otros jugadores. Moviendo hacia la izquierda estando
 * en la pantalla de los nombres, vuelve al menú.
 */
void showHighScores(highscore_t *highscore, window_state_t *state);


#endif //SCORE_RAS_H