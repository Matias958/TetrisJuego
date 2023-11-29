#ifndef RASPBERRY_H
#define RASPBERRY_H

/************** HEADERS ***************/
#include "rules.h"

/************** MACROS ***************/

// Definición de los movimientos
#define UP 'w'
#define RIGHT_RAS 'd'
#define LEFT_RAS 'a'
#define DOWN 's'
#define BUTTON ' '
#define WAIT '.'

/************** PROTOTIPOS ***************/

/*JOYSTICK()
* Función encargada de analizar el estado del joystick.
* Recibe: -
* Devuelve: Un char con el estado del joystick.
*/
char joystick(void);

/*SHOW_DISPLAY()
* Función encargada de ir actualizando la pantalla.
* Recibe: Una matriz con el tablero de juego.
* Devuelve: -
*/
void show_display(char matrix[][WIDTH_OF_BOARD]);

/*INIT()
* Función encargada de inicializar la pantalla con la palabra "tetris" y esperar hasta
* que se presione el botón del joystick para empezar el juego.
* Recibe: -
* Devuelve: -
*/
void init(void);

/*PAUSE()
* Función encargada de mostrar en la pantalla la "p" de pausa y esperar a
* que se presione el botón del joystick para continuar el juego.
* Recibe: -
* Devuelve: -
*/
void pause (void);

/*PRINT_HIGHSCORE()
* Función encargada de mostrar en la pantalla "HI" indicando que
* se consiguió un nuevo highscore
* Recibe: -
* Devuelve: -
*/
void print_highscore(void);

#endif // RASPBERRY_H