#include <stdbool.h>
#include "game.h"
#include "rules.h"

piece_t nextPiece;

/*JUGARTETRIS()
 * Función encargada de ir moviendo las piezas en base a los comandos enviados y llamar a las
 * funciones necesarias para que se ejecute correctamente el juego.
 * Recibe: Un char al movimiento que se realizo, una estructura bloque_t con la pieza con la
 * que se esta jugando; la matris de juego y un int con el puntaje actual.
 * Devuelve: Un bool indicando si pudo hacer el movimiento correctamente o no.
 */
bool playTetris(char movement, piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], int *score, game_mode_t gameMode)
{
    bool flagGoDown = false;
    switch (movement)
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
        if (flagGoDown == false)
        {
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

    if (checkElapsedTime(1.0 / (1.0 + gameMode.difficulty / 2.0 + (*score / 500.0))))
    {
        flagGoDown = movePieceDown(piece, matrix);
        if (flagGoDown == false)
        {
            char flag_estacionar = parkPiece(piece, matrix); // temporal en realidad habria que darle un tiempo
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

void createBoardforNotEmpty(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD])
{
    int i, numberOfPieces = 5 + rand() % 4;
    for (i = 0; i < numberOfPieces; i++)
    {
        piece_t piece = createPiece();
        piece.line = HEIGHT_OF_BOARD - 6;
        while (rand() % 7)
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

void initPiece(void)
{
    nextPiece = createPiece();
}

int getNextPiece(void)
{
    return nextPiece.type;
}