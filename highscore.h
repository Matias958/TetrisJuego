/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: highscore.h
*Descripcion: manejo de archivo que contiene el 
*             registro de puntajes altos
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#ifndef HIGHSCORE_H
#define HIGHSCORE_H

/************** HEADERS ***************/
#include <stdbool.h>

/************** MACROS***************/
#define NUMBER_OF_PLAYERS 5
#define CHARACTERS 3


/*highscore_t
* Estructura donde se almacena la información de los
* puntajes altos durante el juego.
* highscores: arreglo de puntajes
* nameOfHighscore: arreglo de nombres de los respectivos
* puntajes (de largo CHARACTERS + terminador)
*/
typedef struct
{
	int highscores[NUMBER_OF_PLAYERS];
	char nameOfHighscores[NUMBER_OF_PLAYERS][CHARACTERS + 1];

} highscore_t;


/************** PROTOTIPOS ***************/

/*getHighscore()
* Función encargada de recopilar la información que se encuentra en el
* archivo highscore.txt con el formato: AAA(nombre)99999(puntaje),
* Recibe: highscore (estructura donde almacenar toda la información recopilada).
* Devuelve: estado del proceso (true si fue exitoso o false de lo contrario)
*/
bool getHighscore(highscore_t *highscore);

/*checkIfHighscore()
* Función encargada de determinar si se realizo un puntaje para colocarse
*  en el TOP 5 historico del presente juego, y devolver la posición en la
*  que se encuentra en dicho caso.
* Recibe: score (puntaje a contrastar) y highscore (información del estado
*  actual del TOP 5).
* Devuelve: posición en la que se encuentra el puntaje dado dentro del TOP 5
* o un valor mayor a NUMBER_OF_PLAYERS
*/
int checkIfHighscore(int score, highscore_t *highscore);


/*setHighScore()
* Función encargada de guardar un puntaje en el TOP 5.
* Recibe: highscore (estado actual del TOP 5), score (puntaje a guardar) y 
*  name (nombre de 3 caracteres a guardar junto con el puntaje).
* Devuelve: estado del proceso (true si fue exitoso o false de lo contrario)
*/
bool setHighscore(highscore_t *highscore, int score, char name[CHARACTERS]);

#endif
