/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: timer.c
*Descripcion: funciones encargadas de maipular timers en Raspberry
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/


/************** HEADERS ***************/
#include "timer.h"
#include <time.h>

/* startTimer()
* Funcion encargada de que un timer comience a medir el tiempo
* Recibe: puntero a timer
* Devuelve: -
*/
void startTimer(timer_ras_t *timer)
{
    timer->initialNumberOfClocks = clock();
}

/* checkTimer()
* Funcion encargada de que si un timer ha hecho un tick
* Recibe: puntero a timer
* Devuelve: si ha hecho un tick (true) o no (false)
*/
bool checkTimer(timer_ras_t *timer)
{
    return (( (float) (clock() - timer->initialNumberOfClocks) / CLOCKS_PER_SEC >= timer->timeOfTicks));
}