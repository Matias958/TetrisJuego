#ifndef REGLAS_H
#define REGLAS_H


#include <stdio.h>
#include <stdlib.h>
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
void Bajar_Pieza(bloque_t* pieza, char matris[][12]);
void Estacionar (bloque_t* pieza, char matris[][12]);
int wall_kick(bloque_t *pieza, char matris[][12]);
void inicializarTiempo(void);
double tiempo_transcurrido(void);

#endif
