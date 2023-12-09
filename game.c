/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: game.c
*Descripcion: módulo encargado de jugar al Tetris
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/


/************** HEADERS ***************/
#include <stdbool.h>
#include "game.h"
#include "rules.h"

/************** VARIABLES ***************/
static piece_t nextPiece;
static bool haveHold;
static int holdPiece;

/*playTetris()
 * Función encargada de ir moviendo las piezas en base a los comandos enviados y llamar a las
 * Recibe: movimiento ( movimiento a realizar en el tablero), piece (puntero a una pieza), matrix (el tablero donde se esta rotando)
 *			score (puntero al puntaje del jugador), y gameMode (estructura del la dificultad del juego).
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
                haveHold=false;
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
            haveHold=false;
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
                haveHold=false;
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

/*createBoardforNotEmpty()
 * Funcion encargada de llenar el tablero con piezas
 * Recibe: matrix (tablero del juego a llenar)
 * Devuelve: --
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

/*initPiece()
 * Funcion encargada inicializar la siguiente pieza y la pieza holdeada.
 * Recibe: --
 * Devuelve: --
 */
void initPiece(void)
{
    nextPiece = createPiece();
    holdPiece = EMPTY;
    haveHold = false;
}

/*getNextPiece()
 * Funcion encargada de decir que pieza es la siguiente
 * Recibe: --
 * Devuelve: el tipo de la siguiente pieza
 */
int getNextPiece(void)
{
    return nextPiece.type;
}


/*hold()
* Funcion encargada de holdear una pieza.
* Recibe: pieza 
* Devuelve: un bool si se puedo holdear la pieza pieza o no
*/
bool hold (piece_t *piece)
 {
    
    if(haveHold == true)
    {
        return false;
    }
    else if (haveHold == false && holdPiece == EMPTY)
    {
        holdPiece = piece->type;
        *piece = nextPiece;
        nextPiece = createPiece();
        haveHold = true;
        initTime();
    }
    else if (haveHold == false)
    {
        int auxPiece = piece->type;
        *piece = createSpecificPiece(holdPiece);
        holdPiece = auxPiece;
        haveHold = true;
        initTime();
    }
    return true;
 }

/*getNextPiece()
 * Funcion encargada de decir que pieza es la almacenada
 * Recibe: --
 * Devuelve: el tipo de la siguiente pieza
 */
int getHoldPiece(void)
{
    return holdPiece;
}

/*canHold()
 * Funcion encargada de decir si se puede holdear una pieza o no
 * Recibe: --
 * Devuelve: booleano si se puede holdear una pieza o no
 */
bool canHold(void)
{
    return !haveHold;
}