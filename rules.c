/*HEADERS*/
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "rules.h"

static long int numberOfCloksPrev;

const char positionOfGeneration[7][4][4] = { // forma de las piezas
	{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {2, 2, 2, 0}, {0, 0, 2, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {0, 3, 3, 3}, {0, 3, 0, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {0, 4, 4, 0}, {0, 4, 4, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {0, 0, 5, 5}, {0, 5, 5, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {6, 6, 6, 0}, {0, 6, 0, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {7, 7, 0, 0}, {0, 7, 7, 0}, {0, 0, 0, 0}}};

const int wallKickMatrix[4][4][2] = { // saltos preestablecidos para solucionar un choque
	{{-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
	{{1, 0}, {1, -1}, {0, 2}, {1, 2}},
	{{1, 0}, {1, 1}, {0, -2}, {1, -2}},
	{{-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}};

const int wallKickMatrixToPieceI[4][4][2] = { // saltos preestablecidos par solucionar choque de la I
	{{-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
	{{-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
	{{2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
	{{1, 0}, {-2, 0}, {1, -2}, {-2, 1}}};


/*CREATE_PIECE()
 * Funcion encargada de crear y devolver la estructura de una pieza
 * Recibe: -
 * Devuelve: estructura piece_t con la pieza creada
 */
piece_t createPiece(void)
{
	int numberOfPiece = (rand() % 7) + 1; // escoge al azar que figura sera
	piece_t piece;						  // la crea

	piece.type = numberOfPiece; // le da su forma
	for (int i = 0; i < 4; i++) // copiamos la forma de la pieza que corresponda a la matriz de la estructura
	{
		for (int j = 0; j < 4; j++)
		{

			piece.matrixOfPiece[i][j] = positionOfGeneration[numberOfPiece - 1][i][j];
		}
	}

	piece.rotation = 0; // le decimos en que rotacion esta
	piece.column = 4;	// la ubicamos en el espacio de la matriz del juego
	piece.line = 1;
	return piece;
}

/*TURN_PIECE()
 * Funcion encargada de rotar una pieza
 * Recibe: puntero a piece_t con la pieza a girar y una matriz con el tablero del juego.
 * Devuelve: -
 */
void turnPiece(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]) // funcion para rotar una pieza
{
	if (piece->type == PIECE_O) // caso especial del bloque
	{
		return;
	}

	piece_t piece_temp = *piece; // creamos una estructura pieza temporal con la que trabajar
	piece_temp.rotation++;		 // aumentamos en uno la rotacion
	piece_temp.rotation %= 4;	 // si llega a 4 vuelve a 0

	for (int i = 0; i < 4; i++) // rotamos la pieza temporal
	{
		for (int j = 0; j < 4; j++)
		{
			piece_temp.matrixOfPiece[j][3 - i] = piece->matrixOfPiece[i][j]; // regla de rotacion
		}
	}
	// nos fijamos si existe algun conflicto tras la rotacion
	if (collision(matrix, &piece_temp) == SUCCESS) // si no lo hay
	{
		*piece = piece_temp; // copia la pieza temporal a la pieza del juego
	}
	else if (wallKick(&piece_temp, matrix) == SUCCESS) // si hay un error salta al wallkick
	{
		*piece = piece_temp; // si se soluciona copia la pieza temporal con el desplazamiento
	}						 // sino soluciona el wallkick la pieza no permite rotarla
}

/*COLLISION()
 * Función encargada de comprobar si una pieza chocó contra un borde
 * Recibe: una matriz con el tablero del juego y un puntero a piece_t con la pieza
 * Devuelve: int que indica si hubo o no un choque
 */
int collision(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], piece_t *piece)
{
	int conflict = SUCCESS;
	for (int i = 0; i < 4; i++) // recorre la matriz de la pieza
	{
		for (int j = 0; j < 4; j++)
		{
			if ((matrix[piece->line + i][piece->column + j] != 0) && (piece->matrixOfPiece[i][j] > EMPTY)) // compara la matriz del juego con la del la pieza
			{
				conflict = FAIL; // si existe una superposicion es un choque
				return conflict;
			}
		}
	}
	return conflict;
}

/*MOVE_PIECE()
 * Funcion encargada de mover a los lados la pieza.
 * Recibe: puntero a piece_t con la pieza a mover, int con la dirección de movimiento y
 * una matriz con el tablero de juego.
 * Devuelve: -
 */
void movePiece(piece_t *piece, int direction, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD])
{

	piece_t piece_temp = *piece;					   // creamos una estructura pieza temporal con la que trabajar
	piece_temp.column = piece_temp.column + direction; // suma a la column la direccion

	if (collision(matrix, &piece_temp) == SUCCESS) // se fija si no hay un choque
	{
		*piece = piece_temp; // si se soluciona copia la pieza temporal con la direccion
	}
}

/* MOVE_PIECE_DOWN()
 * Funcion encargada de mover una pieza hacia abajo
 * Recibe: puntero a piece_t con la pieza a bajar, una matriz con el tablero del juego
 * Devuelve: un flag en caso de no poder bajar, false es que no pudo realizar el movimiento
 */
bool movePieceDown(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]) // REVISAR SI NO CONVIENE QUE AVISE EN EL CASO DE QUE NO PUEDA BAJAR MAS PARA INICIAR EL TIMER ANTES DE ESTACIONARLA <3 FACU
{
	piece_t auxiliarPiece = *piece;				 // creamos una estructura pieza temporal con la que trabajar
	auxiliarPiece.line = auxiliarPiece.line + 1; // suma a la line la direccion

	if (collision(matrix, &auxiliarPiece) == SUCCESS) // se fija si no hay un choque
	{
		*piece = auxiliarPiece; // si se soluciona copia la pieza temporal con la direccion
		return true;
	}
	return false;
}

/* PARK_PIECE()
 * Función encargada de guardar una pieza en su posición final
 * Recibe: puntero a  piece_t con la pieza a "estacionar", una matriz con el tablero del juego actual
 * Devuelve: un char indicando si se estacionó la pieza por fuera de la matriz del juego
 */
char parkPiece(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD])
{
	int conflict = SUCCESS;
	for (int i = 0; i < 4; i++) // recorre la matriz de la pieza
	{
		for (int j = 0; j < 4; j++)
		{
			if (matrix[piece->line + i][piece->column + j] == EMPTY) // se fija que no haya EMPTY en el espacio en el que se estaciona
			{
				matrix[piece->line + i][piece->column + j] = (piece->matrixOfPiece[i][j]); // pega la pieza en la matriz del juego
			}
			else if (piece->matrixOfPiece[i][j] != EMPTY) // detecta cuando la pieza este superpuesta con un borde
			{
				conflict = SUCCESS; // termina el juego
				return conflict;
			}
		}
	}
	return conflict;
}

/* WALL_KICK()
 * Función encargada de comprobar si al girar una pieza esta choca contra un borde y
 * si esto sucede la acomoda
 * Recibe: puntero a piece_t pieza a "estacionar", una matriz con el tablero del juego actual
 * Devuelve: un int que indica si logro solucionar el choque
 */
int wallKick(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD])
{
	int conflict = SUCCESS; // inicializo variables
	int rotation = piece->rotation;
	int test = 0;

	if (piece->type == PIECE_I) // separo el caso especial de la pieza I
	{
		while (test < 4) // corre hasta que se agoten las pruebas o el conflicto de BIEN
		{
			piece->line += wallKickMatrixToPieceI[rotation][test][0];	// desplazamiento en x
			piece->column += wallKickMatrixToPieceI[rotation][test][1]; // desplazamiento en y
			conflict = collision(matrix, piece);						// chequeo si se resolvio el choque
			if (conflict == SUCCESS)									// si el choque ya se resolvio nos devuelve el desplazamiento y nos avisa
			{
				return conflict;
			}
			piece->line -= wallKickMatrixToPieceI[rotation][test][0]; // quito desplazamientos
			piece->column -= wallKickMatrixToPieceI[rotation][test][1];
			test++;
		}
	}
	else
	{
		while (test < 4) // mismo que con el caso especial salvo el cambio de matriz
		{
			piece->line += wallKickMatrix[rotation][test][0];
			piece->column += wallKickMatrix[rotation][test][1];
			conflict = collision(matrix, piece);
			if (conflict == SUCCESS)
			{
				return conflict;
			}
			piece->line -= wallKickMatrix[rotation][test][0];
			piece->column -= wallKickMatrix[rotation][test][1];
			test++;
		}
	}
	return conflict;
}

/* DELETE_LINE()
 * Función encargada de borrar las filas que se completaron
 * Recibe: una matriz con el tablero actual, una matis de char con las lineas donde ocurre el tetris
 * un puntero a un bool que va a indicar si se "hizo TETRIS", se eliminan 4 filas consecutivas de un movimiento
 * Devuelve: Puntaje que suma, dependiendo de la cantidad de filas
 * que se borraron (considerando el caso de "hacer TETRIS")
 */
int deleteLine(char board[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], char arrayOfLinesWithTetris[HEIGHT_OF_BOARD], bool *isTetris)
{
	int score = 0;
	int i, counter, linesWithTetris;
	int corrector = 0;

	for (i = HEIGHT_OF_BOARD - 2, linesWithTetris = 0; i >= 1; i--)
	{
		counter = 0;
		int j;

		for (j = 1; j < WIDTH_OF_BOARD - 1; j++)
		{
			if (board[i][j] > 0)
			{
				counter++;
			}
		}

		if (counter == 10)
		{
			arrayOfLinesWithTetris[linesWithTetris++] = i - corrector++;
			*isTetris = true;

			// borramos la line completada
			for (int m = 1; m < WIDTH_OF_BOARD - 1; m++)
			{
				board[i][m] = EMPTY;
			}

			score += 100;

			// baja las filas superiores a la borrada
			int k, g;
			for (k = i; k >= 1; k--)
			{
				for (g = 1; g < 11; g++)
				{
					if (board[k - 1][g] != BORDER)
					{
						board[k][g] = board[k - 1][g];
					}
				}
			}

			i++;
		}
	}

	arrayOfLinesWithTetris[linesWithTetris] = END_OF_ARRAY;
	return score >= 400 ? score * 2 : score;
}

/* INIT_TIME()
 * Función encargada de inicializar el timer
 * Recibe: -
 * Devuelve: -
 */
void initTime(void)
{
	numberOfCloksPrev = clock();
}

/* CHECK_ELAPSED_TIME()
 * Función encargada de devolver el tiempo transcurrido
 * Recibe: double con el timestep
 * Devuelve: booleano que indica si pudo obtener el tiempo transcurrido
 */
bool checkElapsedTime(double timestep)
{
	long int diffOfClocks = clock() - numberOfCloksPrev;

	float elapsedTime = ((float)diffOfClocks) / CLOCKS_PER_SEC;

	if (elapsedTime >= timestep)
	{
		initTime();
		return true;
	}
	else
	{
		return false;
	}
}