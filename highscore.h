#ifndef HIGHSCORE_H
#define HIGHSCORE_H

/************** HEADERS ***************/
#include <stdbool.h>

/************** MACROS ***************/
#define NUMBER_OF_PLAYERS 5
#define CHARACTERS 3

/************** ESTRUCTURAS ***************/
typedef struct
{
	int highscores[NUMBER_OF_PLAYERS];
	char nameOfHighscores[NUMBER_OF_PLAYERS][CHARACTERS + 1];

} highscore_t;

/************** PROTOTIPOS ***************/

/*GET_HIGHSCORE()
* Función encargada de recuperar el highscore
* Recibe: un puntero a una highscore_t donde se va a guardar el highscore
* Devuelve: un bool indicando si funcionó correctamente
*/
bool getHighscore(highscore_t *highscore);

/*CHECK_IF_HIGHSCORE()
 * Función encargada de fijarse en que puesto del highscore esta el puntaje actual
 * Recibe: un int con el puntaje de la jugada actual y un puntero a una highscore_t donde esta el highscore
 * Devuelve: un int con el puesto donde se encuentra
 */
int checkIfHighscore(int score, highscore_t *highscore);

/*SET_HIGHSCORE()
 * Función encargada de guardar el puntaje actual dentro el highscore
 * Recibe: un puntero a una highscore_t donde esta el highscore, un int con el puntaje actual y
 * un arreglo de char de tamaño "CHARACTERS" con el alias del nombre del jugador actual
 * Devuelve: un bool indicando si funcionó correctamente
 */
bool setHighscore(highscore_t *highscore, int score, char name[CHARACTERS]);

#endif //HIGHSCORE_H
