/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: menu_al.h
*Descripcion: aspecto gráfico del menu en Allegro.
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#ifndef MENU_AL_H
#define MENU_AL_H

/************** HEADERS ***************/
#include "element_al.h"
#include "game_state.h"

/************** PROTOTIPOS ***************/

/*showMenu
* Funcion encargada de mostrar el menu, y analizar la selección del jugador.
* Recibe: elem ( puntero a estructura con los elementos de Allegro) y state
* (estructura que contiene el estado de la ventana - game_state -: CLOSE_DISPLAY, MENU,
* GAME_SEL, HIGHSCORE o GAME)
* Devuelve: -
*/
void showMenu(element_t *elem, window_state_t *state);

#endif
