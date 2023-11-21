
#include "reglas.h"

static time_t tiempo_ini; // timer

const char arreglo_piezas_0[7][4][4] = { // forma de las piezas
	{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {2, 2, 2, 0}, {0, 0, 2, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {0, 3, 3, 3}, {0, 3, 0, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {0, 4, 4, 0}, {0, 4, 4, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {0, 0, 5, 5}, {0, 5, 5, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {6, 6, 6, 0}, {0, 6, 0, 0}, {0, 0, 0, 0}},
	{{0, 0, 0, 0}, {7, 7, 0, 0}, {0, 7, 7, 0}, {0, 0, 0, 0}}};

const int wall_kick_matrix[4][4][2] = { // saltos preestablecidos para solucionar un choque
	{{-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
	{{1, 0}, {1, -1}, {0, 2}, {1, 2}},
	{{1, 0}, {1, 1}, {0, -2}, {1, -2}},
	{{-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}};

const int wall_kick_matrix_i[4][4][2] = { // saltos preestablecidos par solucionar choque de la I
	{{-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
	{{-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
	{{2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
	{{1, 0}, {-2, 0}, {1, -2}, {-2, 1}}};

/*BLOQUE_T()
 * Funcion encargada de crear y devolver la estructura de una pieza
 * Recibe: -
 * Devuelve: estructura bloque_t con la pieza creada
 */
bloque_t Crear_Pieza(void)
{
	int n_pieza = (rand() % 7) + 1; // escoge al azar que figura sera
	bloque_t pieza;					// la crea

	pieza.tipo = n_pieza;		// le da su forma
	for (int i = 0; i < 4; i++) // copiamos la forma de la pieza que corresponda a la matris de la estructura
	{
		for (int j = 0; j < 4; j++)
		{

			pieza.matrix_pieza[i][j] = arreglo_piezas_0[n_pieza - 1][i][j];
		}
	}

	pieza.rotacion = 0; // le decimos en que rotacion esta
	pieza.columna = 4;	// la ubicamos en el espacio de la matris del juego
	pieza.fila = 1;
	return pieza;
}

/*GIRAR_PIEZA()
 * Funcion encargada de rotar una pieza
 * Recibe: estructura bloque_t con la pieza a girar y char matris [][12]
 * con tablero del juego.
 * Devuelve: -
 */
void Girar_Pieza(bloque_t *pieza, char matris[][12]) // funcion para rotar una pieza
{
	if (pieza->tipo == PIEZA_O) // caso especial del bloque
	{
		return;
	}

	bloque_t pieza_temp = *pieza; // creamos una estructura pieza temporal con la que trabajar
	pieza_temp.rotacion++;		  // aumentamos en uno la rotacion
	pieza_temp.rotacion %= 4;	  // si llega a 4 vuelve a 0

	for (int i = 0; i < 4; i++) // rotamos la pieza temporal
	{
		for (int j = 0; j < 4; j++)
		{
			pieza_temp.matrix_pieza[j][3 - i] = pieza->matrix_pieza[i][j]; // regla de rotacion
		}
	}
	printf("gira \n");						 // nos fijamos si existe algun conflicto tras la rotacion
	if (choque(matris, &pieza_temp) == BIEN) // si no lo hay
	{
		*pieza = pieza_temp; // copia la pieza temporal a la pieza del juego
	}
	else if (wall_kick(&pieza_temp, matris) == BIEN) // si hay un error salta al wallkick
	{
		printf("gira wall kick \n");
		*pieza = pieza_temp; // si se soluciona copia la pieza temporal con el desplazamiento
	}						 // sino soluciona el wallkick la pieza no permite rotarla
}

/*CHOQUE()
 * Función encargada de comprobar si una pieza choco contra un borde
 * Recibe: char matris[][12] con tablero del juego y bloque_t con la pieza
 * Devuelve: int que indica si hubo o no un choque
 */
int choque(char matris[][12], bloque_t *pieza)
{
	int conflicto = BIEN;
	for (int i = 0; i < 4; i++) // recorre la matris de la pieza
	{
		for (int j = 0; j < 4; j++)
		{
			if ((matris[pieza->fila + i][pieza->columna + j] != 0) && (pieza->matrix_pieza[i][j] > NADA)) // compara la matris del juego con la del la pieza
			{
				conflicto = MAL; // si existe una superposicion es un choque
				printf("choca\n");
				return conflicto;
			}
		}
	}
	return conflicto;
}

/*MOVER_PIEZA()
 * Funcion encargada de mover a los lados la pieza
 * Recibe: bloque_t con la pieza a mover, int con la direcci�n de movimiento,
 * char matris[][12] con el tablero de juego
 * Devuelve: -
 */
void Mover_Pieza(bloque_t *pieza, int direccion, char matris[][12])
{

	bloque_t pieza_temp = *pieza;						 // creamos una estructura pieza temporal con la que trabajar
	pieza_temp.columna = pieza_temp.columna + direccion; // suma a la columna la direccion

	if (choque(matris, &pieza_temp) == BIEN) // se fija si no hay un choque
	{
		*pieza = pieza_temp; // si se soluciona copia la pieza temporal con la direccion
	}
}

/* BAJAR_PIEZA()
 * Funcion encargada de mover una pieza hacia abajo
 * Recibe: bloque_t pieza a bajar, char matris[][12]
 * tablero del juego
 * Devuelve: un flag en caso de no poder bajar, false es que no pudo realizar el movimiento
 */
bool Bajar_Pieza(bloque_t *pieza, char matris[][12]) // REVISAR SI NO CONVIENE QUE AVISE EN EL CASO DE QUE NO PUEDA BAJAR MAS PARA INICIAR EL TIMER ANTES DE ESTACIONARLA <3 FACU
{
	bloque_t pieza_temp = *pieza;		   // creamos una estructura pieza temporal con la que trabajar
	pieza_temp.fila = pieza_temp.fila + 1; // suma a la fila la direccion

	if (choque(matris, &pieza_temp) == BIEN) // se fija si no hay un choque
	{
		*pieza = pieza_temp; // si se soluciona copia la pieza temporal con la direccion
		return true;
	}
	return false;
}

/* ESTACIONAR()
 * Función encargada de guardar una pieza en su posición final
 * Recibe: bloque_t pieza a "estacionar", char matris [][12]
 * tablero del juego actual
 * Devuelve: si se estaciono la pieza por fuera de la matris del juego
 */
char Estacionar(bloque_t *pieza, char matris[][12])
{
	int conflicto = BIEN;
	for (int i = 0; i < 4; i++) // recorre la matris de la pieza
	{
		for (int j = 0; j < 4; j++)
		{
			if (matris[pieza->fila + i][pieza->columna + j] == NADA) // se fija que no haya nada en el espacio en el que se estaciona
			{
				matris[pieza->fila + i][pieza->columna + j] = (pieza->matrix_pieza[i][j]); // pega la pieza en la matris del juego
			}
			else if (pieza->matrix_pieza[i][j] != NADA) // detecta cuando la pieza este superpuesta con un borde
			{
				conflicto = MAL; // termina el juego
				return conflicto;
			}
		}
	}
	return conflicto;
}

/* WALL_KICK()
 * Función encargada de comprobar si al girar una pieza esta choca contra un borde y
 * si esto sucede la acomoda
 * Recibe: bloque_t pieza a "estacionar", char matris [][12]
 * tablero del juego actual
 * Devuelve: si logro solucionar el choque
 */
int wall_kick(bloque_t *pieza, char matris[][12])
{
	int conflicto = MAL; // inicializo variables
	int rotacion = pieza->rotacion;
	int prueba = 0;

	if (pieza->tipo == PIEZA_I) // separo el caso especial de la pieza I
	{
		while (prueba < 4) // corre hasta que se agoten las pruebas o el conflicto de BIEN
		{
			pieza->fila += wall_kick_matrix_i[rotacion][prueba][0];	   // desplazamiento en x
			pieza->columna += wall_kick_matrix_i[rotacion][prueba][1]; // desplazamiento en y
			conflicto = choque(matris, pieza);						   // chequeo si se resolvio el choque
			if (conflicto == BIEN)									   // si el choque ya se resolvio nos devuelve el desplazamiento y nos avisa
			{
				return conflicto;
			}
			pieza->fila -= wall_kick_matrix_i[rotacion][prueba][0]; // quito desplazamientos
			pieza->columna -= wall_kick_matrix_i[rotacion][prueba][1];
			prueba++;
		}
	}
	else
	{
		while (prueba < 4) // mismo que con el caso especial salvo el cambio de matris
		{
			printf("entra al wall kick \n");
			pieza->fila += wall_kick_matrix[rotacion][prueba][0];
			pieza->columna += wall_kick_matrix[rotacion][prueba][1];
			conflicto = choque(matris, pieza);
			if (conflicto == BIEN)
			{
				return conflicto;
			}
			pieza->fila -= wall_kick_matrix[rotacion][prueba][0];
			pieza->columna -= wall_kick_matrix[rotacion][prueba][1];
			prueba++;
		}
	}
	return conflicto;
}

/* BORRARFILA()
 * Función encargada de borrar las filas que se completaron
 * Recibe: char tablero[18][12] con el tablero actual
 * Devuelve: Puntaje que suma, dependiendo de la cantidad de filas
 * que se borraron (considerando el caso de "hacer TETRIS", eliminar 4 filas de un movimiento
 */
int borrarFila(char tablero[18][12], char filas_tetris[18], bool *tetris)
{
	int puntaje = 0;
	int i, contador, filas_con_tetris;
	int corrector = 0;

	for (i = LARGO_TABLERO - 2, filas_con_tetris = 0; i >= 1; i--)
	{
		contador = 0;
		int j;

		for (j = 1; j < ANCHO_TABLERO - 1; j++)
		{
			if (tablero[i][j] > 0)
			{
				contador++;
			}
		}

		if (contador == 10)
		{
			filas_tetris[filas_con_tetris++] = i - corrector++;
			*tetris = true;

			//borramos la fila completada
			for (int m = 1; m < ANCHO_TABLERO - 1; m++)
			{
				tablero[i][m] = NADA; 
			}

			puntaje += 100;

			//baja las filas superiores a la borrada
			int k, g;
			for (k = i; k >= 1; k--)
			{
				for ( g = 1; g < 11; g++)
				{
					if (tablero[k - 1][g] != BORDE)
					{
						tablero[k][g] = tablero[k - 1][g];
					}
				}
			}

			i++;

		}
	}

	filas_tetris[filas_con_tetris] = FINAL_DEL_ARREGLO;
	return puntaje >= 400 ? puntaje * 2 : puntaje;
}



/* INICIALIZARTIEMPO()
 * Función encargada de inicializar el timer
 * Recibe: -
 * Devuelve: -
 */
void inicializarTiempo(void)
{
	tiempo_ini = time(NULL);
}

/* TIEMPO_TRANSCURRIDO()
 * Función encargada de devolver el tiempo transcurrido
 * Recibe: double con el timestep
 * Devuelve: booleano que indica si pudo obtener el tiempo transcurrido
 */

bool tiempo_transcurrido(double timestep)
{
	time_t tiempo_actual = time(NULL);

	if (difftime(tiempo_actual, tiempo_ini) >= timestep)
	{
		inicializarTiempo();
		return true;
	}
	else
	{
		return false;
	}
}
