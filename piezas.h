#ifndef PIEZAS_H        
#define PIEZAS_H


//Definición de las piezas y posibles valores del tablero
enum piezas {NADA, PIEZA_I, PIEZA_J, PIEZA_L, PIEZA_O, PIEZA_S, PIEZA_T, PIEZA_Z, BORDE};

extern const char arreglo_piezas_0 [7][4][4];

// Estructura que define y edita la pieza movil                             
typedef struct                  
{
    int tipo;
    char matrix_pieza [4][4];
    int columna;
    int fila;
    int rotacion;
} bloque_t;

#endif //PIEZAS_H