#ifndef SCORE_RAS_H
#define SCORE_RAS_H

/************** HEADERS ***************/
#include "rules.h"
#include "highscore.h"
#include "game_state.h"

/************** PROTOTIPOS ***************/

/*SCORE_RAS()
 * Función encargada de manejar las funciones de puntaje en la raspberry
 * Recibe: un int con el puntaje y un puntero a highscore_t con el highscore
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 */
bool score_ras(int score, highscore_t *highscore);

/*PRINT_NUM()
 * Función encargada de imprimir un numero en la pantalla. (No borra el display)
 * Recibe: un int con el numero, uno con el corrimiento en x y otro en y
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 */
bool print_num(int num, int i, int j);

/*PRINT_LETTER()
 * Función encargada de imprimir una letra en la pantalla. (No borra el display)
 * Recibe: un char con la letra, un int con el corrimiento en x y otro en y
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 */
bool print_letter(char letter, int i, int j);

#endif //SCORE_RAS_H