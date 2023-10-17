#ifndef PIEZAS_H        //programacion defensiva
#define PIEZAS_H

// #define BORDE   100
// #define NADA    0
// #define PIEZA_I 1       //palo
// #define PIEZA_J 2       //j
// #define PIEZA_L 3       //L
// #define PIEZA_O 4       //cuadrado
// #define PIEZA_S 5       //s
// #define PIEZA_T 6       //T
// #define PIEZA_Z 7       //z

enum piezas {NADA, PIEZA_I, PIEZA_J, PIEZA_L, PIEZA_O, PIEZA_S, PIEZA_T, PIEZA_Z, BORDE};

extern const char arreglo_piezas_0 [7][4][4];

                                  
typedef struct                  //estructura que define y edita la pieza movil
{
    int tipo;
    char matrix_pieza [4][4];
    int columna;
    int fila;
    int rotacion;
} bloque_t;

#endif