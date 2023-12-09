/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: rules.c
*Descripcion: Manejo de piezas en Tetris.
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

/************** HEADERS ***************/
#include <time.h>
#include <stdio.h>
#include <math.h>

#include "rules.h"

/************** VARIABLES GLOBALES ***************/
static long int numberOfCloksPrev;

static const char positionOfGeneration[7][4][4] = { // forma de las piezas
	{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {2, 2, 2, 0}, {0, 0, 2, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {0, 3, 3, 3}, {0, 3, 0, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {0, 4, 4, 0}, {0, 4, 4, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {0, 0, 5, 5}, {0, 5, 5, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {6, 6, 6, 0}, {0, 6, 0, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {7, 7, 0, 0}, {0, 7, 7, 0}, {0, 0, 0, 0}}};

static const int wallKickMatrix[4][4][2] = { // saltos preestablecidos para solucionar un choque
	{{-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
	{{1, 0}, {1, -1}, {0, 2}, {1, 2}},
	{{1, 0}, {1, 1}, {0, -2}, {1, -2}},
	{{-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}};

static const int wallKickMatrixToPieceI[4][4][2] = { // saltos preestablecidos par solucionar choque de la I
	{{-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
	{{-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
	{{2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
	{{1, 0}, {-2, 0}, {1, -2}, {-2, 1}}};

/*createPiece()
 * Funcion encargada de crear y devolver la estructura de una pieza
 * Recibe: -
 * Devuelve: pieza creada
 */
piece_t createPiece(void)
{
	//crea una pieza de manera aleatoria
	int numberOfPiece = (rand() % 7) + 1; 
	piece_t piece;						  
	piece.type = numberOfPiece; 

	// copiamos la forma de la pieza que corresponda a la matris de la estructura
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
		{

			piece.matrixOfPiece[i][j] = positionOfGeneration[numberOfPiece - 1][i][j];
		}
	}

	piece.rotation = 0; // le decimos en que rotacion esta
	piece.column = 4;	// la ubicamos en el espacio de la matris del juego
	piece.line = 1;

	return piece;
}

/*createSpecificPiece()
 * Funcion encargada de crear y devolver la estructura de una pieza, en especifico
 * Recibe: numberOfPiece (número de pieza de a crear)
 * Devuelve: pieza creada
 */
piece_t createSpecificPiece(int numberOfPiece)
{
	piece_t piece;

	// copiamos la forma de la pieza que corresponda a la matris de la estructura
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			piece.matrixOfPiece[i][j] = positionOfGeneration[numberOfPiece - 1][i][j];
		}
	}

	piece.rotation = 0; // le decimos en que rotacion esta
	piece.column = 4;	// la ubicamos en el espacio de la matris del juego
	piece.line = 1;

	return piece;
}

/*turnPiece()
 * Funcion encargada de rotar una pieza
 * Recibe: piece (puntero a una pieza) y matrix (el tablero donde se esta rotando)
 * Devuelve: -
 */
void turnPiece(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]) 
{
	if (piece->type == PIECE_O) // caso especial del bloque
	{
		return;
	}

	piece_t pieceTemp = *piece; // creamos una estructura pieza temporal con la que trabajar
	pieceTemp.rotation++;		 // aumentamos en uno la rotacion
	pieceTemp.rotation %= 4;	 // si llega a 4 vuelve a 0

	for (int i = 0; i < 4; i++) // rotamos la pieza temporal
	{
		for (int j = 0; j < 4; j++)
		{
			pieceTemp.matrixOfPiece[j][3 - i] = piece->matrixOfPiece[i][j]; 
		}
	}

	// nos fijamos si existe algun conflicto tras la rotacion
	if (collision(matrix, &pieceTemp) == SUCCESS) 
	{
		*piece = pieceTemp; 
	}
	// si hay un error salta al wallkick
	else if (wallKick(&pieceTemp, matrix) == SUCCESS) 
	{
		*piece = pieceTemp; // si se soluciona copia la pieza temporal con el desplazamiento
	}
	// si no soluciona el wallkick la pieza no permite rotarla						 
}

/*collision()
 * Función encargada de comprobar si una pieza choco.
 * Recibe: matrix (tablero del juego) y piece (puntero a la pieza a analizar)
 * Devuelve: int que indica si hubo o no un choque (FAIL o SUCCCESS respectivamente)
 */
int collision(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], piece_t *piece)
{
	int conflict = SUCCESS;

	for (int i = 0; i < 4; i++) // recorre la matris de la pieza
	{
		for (int j = 0; j < 4; j++)
		{
			if ((matrix[piece->line + i][piece->column + j] != 0) && (piece->matrixOfPiece[i][j] > EMPTY)) 
			{
				conflict = FAIL; // si existe una superposicion es un choque
				return conflict;
			}
		}
	}
	return conflict;
}

/*movePiece()
 * Funcion encargada de mover a los lados la pieza
 * Recibe: piece (puntero a pieza a mover), direction (dirección de movimiento: LEFT o RIGHT)
 * y matrix (el tablero de juego)
 * Devuelve: -
 */
void movePiece(piece_t *piece, int direction, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD])
{
	piece_t pieceTemp = *piece;					   
	pieceTemp.column = pieceTemp.column + direction; // suma a la column la direccion

	if (collision(matrix, &pieceTemp) == SUCCESS) 
	{
		*piece = pieceTemp; // si se soluciona copia la pieza temporal con la direccion
	}
}

/* movePieceDown()
 * Funcion encargada de mover una pieza hacia abajo
 * Recibe: piece (puntero a pieza a bajar) y matrix (tablero donde se desea bajar)
 * Devuelve: estado del movimiento (true si exitoso, false de lo contrario)
 */
bool movePieceDown(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]) 
{
	piece_t auxiliarPiece = *piece;		
	auxiliarPiece.line = auxiliarPiece.line + 1; // suma a la line la direccion

	if (collision(matrix, &auxiliarPiece) == SUCCESS) // se fija si no hay un choque
	{
		*piece = auxiliarPiece; 
		return true;
	}

	return false;
}

/* parkPiece()
 * Función encargada de guardar una pieza en su posición final
 * Recibe: piece (puntero a pieza a "estacionar") y matrix (tablero de juego)
 * Devuelve: char que indica si se estaciono la pieza (SUCCESS) o no (FAIL)
 */
char parkPiece(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD])
{
	int conflict = SUCCESS;
	
	for (int i = 0; i < 4 && conflict != FAIL; i++) // recorre la matris de la pieza
	{
		for (int j = 0; j < 4 && conflict != FAIL; j++)
		{
			// se fija que haya EMPTY en el espacio en el que se estaciona
			if (matrix[piece->line + i][piece->column + j] == EMPTY) 
			{
				// coloca la pieza en el tablero de juego
				matrix[piece->line + i][piece->column + j] = (piece->matrixOfPiece[i][j]); 
			}

			// detecta cuando la pieza este superpuesta
			else if (piece->matrixOfPiece[i][j] != EMPTY) 
			{
				conflict = FAIL;
			}
		}
	}

	return conflict;
}


/* wallKick()
 * Función encargada de comprobar si al girar una pieza esta choca ysi esto sucede la acomoda
 * Recibe: piece (puntero a pieza a comodar) y matrix (tablero de juego)
 * Devuelve: un int que indica si logro solucionar el choque (SUCCESS) o no (FAIL)
 */
int wallKick(piece_t *piece, char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD])
{
	int conflict = FAIL; 
	int rotation = piece->rotation;
	int test = 0;

	// separo el caso especial de la pieza I
	if (piece->type == PIECE_I)
	{
		// corre hasta que se agoten las pruebas o el conflicto de BIEN
		while (test < 4 && conflict == FAIL)
		{
			piece->line += wallKickMatrixToPieceI[rotation][test][1];	// desplazamiento en x
			piece->column += wallKickMatrixToPieceI[rotation][test][0]; // desplazamiento en y
			conflict = collision(matrix, piece);// chequeo si se resolvio el choque

			// si el choque no se resolvio
			if (conflict == FAIL)
			{
				piece->line -= wallKickMatrixToPieceI[rotation][test][1]; // quito desplazamientos
				piece->column -= wallKickMatrixToPieceI[rotation][test][0];
				test++;
			}
		}
	}

	else
	{
		// mismo que con el caso especial salvo el cambio de matris
		while (test < 4 && conflict == FAIL)
		{
			piece->line += wallKickMatrix[rotation][test][0];
			piece->column += wallKickMatrix[rotation][test][1];
			conflict = collision(matrix, piece);

			if (conflict == FAIL)
			{
				piece->line -= wallKickMatrix[rotation][test][0];
				piece->column -= wallKickMatrix[rotation][test][1];
				test++;
			}
		}
	}

	return conflict;
}

/* deleteLine()
 * Función encargada de borrar las filas que se completaron
 * Recibe: matrix (tablero de juego), linesOfMatrix (arreglo donde se colocan sucesivamente,
 *  las filas donde hubo tetris, para finalmente colocar el terminador END_OF_ARRAY) y
 * isTetris(puntero donde se devuelve si hubo tetris - true - o no -false-)
 * Devuelve: puntaje que se ha conseguido sumar
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

		if (counter == 10)   //si hay tetris borro la fila
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

	arrayOfLinesWithTetris[linesWithTetris] = END_OF_ARRAY; //se coloca el terminador
	return score >= 400 ? score * 2 : score; //si se hacen cuatro tetris, hay un multiplicador
}

/* INICIALIZARTIEMPO()
 * Función encargada de inicializar el timer
 * Recibe: -
 * Devuelve: -
 */
void initTime(void)
{
	numberOfCloksPrev = clock(); //guardamos el número de clocks del procesador
}

/* checkElapsedTime()
 * Función encargada de verificar si ha transcurrido un determinado tiempo tras
 * la inicialización 
 * Recibe: timeStep (tiempo a contrastar si ha transcurrido o no)
 * Devuelve: si ha transcurrido el tiempo (true) o no (false)
 */
bool checkElapsedTime(double timeStep)
{
	//verifica la diferencia de clocks entre cada llamada
	long int diffOfClocks = clock() - numberOfCloksPrev;

	float elapsedTime = ((float)diffOfClocks) / CLOCKS_PER_SEC; 

	// si la diferencia es mayor a timeStep, devuelve true y reinicia el tiempo
	if (elapsedTime >= timeStep) 
	{
		initTime();
		return true;
	}
	else
	{
		return false;
	}
}