#ifndef REGLAS_H
#define REGLAS_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "piezas.h"
#include <time.h>


#define IZQUIERDA -1
#define DERECHA 1
#define BIEN 0
#define MAL 1
 
//headers
bloque_t Crear_Pieza (void);
void Girar_Pieza(bloque_t* pieza, char matris [][12]);
int  choque (char matris[][12], bloque_t * pieza);
void Mover_Pieza (bloque_t* pieza, int direccion, char matris[][12]);
bool Bajar_Pieza(bloque_t* pieza, char matris[][12]);
char Estacionar (bloque_t* pieza, char matris[][12]);
int borrarFila (char matrisw[18][12]);

int wall_kick(bloque_t *pieza, char matris[][12]);

/* INICIALIZARTIEMPO()
* Función encargada de inicializar el timer
* Recibe: -
* Devuelve: -
*/
void inicializarTiempo(void);

/* TIEMPO_TRANSCURRIDO()
* Función encargada de devolver el tiempo transcurrido
* Recibe: double con el timestep
* Devuelve: booleano que indica si pudo obtener el tiempo transcurrido
*/
bool tiempo_transcurrido(double timestep);

#endif
