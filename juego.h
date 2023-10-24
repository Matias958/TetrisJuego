#ifndef JUEGO_H
#define JUEGO_H

/************** HEADERS ***************/

#include "reglas.h"

/************** PROTOTIPOS ***************/

/*JUGARTETRIS()
* Función encargada de ir moviendo las piezas en base a los comandos enviados y llamar a las
* funciones necesarias para que se ejecute correctamente el juego.
* Recibe: Un char al movimiento que se realizo, una estructura bloque_t con la pieza con la 
* que se esta jugando; la matris de juego y un int con el puntaje actual.
* Devuelve: Un bool indicando si pudo hacer el movimiento correctamente o no.
*/
bool jugarTetris (char movimiento, bloque_t *pieza, char matris[][12], int *puntaje);


void crearTablero (char matris[][12]);

#endif // JUEGO_H