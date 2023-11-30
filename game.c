/*HEADERS*/
#include <stdbool.h>
#include "game.h"
#include "rules.h"

piece_t nextPiece;

/* PLAY_TETRIS()
 * Función encargada de ir moviendo las piezas en base a los comandos enviados y llamar a las
 * funciones necesarias para que se ejecute correctamente el juego.
 * Recibe: Un char al movimiento que se realizo, una estructura piece_t con la pieza con la
 * que se esta jugando; la matriz de juego, un puntero a int donde se guarda puntaje actual y
 * una estructura game_mode_t indicando modo y dificultad elegido.
 * Devuelve: Un bool indicando si pudo hacer el movimiento correctamente o no.
 */
bool playTetris(char movement, piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], int *score, game_mode_t gameMode)
{
    bool flagGoDown = false;
    switch (movement)  //juego segun que movimiento se hizo 
    {
    case 'd':
        movePiece(piece, gameMode.mirrored ? LEFT : RIGHT, matrix);
        break;
    case 'a':
        movePiece(piece, gameMode.mirrored ? RIGHT : LEFT, matrix);
        break;
    case 's':
        flagGoDown = movePieceDown(piece, matrix);
        // inicializarTiempo();
        if (flagGoDown == false) //si choco estaciona la pieza
        {
            char flag_estacionar = parkPiece(piece, matrix);
            if (flag_estacionar == SUCCESS)  //si se puede seguir jugando crea otra pieza y sigue jugando
            {
                *piece = nextPiece;
                nextPiece = createPiece();
            }
            else  //si no se puede seguir jugando devuelve true
            {
                return true;
            }
        }
        break;

    case 'w':
        turnPiece(piece, matrix);
        break;

    case ' ': // baja hasta chocar
        flagGoDown = movePieceDown(piece, matrix);
        while (flagGoDown)
        {
            flagGoDown = movePieceDown(piece, matrix);
        }
        char flag_estacionar = parkPiece(piece, matrix);
        if (flag_estacionar == SUCCESS)
        {
            *piece = nextPiece;
            nextPiece = createPiece();
        }
        else
        {
            return true;
        }
        break;

    default:
        break;
    }

    if (checkElapsedTime(1.0 / (1.0 + gameMode.difficulty / 2.0 + (*score / 500.0)))) //si no se hizo una accion compruebo si tengo que bajar por tiempo
    {
        flagGoDown = movePieceDown(piece, matrix); //en caso que ya paso el tiempo baja la pieza
        if (flagGoDown == false)
        {
            char flag_estacionar = parkPiece(piece, matrix); //verifico otra ves que pueda seguir jugando
            if (flag_estacionar == SUCCESS)
            {
                *piece = nextPiece;
                nextPiece = createPiece();
            }
            else
            {
                return true;
            }
        }
    }

    if (collision(matrix, piece) == FAIL)
    {
        return true;
    }

    return false;
}

/*CREATE_BOARD_FOR_NOT_EMPTY()
 * Función encargada de crear un tablero con piezas preinicializadas para el modo "not_empty".
 * Recibe: la matriz de juego.
 * Devuelve: -
 */
void createBoardforNotEmpty(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD])
{
    int i, numberOfPieces = 5 + rand() % 4; //creo una cantidad de 5 a 8 piezas
    for (i = 0; i < numberOfPieces; i++)
    {
        piece_t piece = createPiece();
        piece.line = HEIGHT_OF_BOARD - 6; //las crea solo en la parte baja del tablero
        while (rand() % 7) //las muevo de forma random 
        {
            int movement = rand() % 100;

            if (!(movement % 7))
            {
                bool flag_bajar = movePieceDown(&piece, matrix);
                if (flag_bajar == false)
                {
                    break;
                }
            }

            if (!(movement % 5))
            {
                turnPiece(&piece, matrix);
            }

            if (!(movement % 3))
            {
                movePiece(&piece, RIGHT, matrix);
            }

            if (!(movement % 2))
            {
                movePiece(&piece, LEFT, matrix);
            }
        }
        parkPiece(&piece, matrix);
    }
}

/*INIT_PIECE()
 * Función encargada de inicializar una pieza.
 * Recibe: -
 * Devuelve: -
 */
void initPiece(void)
{
    nextPiece = createPiece();
}

/*GET_NEXT_PIECE()
 * Función encargada de obtener el tipo de una pieza ya creada.
 * Recibe: -
 * Devuelve: un int con el tipo de pieza
 */
int getNextPiece(void)
{
    return nextPiece.type;
}