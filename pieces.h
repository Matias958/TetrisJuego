/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: pieces.h
*Descripcion: definiciones para piezas.
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#ifndef PIECES_H
#define PIECES_H

// Definición de las piezas y posibles valores del tablero
enum piezas
{
    EMPTY,
    PIECE_I,
    PIECE_J,
    PIECE_L,
    PIECE_O,
    PIECE_S,
    PIECE_T,
    PIECE_Z,
    BORDER
};

// Estructura que define y edita la pieza movil
typedef struct
{
    int type;
    char matrixOfPiece[4][4];
    int column;
    int line;
    int rotation;
} piece_t;

#endif