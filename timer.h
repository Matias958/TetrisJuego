/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: timer.h
*Descripcion: funciones encargadas de maipular timers en Raspberry
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#ifndef TIMER_H
#define TIMER_H

/************** HEADERS ***************/
#include <stdbool.h>

/************** DECLARACIONES ***************/
typedef struct
{
    long int initialNumberOfClocks;
    float timeOfTicks;
}timer_ras_t;


/************** PROTOTIPOS ***************/
/* startTimer()
* Funcion encargada de que un timer comience a medir el tiempo
* Recibe: puntero a timer
* Devuelve: -
*/
void startTimer(timer_ras_t *timer);

/* checkTimer()
* Funcion encargada de que si un timer ha hecho un tick
* Recibe: puntero a timer
* Devuelve: si ha hecho un tick (true) o no (false)
*/
bool checkTimer(timer_ras_t *timer);

#endif