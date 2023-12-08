#include <stdlib.h>
#include <stdio.h>
#include "game_al.h"
#include "buttons_al.h"
#include "game.h"

#define BOARD_WIDTH WIDTH_OF_BOARD
#define BOARD_LENGHT HEIGHT_OF_BOARD

#define BOARD_START_X 400
#define BOARD_START_Y 100

#define SQUARE_SIZE 35
#define SQUARE_SIG_SIZE 35

#define SIZE_OF_SCORE_WINDOW_X (6 * SQUARE_SIG_SIZE)
#define SIZE_OF_SCORE_WINDOW_Y 100
#define SCORE_WINDOW_POS_X (BOARD_START_X + BOARD_WIDTH * SQUARE_SIZE + 50)
#define SCORE_WINDOW_POS_Y BOARD_START_Y

#define SIZE_OF_NEXT_PIECE_WINDOW_X (SIZE_OF_SCORE_WINDOW_X)
#define SIZE_OF_NEXT_PIECE_WINDOW_Y 200
#define NEXT_PIECE_WINDOW_POS_X SCORE_WINDOW_POS_X
#define NEXT_PIECE_WINDOW_POS_Y (SCORE_WINDOW_POS_Y + SIZE_OF_SCORE_WINDOW_Y + 100)

#define ACTIVE_GAME_MODES_POS_X (BOARD_START_X - 150)
#define ACTIVE_GAME_MODES_POS_Y (BOARD_START_Y + 2 * SQUARE_SIZE)

#define SIZE_OF_GAME_MODE_WINDOW_X 100
#define WINDOW_POS_MODE_X (BOARD_START_X - SIZE_OF_GAME_MODE_WINDOW_X)
#define WINDOW_POS_MODE_Y BOARD_START_Y

#define TURN_AL ALLEGRO_KEY_W
#define TURN_AL_2 ALLEGRO_KEY_UP
#define RIGHT_AL ALLEGRO_KEY_D
#define RIGHT_AL_2 ALLEGRO_KEY_RIGHT
#define LEFT_AL ALLEGRO_KEY_A
#define LEFT_AL_2 ALLEGRO_KEY_LEFT
#define DOWN_AL ALLEGRO_KEY_S
#define DOWN_AL_2 ALLEGRO_KEY_DOWN
#define PAUSE ALLEGRO_KEY_ESCAPE
#define DROP ALLEGRO_KEY_SPACE

#define SIZE_OF_TITLE 200

enum bordes
{
	EMPTY_B = BORDER + 1,
	PIECE_I_B,
	PIECE_J_B,
	PIECE_L_B,
	PIECE_O_B,
	PIECE_S_B,
	PIECE_T_B,
	PIECE_Z_B,
	BORDER_B
};
enum game_over_options
{
	PLAY,
	SCORE
};
enum pause_options
{
	RESUME,
	QUIT
};

static const int posPieza[7][4][2] = {
	{{SQUARE_SIG_SIZE, SQUARE_SIG_SIZE * 2.5}, {SQUARE_SIG_SIZE * 2, SQUARE_SIG_SIZE * 2.5}, {3 * SQUARE_SIG_SIZE, SQUARE_SIG_SIZE * 2.5}, {4 * SQUARE_SIG_SIZE, SQUARE_SIG_SIZE * 2.5}},	  // I   0
	{{SQUARE_SIG_SIZE * 1.5, 2 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 2.5, 2 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 3.5, 2 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 3.5, 3 * SQUARE_SIG_SIZE}}, // J    0
	{{SQUARE_SIG_SIZE * 1.5, 3 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 1.5, 2 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 2.5, 2 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 3.5, 2 * SQUARE_SIG_SIZE}}, // L  0
	{{SQUARE_SIG_SIZE * 2, 2 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 2, 3 * SQUARE_SIG_SIZE}, {3 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE}, {3 * SQUARE_SIG_SIZE, 3 * SQUARE_SIG_SIZE}},		  // O    0
	{{SQUARE_SIG_SIZE * 1.5, 3 * SQUARE_SIG_SIZE}, {2.5 * SQUARE_SIG_SIZE, 3 * SQUARE_SIG_SIZE}, {2.5 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE}, {3.5 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE}}, // S
	{{SQUARE_SIG_SIZE * 1.5, 2 * SQUARE_SIG_SIZE}, {2.5 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE}, {3.5 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE}, {2.5 * SQUARE_SIG_SIZE, 3 * SQUARE_SIG_SIZE}}, // T   0
	{{3.5 * SQUARE_SIG_SIZE, 3 * SQUARE_SIG_SIZE}, {2.5 * SQUARE_SIG_SIZE, 3 * SQUARE_SIG_SIZE}, {2.5 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE}, {1.5 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE}}, // Z   0
};

static void drawBoard(char board[BOARD_LENGHT][BOARD_WIDTH], char prediction_board[BOARD_LENGHT][BOARD_WIDTH], ALLEGRO_COLOR squareColors[], ALLEGRO_COLOR squareBorderColors[]);
static void initBoardColors(ALLEGRO_COLOR squareColors[]);
static void initBoardBorderColors(ALLEGRO_COLOR squareColors[]);
static void drawActiveModes(element_t *elem, game_mode_t gameModes);
static void showNextPiece(ALLEGRO_COLOR squareColors[], ALLEGRO_COLOR squareBorderColors[], element_t *elem);
static void showScore(element_t *elem, int score, highscore_t *highscore);
static void isTetrisAnimation(char arrayOfLinesWithTetris[HEIGHT_OF_BOARD], ALLEGRO_COLOR squareColors[], element_t *elem);
static void gameOver(window_state_t *state, element_t *elem, int score, highscore_t *highscore);
static void drawPauseMenu(window_state_t *state, element_t *elem, bool *playing);

/*drawBoard()
 * Funcion encargada de dibujar el tablero del juego
 * Recibe: board(tablero a dibujar), prediction_board (tablero con la informacion de donde va a caer la pieza)
 *			squareColors (arreglo de los colores de las piezas), squareBorderColors (arreglo de los colores de los bordes de las piezas)
 * Devuelve: --
 */
static void drawBoard(char board[BOARD_LENGHT][BOARD_WIDTH], char prediction_board[BOARD_LENGHT][BOARD_WIDTH], ALLEGRO_COLOR squareColors[], ALLEGRO_COLOR squareBorderColors[])
{
	int i;
	int j;
	for (i = 0; i < BOARD_LENGHT; i++) //dibujo cada pieza 
	{
		for (j = 0; j < BOARD_WIDTH; j++)
		{
			float x1 = BOARD_START_X + j * SQUARE_SIZE; 
			float y1 = BOARD_START_Y + i * SQUARE_SIZE;

			al_draw_filled_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, squareColors[(int)board[i][j]]);

			al_draw_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, squareBorderColors[(int)board[i][j]], 2);
		}
	}

	// dibujamos la predicción de la caida de la pieza
	for (i = 0; i < BOARD_LENGHT; i++)
	{
		for (j = 0; j < BOARD_WIDTH; j++)
		{
			float x1 = BOARD_START_X + j * SQUARE_SIZE;
			float y1 = BOARD_START_Y + i * SQUARE_SIZE;

			if (prediction_board[i][j] != EMPTY && prediction_board[i][j] != board[i][j])
			{
				al_draw_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, squareBorderColors[(int)prediction_board[i][j]], 3);
			}
		}
	}

}


/*showScore()
 * Funcion encargada de mostar el puntaje actual del jugador
 * Recibe: elem (puntero a la estructura con todos los punteros de allegro),score (el puntaje que alcanzo el jugador),
 *			 y highscore (puntero a la estructura que almacena los puntajes mas altos)
 * Devuelve: --
 */
static void showScore(element_t *elem, int score, highscore_t *highscore)
{
	static bool isHighScore;
	//si hubo highscore se muestra en pantalla
	int position = checkIfHighscore(score, highscore);
	static int prevPosition;

	isHighScore = position <= NUMBER_OF_PLAYERS;
	if (!isHighScore)
	{
		prevPosition = NUMBER_OF_PLAYERS + 1;
	}

	//Nombre del cuadro
	al_draw_text(elem->buttonsBorder, al_map_rgb(66, 67, 62), SCORE_WINDOW_POS_X + SIZE_OF_SCORE_WINDOW_X / 2, SCORE_WINDOW_POS_Y - 3 * SIZE_OF_SCORE_WINDOW_Y / 5 - 10, ALLEGRO_ALIGN_CENTER, "SCORE");
	al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), SCORE_WINDOW_POS_X + SIZE_OF_SCORE_WINDOW_X / 2, SCORE_WINDOW_POS_Y - 3 * SIZE_OF_SCORE_WINDOW_Y / 5 - 10, ALLEGRO_ALIGN_CENTER, "SCORE");

	//Recuadro de score
	al_draw_filled_rectangle(SCORE_WINDOW_POS_X, SCORE_WINDOW_POS_Y, SCORE_WINDOW_POS_X + SIZE_OF_SCORE_WINDOW_X, SCORE_WINDOW_POS_Y + SIZE_OF_SCORE_WINDOW_Y, al_map_rgb(66, 67, 62));
	al_draw_rectangle(SCORE_WINDOW_POS_X, SCORE_WINDOW_POS_Y, SCORE_WINDOW_POS_X + SIZE_OF_SCORE_WINDOW_X, SCORE_WINDOW_POS_Y + SIZE_OF_SCORE_WINDOW_Y, isHighScore ? al_map_rgb(190, 171, 30) : al_map_rgb(124, 121, 108), 6);

	//Dibujo del score dado
	char buffer[6];
	snprintf(buffer, sizeof(buffer), "%d", score);
	al_draw_text(elem->buttonsBorder, al_map_rgb(0, 0, 0), SCORE_WINDOW_POS_X + SIZE_OF_SCORE_WINDOW_X / 2, SCORE_WINDOW_POS_Y + SIZE_OF_SCORE_WINDOW_Y / 5, 1, buffer);
	al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), SCORE_WINDOW_POS_X + SIZE_OF_SCORE_WINDOW_X / 2, SCORE_WINDOW_POS_Y + SIZE_OF_SCORE_WINDOW_Y / 5, 1, buffer);

	//si se realiza una actuaización se realiza el sonido que lo indica
	if (position <= NUMBER_OF_PLAYERS && prevPosition > position)
	{
		isHighScore = true;
		while(!al_play_sample(elem->effectHighscore, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
		prevPosition = position;
	}

	if (isHighScore)
	{
		snprintf(buffer, sizeof(buffer), "%d", position);
		al_draw_text(elem->highscoreNews, al_color_name("yellow"), SCORE_WINDOW_POS_X + SIZE_OF_SCORE_WINDOW_X / 2, SCORE_WINDOW_POS_Y, ALLEGRO_ALIGN_CENTER, "HIGH SCORE");
		al_draw_text(elem->highscoreNews, al_color_name("yellow"), SCORE_WINDOW_POS_X + SIZE_OF_SCORE_WINDOW_X / 2 - 15, SCORE_WINDOW_POS_Y + SIZE_OF_SCORE_WINDOW_Y - 35, 0, "#");
		al_draw_text(elem->highscoreNews, al_color_name("yellow"), SCORE_WINDOW_POS_X + SIZE_OF_SCORE_WINDOW_X / 2 + 7, SCORE_WINDOW_POS_Y + SIZE_OF_SCORE_WINDOW_Y - 35, 0, buffer);
	}

}


/*showNextPiece()
 * Funcion encargada de mostrar la siguiente pieza 
 * Recibe: squareColors (arreglo de los colores de las piezas), squareBorderColors (arreglo de los colores de los bordes de las piezas)
 *			elem (puntero a la estructura con todos los punteros de allegro)	
 * Devuelve: --
 */
static void showNextPiece(ALLEGRO_COLOR squareColors[], ALLEGRO_COLOR squareBorderColors[], element_t *elem)
{

	//recuadro con el nombre
	al_draw_text(elem->buttonsBorder, al_map_rgb(66, 67, 62), NEXT_PIECE_WINDOW_POS_X + SIZE_OF_NEXT_PIECE_WINDOW_X / 2, NEXT_PIECE_WINDOW_POS_Y - 65, ALLEGRO_ALIGN_CENTER, "NEXT PIECE");
	al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), NEXT_PIECE_WINDOW_POS_X + SIZE_OF_NEXT_PIECE_WINDOW_X / 2, NEXT_PIECE_WINDOW_POS_Y - 65, ALLEGRO_ALIGN_CENTER, "NEXT PIECE");
	al_draw_filled_rectangle(NEXT_PIECE_WINDOW_POS_X, NEXT_PIECE_WINDOW_POS_Y, NEXT_PIECE_WINDOW_POS_X + SIZE_OF_NEXT_PIECE_WINDOW_X, NEXT_PIECE_WINDOW_POS_Y + SIZE_OF_NEXT_PIECE_WINDOW_Y, al_map_rgb(66, 67, 62));
	al_draw_rectangle(NEXT_PIECE_WINDOW_POS_X, NEXT_PIECE_WINDOW_POS_Y, NEXT_PIECE_WINDOW_POS_X + SIZE_OF_NEXT_PIECE_WINDOW_X, NEXT_PIECE_WINDOW_POS_Y + SIZE_OF_NEXT_PIECE_WINDOW_Y, al_map_rgb(124, 121, 108), 6);

	int nextPiece = getNextPiece();
	int i;

	//dibujo la siguiente pieza
	for (i = 0; i < 4; i++)
	{
		al_draw_filled_rectangle(posPieza[nextPiece - 1][i][0] + NEXT_PIECE_WINDOW_POS_X, posPieza[nextPiece - 1][i][1] + NEXT_PIECE_WINDOW_POS_Y, posPieza[nextPiece - 1][i][0] + NEXT_PIECE_WINDOW_POS_X + SQUARE_SIG_SIZE, posPieza[nextPiece - 1][i][1] + NEXT_PIECE_WINDOW_POS_Y + SQUARE_SIG_SIZE, squareColors[nextPiece]);

		al_draw_rectangle(posPieza[nextPiece - 1][i][0] + NEXT_PIECE_WINDOW_POS_X, posPieza[nextPiece - 1][i][1] + NEXT_PIECE_WINDOW_POS_Y, posPieza[nextPiece - 1][i][0] + NEXT_PIECE_WINDOW_POS_X + SQUARE_SIG_SIZE, posPieza[nextPiece - 1][i][1] + NEXT_PIECE_WINDOW_POS_Y + SQUARE_SIG_SIZE, squareBorderColors[nextPiece], 2);
	}

}

/*isTetrisAnimation()
 * Funcion encargada de animar un tetris
 * Recibe: arrayOfLinesWithTetris (arreglo que dice que filas del tablero hay tetris), squareColors (arreglo de los colores de las piezas),
 *			elem (puntero a la estructura con todos los punteros de allegro)	
 * Devuelve: --
 */
static void isTetrisAnimation(char arrayOfLinesWithTetris[HEIGHT_OF_BOARD], ALLEGRO_COLOR squareColors[], element_t *elem)
{
	int i;
	int times;
	for (times = 0; times < 4; times++) 
	{
		for (i = 0; arrayOfLinesWithTetris[i] != END_OF_ARRAY; i++) //si hay un tetris muestro una animacion
		{
			int j;
			for (j = 1; j < BOARD_WIDTH - 1; j++)
			{
				float x1 = BOARD_START_X + j * SQUARE_SIZE;
				float y1 = BOARD_START_Y + arrayOfLinesWithTetris[i] * SQUARE_SIZE;

				al_draw_filled_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, times % 2 ? al_map_rgb(220, 20, 60) : al_map_rgb(35, 235, 195)); // pinto la fila de un color
				al_draw_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, squareColors[EMPTY], 2);
			}
			al_draw_text(elem->fontInGameBorder, al_map_rgb(66, 67, 62), BOARD_START_X + BOARD_WIDTH * SQUARE_SIZE,
						 BOARD_START_Y + arrayOfLinesWithTetris[i] * SQUARE_SIZE - SQUARE_SIZE + SQUARE_SIZE / 4, 0, "+100");

			al_draw_text(elem->fontInGame, al_map_rgb(255, 255, 255), BOARD_START_X + BOARD_WIDTH * SQUARE_SIZE,
						 BOARD_START_Y + arrayOfLinesWithTetris[i] * SQUARE_SIZE - SQUARE_SIZE + SQUARE_SIZE / 4, 0, "+100");
		}
		al_flip_display();
		al_rest(0.100);
	}
	al_draw_bitmap(elem->gameBackround, 0, 0, 0);
}

/*drawActiveModes()
 * Funcion encargada de dibujar los modos activo
 * Recibe: elem (puntero a la estructura con todos los punteros de allegro), gameMode (estructura que maneja la dificultad del juego)
 * Devuelve: --
 */
static void drawActiveModes(element_t *elem, game_mode_t gameMode)
{
	bool gameModesActive[] = {gameMode.mirrored, gameMode.blinking, gameMode.notEmpty};
	ALLEGRO_BITMAP *pictures_logo[] = {elem->mirroredLogo, elem->blinkingLogo, elem->notEmptyLogo};

	al_draw_rectangle(ACTIVE_GAME_MODES_POS_X - 75, ACTIVE_GAME_MODES_POS_Y - 70, ACTIVE_GAME_MODES_POS_X + 75, ACTIVE_GAME_MODES_POS_Y + 3 * 120, al_map_rgb(124, 121, 108), 6);

	al_draw_text(elem->buttonsBorder, al_map_rgb(66, 67, 62), ACTIVE_GAME_MODES_POS_X, ACTIVE_GAME_MODES_POS_Y - 4 * SQUARE_SIZE, ALLEGRO_ALIGN_CENTER, "GAME MODE");
	al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), ACTIVE_GAME_MODES_POS_X, ACTIVE_GAME_MODES_POS_Y - 4 * SQUARE_SIZE, ALLEGRO_ALIGN_CENTER, "GAME MODE");

	int i;

	for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
	{
		al_set_target_bitmap(elem->borderLogo);

		al_clear_to_color(gameModesActive[i] ? al_map_rgba(200, 0, 60, 200) : al_map_rgba(66, 67, 62, 200));

		al_draw_rectangle(0, 0, 75, 75, gameModesActive[i] ? al_map_rgb(255, 255, 255) : al_map_rgb(124, 121, 108), gameModesActive[i] ? 5 : 4);

		al_set_target_backbuffer(elem->display);

		al_draw_rotated_bitmap(elem->borderLogo, al_get_bitmap_width(elem->borderLogo) / 2.0, al_get_bitmap_height(elem->borderLogo) / 2.0,
							   ACTIVE_GAME_MODES_POS_X, ACTIVE_GAME_MODES_POS_Y + i * 120, ALLEGRO_PI / 4, 0);

		al_draw_bitmap(pictures_logo[i], ACTIVE_GAME_MODES_POS_X - 50, ACTIVE_GAME_MODES_POS_Y - (i == 2 ? 50 : 42) + i * 120, 0);
	}

	//muestro en nivel de dificultad
	int numberOfStars = gameMode.difficulty;
	for (i = 0; i < 3; i++)
	{
		if (i < numberOfStars)
		{
			al_draw_text(elem->difficultyBorder, al_map_rgb(0, 0, 0), ACTIVE_GAME_MODES_POS_X - 40 + i * 40, ACTIVE_GAME_MODES_POS_Y + 2 * 120 + 60, ALLEGRO_ALIGN_CENTER, "a");
			al_draw_text(elem->difficulty, al_map_rgb(200, 175, 0), ACTIVE_GAME_MODES_POS_X - 40 + i * 40, ACTIVE_GAME_MODES_POS_Y + 2 * 120 + 60, ALLEGRO_ALIGN_CENTER, "a");
		}
		else
		{
			al_draw_text(elem->difficultyBorder, al_map_rgb(0, 0, 0), ACTIVE_GAME_MODES_POS_X - 40 + i * 40, ACTIVE_GAME_MODES_POS_Y + 2 * 120 + 60, ALLEGRO_ALIGN_CENTER, "a");
			al_draw_text(elem->difficulty, al_map_rgb(100, 100, 100), ACTIVE_GAME_MODES_POS_X - 40 + i * 40, ACTIVE_GAME_MODES_POS_Y + 2 * 120 + 60, ALLEGRO_ALIGN_CENTER, "a");
		}
	}

}

static void initBoardColors(ALLEGRO_COLOR squareColors[])
{
	squareColors[EMPTY] = al_map_rgb(66, 67, 62);
	squareColors[PIECE_I] = al_map_rgb(0, 255, 255);
	squareColors[PIECE_J] = al_map_rgb(0, 200, 245);
	squareColors[PIECE_O] = al_map_rgb(255, 255, 0);
	squareColors[PIECE_L] = al_map_rgb(250, 150, 50);
	squareColors[PIECE_S] = al_map_rgb(0, 255, 127);
	squareColors[PIECE_Z] = al_map_rgb(250, 50, 50);
	squareColors[PIECE_T] = al_map_rgb(200, 30, 200);
	squareColors[BORDER] = al_map_rgb(124, 121, 108);
}

static void initBoardBorderColors(ALLEGRO_COLOR squareColors[])
{
	squareColors[EMPTY] = al_map_rgb(124, 121, 108);
	squareColors[PIECE_I] = al_map_rgb(0, 150, 150);
	squareColors[PIECE_J] = al_map_rgb(0, 125, 150);
	squareColors[PIECE_O] = al_map_rgb(150, 150, 0);
	squareColors[PIECE_L] = al_map_rgb(200, 110, 0);
	squareColors[PIECE_S] = al_map_rgb(0, 155, 80);
	squareColors[PIECE_Z] = al_map_rgb(255, 0, 0);
	squareColors[PIECE_T] = al_map_rgb(128, 0, 128);
	squareColors[BORDER] = al_map_rgb(66, 67, 62);
}
/*playGame()
 * Funcion encargada de manejar todo el juego
 * Recibe: elem (puntero a la estructura con todos los punteros de allegro), mode (estructura que maneja la dificultad del juego)
 *			state (puntero a la estructura del estado del display), y highscore (puntero a la estructura que almacena los puntajes mas altos)
 * Devuelve: --
 */
void playGame(element_t *elem, game_mode_t mode, window_state_t *state, highscore_t *highscore)
{

	ALLEGRO_EVENT ev;
	al_stop_samples();
	while (!al_play_sample(elem->effectPlay, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
	while (!al_play_sample(elem->controlsMusic, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));

	//mostramos los controles
	al_draw_bitmap(elem->controls, 0, 0, 0);
	al_flip_display();

	al_start_timer(elem->timerControls);
	al_start_timer(elem->timerOff);

	al_get_next_event(elem->eventQueue, &ev);
	float carga = 0.0;
	char buffer[5];
	snprintf(buffer, sizeof(buffer), "%d%%",(int) (carga * 100));

	while ((ev.type != ALLEGRO_EVENT_TIMER || ev.timer.source == elem->timerOff) && ev.type != ALLEGRO_EVENT_KEY_DOWN)
	{
		if (ev.timer.source == elem->timerOff)
		{
			carga += 0.2;
			al_draw_bitmap(elem->controls, 0, 0, 0);
			snprintf(buffer, sizeof(buffer), "%d%%",(int) (carga * 100));
		}

		al_draw_filled_rectangle(SCREEN_W / 3.0, 6 * SCREEN_H / 7.0 - 20, SCREEN_W / 3.0 + carga  * (SCREEN_W / 3.0), 6 * SCREEN_H / 7.0 + 20, al_map_rgb(0, 75, 205));
		al_draw_rectangle(SCREEN_W / 3.0, 6 * SCREEN_H / 7.0 - 20, 2 * SCREEN_W / 3.0, 6 * SCREEN_H / 7.0 + 20, al_color_name("white"), 4);

		al_draw_text(elem->gameModesDescription, al_color_name("white"), SCREEN_W / 2, 6 * SCREEN_H / 7.0 - 7, ALLEGRO_ALIGN_CENTER, buffer);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			*state = CLOSE_DISPLAY;
			al_stop_timer(elem->timerControls);
			al_stop_timer(elem->timerOff);
			return;
		}

		al_flip_display();
		while (!al_get_next_event(elem->eventQueue, &ev));

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			//cargamos el fondo
			al_draw_bitmap(elem->controls, 0, 0, 0);

			//ponemos la barra en 100
			carga = 1.0;
			snprintf(buffer, sizeof(buffer), "%d%%", (int)(carga * 100));

			//dibujamos
			al_draw_filled_rectangle(SCREEN_W / 3.0, 6 * SCREEN_H / 7.0 - 20, SCREEN_W / 3.0 + carga * (SCREEN_W / 3.0), 6 * SCREEN_H / 7.0 + 20, al_map_rgb(0, 75, 205));
			al_draw_rectangle(SCREEN_W / 3.0, 6 * SCREEN_H / 7.0 - 20, 2 * SCREEN_W / 3.0, 6 * SCREEN_H / 7.0 + 20, al_color_name("white"), 4);
			al_draw_text(elem->gameModesDescription, al_color_name("white"), SCREEN_W / 2, 6 * SCREEN_H / 7.0 - 7, ALLEGRO_ALIGN_CENTER, buffer);

			//mostramos
			al_flip_display();
			al_rest(0.5);
		}
	}

	al_stop_timer(elem->timerOff);
	al_stop_timer(elem->timerControls);
		
	al_draw_bitmap(elem->gameBackround, 0, 0, 0);

	al_stop_samples();

	while(!al_play_sample(elem->effectPlay, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
	al_set_sample_instance_gain(elem->sampleGameReg, 1);
	al_set_sample_instance_speed(elem->sampleGameReg, 1.0);
	al_play_sample_instance(elem->sampleGameReg);

	// creamos e inicializamos un arreglo con los colores de las distintas piezas
	ALLEGRO_COLOR squareColors[9];
	ALLEGRO_COLOR squareBorderColors[9];
	initBoardColors(squareColors);
	initBoardBorderColors(squareBorderColors);

	srand(time(NULL));

	char matrix[BOARD_LENGHT][BOARD_WIDTH];
	char auxiliaryMatrix[BOARD_LENGHT][BOARD_WIDTH];
	char predictionMatrix[BOARD_LENGHT][BOARD_WIDTH];
	char blinkingMatrix[BOARD_LENGHT][BOARD_WIDTH];

	char arrayOfLinesWithTetris[BOARD_LENGHT];

	for (int i = 0; i < BOARD_LENGHT; i++) // llena de 0 la matriz el interior y define los bordes
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (i == 0 || i == 17 || j == 0 || j == 11)
			{
				matrix[i][j] = BORDER;
				blinkingMatrix[i][j] = BORDER;
			}
			else
			{
				matrix[i][j] = EMPTY;
				blinkingMatrix[i][j] = EMPTY;
			}
		}
	}

	if (mode.notEmpty) //llena con piezas el tablero si es necesario
	{
		createBoardforNotEmpty(matrix);
	}
	int score = 0;
	int times = 0;

	//inicializo el tiempo y creo la primera pieza
	initTime();
	initPiece();
	piece_t piece = createPiece();
	piece_t predictionPiece = piece;

	if (mode.blinking) //empiezo un timer si es necesario
	{
		al_start_timer(elem->timerOn);
	}
	bool playing = true;
	bool draw = true;
	bool tetris = false;
	bool off = false;

	while (playing)
	{
		if (!al_get_sample_instance_playing(elem->sampleGameReg))
		{
			al_play_sample_instance(elem->sampleGameReg);
		}

		if (al_get_next_event(elem->eventQueue, &ev)) // pedimos el evento que venga
		{

			if (ev.type == ALLEGRO_EVENT_KEY_DOWN) //si se preciono una tecla llamo a la funcion jugar con dicha tecla
			{
				switch (ev.keyboard.keycode)
				{
				case TURN_AL_2:
				case TURN_AL:
					playing = !playTetris('w', &piece, matrix, &score, mode);
					al_play_sample(elem->effectRotate, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				case DOWN_AL_2:
				case DOWN_AL:
					playing = !playTetris('s', &piece, matrix, &score, mode);
					al_play_sample(elem->effectMove, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				case RIGHT_AL_2:
				case RIGHT_AL:
					playing = !playTetris('d', &piece, matrix, &score, mode);
					al_play_sample(elem->effectMove, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				case LEFT_AL_2:
				case LEFT_AL:
					playing = !playTetris('a', &piece, matrix, &score, mode);
					al_play_sample(elem->effectMove, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				case DROP:
					playing = !playTetris(' ', &piece, matrix, &score, mode);
					al_play_sample(elem->effectLanding, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				case PAUSE:
					drawPauseMenu(state, elem, &playing);
					al_draw_bitmap(elem->gameBackround, 0, 0, 0);
					break;
				}

				draw = true;
			}

			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				*state = CLOSE_DISPLAY;
				playing = false;
			}

			if (mode.blinking && ev.type == ALLEGRO_EVENT_TIMER) //verifico cuando es blinking
			{
				if (ev.timer.source == elem->timerOff)
				{
					off = false;
					al_stop_timer(elem->timerOff);
					al_start_timer(elem->timerOn);
				}
				else if (ev.timer.source == elem->timerOn)
				{
					off = true;
					al_stop_timer(elem->timerOn);
					al_start_timer(elem->timerOff);
					drawBoard(blinkingMatrix, blinkingMatrix, squareColors, squareBorderColors);
				}
			}
		}

		if (playing && *state == GAME) //si sigue jugando vemos si tiene que bajar la pieza
		{
			playing = !playTetris('\0', &piece, matrix, &score, mode); // actualizamos
		}

		times++;

		if (times % 1000 || tetris) //dibujo cada tantas veces o si hay tetris
		{
			times = 0;
			draw = true;
		}

		if (draw && playing)
		{
			int i, j;
			// copia la matris de juego en una auxiliar para mostrar
			for (i = 0; i < BOARD_LENGHT; i++)
			{
				for (j = 0; j < BOARD_WIDTH; j++)
				{
					auxiliaryMatrix[i][j] = matrix[i][j];
					predictionMatrix[i][j] = matrix[i][j];
				}
			}

			// veamos donde caeria la pieza
			predictionPiece = piece;
			bool flagGoDown = movePieceDown(&predictionPiece, predictionMatrix);
			while (flagGoDown)
			{
				flagGoDown = movePieceDown(&predictionPiece, predictionMatrix);
			}
			parkPiece(&predictionPiece, predictionMatrix);

			parkPiece(&piece, auxiliaryMatrix); // estacionamos la pieza que se esta moviendo para visualizarla

			if (!off)
			{
				drawBoard(auxiliaryMatrix, predictionMatrix, squareColors, squareBorderColors);
			}
			//verifico si hay tetris
			score += deleteLine(matrix, arrayOfLinesWithTetris, &tetris);



			if (tetris)
			{
				while(!al_play_sample(elem->effectTetris, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
				isTetrisAnimation(arrayOfLinesWithTetris, squareColors, elem);
				if (!off)
				{
					drawBoard(auxiliaryMatrix, predictionMatrix, squareColors, squareBorderColors);
				}

				//modificamos la velocidad de la música en función del puntaje
				al_set_sample_instance_speed(elem->sampleGameReg, 1.0 + score / 7500.0);

				tetris = false;
			}
			//muestro el resto de informacion
			showScore(elem, score, highscore);
			showNextPiece(squareColors, squareBorderColors, elem);
			drawActiveModes(elem, mode);

			al_flip_display();
			draw = false;
		}
	}

	al_stop_sample_instance(elem->sampleGameReg);

	if (mode.blinking)
	{
		al_stop_timer(elem->timerOn);
		al_stop_timer(elem->timerOff);
		drawBoard(auxiliaryMatrix, predictionMatrix, squareColors, squareBorderColors);
	}

	if (*state != CLOSE_DISPLAY)
	{
		gameOver(state, elem, score, highscore);
	}
}

/*gameOver()
 * Funcion encargada de mostar el menu de fin de juego
 * Recibe: elem (puntero a la estructura con todos los punteros de allegro), state (puntero a la estructura del estado del display),
			score (el puntaje que alcanzo el jugador), y highscore (puntero a la estructura que almacena los puntajes mas altos)
 * Devuelve: --
 */
static void gameOver(window_state_t *state, element_t *elem, int score, highscore_t *highScore)
{
	ALLEGRO_EVENT ev;
	//dibujo el menu de game over
	al_clear_to_color(al_map_rgb(20, 20, 20));
	al_draw_bitmap(elem->gameBackround, 0, 0, 0);
	al_flip_display();

	al_stop_samples();
	while(!al_play_sample(elem->effectGameOver, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));

	int numberOfBlinkings;
	for (numberOfBlinkings = 0; numberOfBlinkings < 4; numberOfBlinkings++)
	{
		al_draw_text(elem->titleBorder, al_color_name("black"), SCREEN_W / 2, SCREEN_H / 6, 1, "GAME OVER");
		al_draw_text(elem->title, numberOfBlinkings % 2 ? al_color_name("white") : al_color_name("red"), SCREEN_W / 2, SCREEN_H / 6, 1, "GAME OVER");
		al_rest(0.300);
		al_flip_display();
	}

	// al_play_sample(elem->effectGameOver, 1.0, 1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	while(!al_play_sample(elem->sampleGameOver, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL));

	// botones
	button_t play = {"PLAY AGAIN", SCREEN_W / 2, SCREEN_H * 0.65, 130, 40, 20,
					 false, al_map_rgb(100, 110, 200), al_map_rgb(100, 0, 200),
					 elem->buttons};

	button_t highscore = {"HIGHSCORE", SCREEN_W / 2, SCREEN_H * 0.80, 130, 40, 20,
						  false, al_map_rgb(100, 110, 200), al_map_rgb(100, 0, 200),
						  elem->buttons};

	button_t *buttons[] = {&play, &highscore, NULL};
	//muestro en puntaje
	char buffer[15];
	snprintf(buffer, sizeof(buffer), "%s%d", "SCORE: ", score);

	int position = checkIfHighscore(score, highScore);
	char buffer2[4];
	snprintf(buffer2, sizeof(buffer2), "%d", position);
	//si hay un nuevo highscore
	if (position <= NUMBER_OF_PLAYERS)
	{
		while(!al_play_sample(elem->effectHighscore, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
		char name[4] = "   ";
		int c = 0;
		bool waiting = true;
		while (waiting)
		{
			al_clear_to_color(al_map_rgb(20, 20, 20));
			al_draw_bitmap(elem->gameBackround, 0, 0, 0);

			al_draw_text(elem->titleBorder, al_color_name("black"), SCREEN_W / 2, SCREEN_H / 6, 1, "GAME OVER");
			al_draw_text(elem->title, al_color_name("white"), SCREEN_W / 2, SCREEN_H / 6, 1, "GAME OVER");
			drawButtons(buttons, al_color_name("white"));

			al_draw_text(elem->buttonsBorder, al_color_name("black"), SCREEN_W / 2, SCREEN_H / 6 + SIZE_OF_TITLE, ALLEGRO_ALIGN_CENTER, buffer);
			al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 6 + SIZE_OF_TITLE, ALLEGRO_ALIGN_CENTER, buffer);

			al_draw_text(elem->highscoreNews, al_color_name("yellow"), SCREEN_W / 2 - 10, SCREEN_H / 6 + SIZE_OF_TITLE + 45, ALLEGRO_ALIGN_CENTRE, "New #");
			al_draw_text(elem->highscoreNews, al_color_name("yellow"), SCREEN_W / 2 + 50, SCREEN_H / 6 + SIZE_OF_TITLE + 45, ALLEGRO_ALIGN_CENTRE, buffer2);

			al_set_target_bitmap(elem->bitmap);

			// Dibujar un rectángulo con transparencia
			al_clear_to_color(al_map_rgba(66, 67, 62, 230));

			al_set_target_backbuffer(elem->display);

			// Dibujar el bitmap en el display
			al_draw_bitmap(elem->bitmap, SCREEN_W / 4, SCREEN_H / 4, 0);
			al_draw_rectangle(SCREEN_W / 4, SCREEN_H / 4, SCREEN_W / 4 + SCREEN_W / 2, SCREEN_H / 4 + SCREEN_H / 2, al_map_rgb(255, 255, 255), 4);
			al_draw_text(elem->pauseMenu, al_map_rgb(190, 171, 30), SCREEN_W / 2, SCREEN_H * 0.30, ALLEGRO_ALIGN_CENTRE, "HIGHSCORE");

			al_draw_text(elem->buttons, al_map_rgb(190, 171, 30), SCREEN_W / 2, SCREEN_H * 0.30 + 70, ALLEGRO_ALIGN_CENTRE, "Please enter your name: ");

			al_get_next_event(elem->eventQueue, &ev);

			// analizamos si se cerró la ventana
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				waiting = false;
				*state = CLOSE_DISPLAY;
			}

			if (ev.type == ALLEGRO_EVENT_KEY_DOWN) //guardo las teclas que se precionan
			{
				char key = ev.keyboard.keycode;

				if (c < CHARACTERS)
				{
					if (key >= ALLEGRO_KEY_A && key <= ALLEGRO_KEY_Z)
					{
						name[c++] = key - ALLEGRO_KEY_A + 'A';
					}
					else if (key >= ALLEGRO_KEY_0 && key <= ALLEGRO_KEY_9)
					{
						name[c++] = key - ALLEGRO_KEY_0 + '0';
					}
					else if (c > 0 && (key == ALLEGRO_KEY_DELETE || key == ALLEGRO_KEY_BACKSPACE))
					{
						name[--c] = ' ';
					}
				}

				else if (key == ALLEGRO_KEY_DELETE || key == ALLEGRO_KEY_BACKSPACE)
				{
					name[--c] = ' ';
				}
				else if (key == ALLEGRO_KEY_ENTER)
				{
					waiting = false;
				}
			}

			al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H * 0.30 + 170, ALLEGRO_ALIGN_CENTRE, name);

			al_flip_display();
		}
		//guardo los nuevos highscore
		setHighscore(highScore, score, name);
	}
	//dibujo el resto del menu
	al_clear_to_color(al_map_rgb(20, 20, 20));

	al_draw_bitmap(elem->gameBackround, 0, 0, 0);

	drawButtons(buttons, al_color_name("white"));

	al_draw_text(elem->titleBorder, al_color_name("black"), SCREEN_W / 2, SCREEN_H / 6, 1, "GAME OVER");
	al_draw_text(elem->title, al_color_name("white"), SCREEN_W / 2, SCREEN_H / 6, 1, "GAME OVER");

	al_draw_text(elem->buttonsBorder, al_color_name("black"), SCREEN_W / 2, SCREEN_H / 6 + SIZE_OF_TITLE, ALLEGRO_ALIGN_CENTER, buffer);
	al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 6 + SIZE_OF_TITLE, ALLEGRO_ALIGN_CENTER, buffer);

	if (position <= NUMBER_OF_PLAYERS)
	{
		al_draw_text(elem->highscoreNews, al_color_name("yellow"), SCREEN_W / 2 - 10, SCREEN_H / 6 + SIZE_OF_TITLE + 45, ALLEGRO_ALIGN_CENTRE, "New #");
		al_draw_text(elem->highscoreNews, al_color_name("yellow"), SCREEN_W / 2 + 50, SCREEN_H / 6 + SIZE_OF_TITLE + 45, ALLEGRO_ALIGN_CENTRE, buffer2);
		while (!al_play_sample(elem->effectHighscore, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
	}
	
	al_flip_display();

	// esperamos a alguna selección
	bool waitingForUpdate = true;
	bool draw = false;
	int times = 0;

	while (waitingForUpdate && *state != CLOSE_DISPLAY)
	{
		al_get_next_event(elem->eventQueue, &ev); // pedimos el evento que venga

		// analizamos si se cerró la ventana
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			*state = CLOSE_DISPLAY;
			waitingForUpdate = false;
		}

		// vemos si se posicionó el mouse sobre un botón
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			int i;
			for (i = 0; buttons[i]; i++)
			{
				if (!buttons[i]->press && (ev.mouse.x <= buttons[i]->x_center + buttons[i]->width && ev.mouse.x >= buttons[i]->x_center - buttons[i]->width && ev.mouse.y <= buttons[i]->y_center + buttons[i]->height && ev.mouse.y >= buttons[i]->y_center - buttons[i]->height))
				{
					if (!buttons[i]->press) // si el botón cambia de estado, dibujamos
					{
						draw = true;
					}
					buttons[i]->press = true; // actualizamos el estado del botón
					while(!al_play_sample(elem->effectCursor, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
				}

				else if (buttons[i]->press && (ev.mouse.x > buttons[i]->x_center + buttons[i]->width || ev.mouse.x < buttons[i]->x_center - buttons[i]->width || ev.mouse.y > buttons[i]->y_center + buttons[i]->height || ev.mouse.y < buttons[i]->y_center - buttons[i]->height))
				{
					if (buttons[i]->press) // si el botón cambia de estado, dibujamos
					{
						draw = true;
					}
					buttons[i]->press = false; // actualizamos el estado del botón
				}
			}
		}

		// analizamos si se pulso algún botón
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.x <= buttons[PLAY]->x_center + buttons[PLAY]->width && ev.mouse.x >= buttons[PLAY]->x_center - buttons[PLAY]->width && ev.mouse.y <= buttons[PLAY]->y_center + buttons[PLAY]->height && ev.mouse.y >= buttons[PLAY]->y_center - buttons[PLAY]->height)
			{
				*state = GAME_SEL;
				while(!al_play_sample(elem->effectPlay, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
				al_rest(0.4);
				al_stop_samples();
				while(!al_play_sample(elem->sampleMenu, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL));
				waitingForUpdate = false;
			}

			else if (ev.mouse.x <= buttons[SCORE]->x_center + buttons[SCORE]->width && ev.mouse.x >= buttons[SCORE]->x_center - buttons[SCORE]->width && ev.mouse.y <= buttons[SCORE]->y_center + buttons[SCORE]->height && ev.mouse.y >= buttons[SCORE]->y_center - buttons[SCORE]->height)
			{
				*state = HIGHSCORE;
				while(!al_play_sample(elem->effectPlay, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
				al_rest(0.6);
				waitingForUpdate = false;
			}
		}

		if (++times % 1000)
		{
			draw = true;
			times = 0;
		}

		// redibujamos si es necesario
		if (draw)
		{
			drawButtons(buttons, al_color_name("white"));
			al_flip_display(); // cargamos el buffer en el display
			draw = false;	   // cambiamos el estado de draw
		}
	}
}

/*gameOver()
 * Funcion encargada de dibujar el menu de pausa
 * Recibe:  state (puntero a la estructura del estado del display), elem (puntero a la estructura con todos los punteros de allegro),
			playing (puntero al booleano del juego)
 * Devuelve: --
 */
static void drawPauseMenu(window_state_t *state, element_t *elem, bool *playing)
{
	while(!al_play_sample(elem->effectPause, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
	al_set_sample_instance_gain(elem->sampleGameReg, 0.2);

	ALLEGRO_EVENT ev;
	bool waitingForUpdate = true;
	bool draw = true;

	al_set_target_bitmap(elem->bitmap);

	// Dibujar un rectángulo rojo con transparencia
	al_clear_to_color(al_map_rgba(66, 67, 62, 140));

	al_set_target_backbuffer(elem->display);

	// Dibujar el bitmap en el display
	al_draw_bitmap(elem->bitmap, SCREEN_W / 4, SCREEN_H / 4, 0);
	al_draw_rectangle(SCREEN_W / 4, SCREEN_H / 4, SCREEN_W / 4 + SCREEN_W / 2, SCREEN_H / 4 + SCREEN_H / 2, al_map_rgb(255, 255, 255), 4);
	al_draw_text(elem->pauseMenu, al_map_rgb(195, 44, 23), SCREEN_W / 2, SCREEN_H * 0.30, ALLEGRO_ALIGN_CENTRE, "PAUSE");

	// botones
	button_t resume = {"RESUME", SCREEN_W / 2, SCREEN_H * 0.50, 130, 40, 20,
					   false, al_map_rgb(100, 110, 200), al_map_rgb(100, 0, 200),
					   elem->buttons};

	button_t quit = {"QUIT", SCREEN_W / 2, SCREEN_H * 0.65, 130, 40, 20,
					 false, al_map_rgb(231, 87, 65), al_map_rgb(195, 44, 23),
					 elem->buttons};

	button_t *buttons[] = {&resume, &quit, NULL};
	al_flip_display();

	int times = 0;
	while (waitingForUpdate) //se queda mientras continue la pausa
	{
		if (!al_get_sample_instance_playing(elem->sampleGameReg))
		{
			while(!al_play_sample_instance(elem->sampleGameReg));
			al_set_sample_instance_gain(elem->sampleGameReg, 0.2);
		}

		al_get_next_event(elem->eventQueue, &ev); // pedimos el evento que venga

		// analizamos si se cerró la ventana
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			*state = CLOSE_DISPLAY;
			waitingForUpdate = false;
			*playing = false;
		}

		// vemos si se posicionó el mouse sobre un botón
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			int i;
			for (i = 0; buttons[i]; i++)
			{
				if (!buttons[i]->press && (ev.mouse.x <= buttons[i]->x_center + buttons[i]->width && ev.mouse.x >= buttons[i]->x_center - buttons[i]->width && ev.mouse.y <= buttons[i]->y_center + buttons[i]->height && ev.mouse.y >= buttons[i]->y_center - buttons[i]->height))
				{
					if (!buttons[i]->press) // si el botón cambia de estado, dibujamos
					{
						draw = true;
					}
					buttons[i]->press = true; // actualizamos el estado del botón
					while(!al_play_sample(elem->effectCursor, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
				}

				else if (buttons[i]->press && (ev.mouse.x > buttons[i]->x_center + buttons[i]->width || ev.mouse.x < buttons[i]->x_center - buttons[i]->width || ev.mouse.y > buttons[i]->y_center + buttons[i]->height || ev.mouse.y < buttons[i]->y_center - buttons[i]->height))
				{
					if (buttons[i]->press) // si el botón cambia de estado, dibujamos
					{
						draw = true;
					}
					buttons[i]->press = false; // actualizamos el estado del botón
				}
			}
		}

		// analizamos si se pulso algún botón
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.x <= buttons[RESUME]->x_center + buttons[RESUME]->width && ev.mouse.x >= buttons[RESUME]->x_center - buttons[RESUME]->width && ev.mouse.y <= buttons[RESUME]->y_center + buttons[RESUME]->height && ev.mouse.y >= buttons[RESUME]->y_center - buttons[RESUME]->height)
			{
				while(!al_play_sample(elem->effectPause, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
				al_rest(0.4);
				al_set_sample_instance_gain(elem->sampleGameReg, 1.0);
				waitingForUpdate = false;
			}

			else if (ev.mouse.x <= buttons[QUIT]->x_center + buttons[QUIT]->width && ev.mouse.x >= buttons[QUIT]->x_center - buttons[QUIT]->width && ev.mouse.y <= buttons[QUIT]->y_center + buttons[QUIT]->height && ev.mouse.y >= buttons[QUIT]->y_center - buttons[QUIT]->height)
			{
				while(!al_play_sample(elem->effectPlay, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
				al_rest(0.4);
				waitingForUpdate = false;
				*playing = false;
			}
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == PAUSE)
		{
			while(!al_play_sample(elem->effectPause, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
			al_rest(0.4);
			al_set_sample_instance_gain(elem->sampleGameReg, 1.0);
			waitingForUpdate = false;
		}

		if (++times % 1000)
		{
			draw = true;
			times = 0;
		}

		// redibujamos si es necesario
		if (draw)
		{
			drawButtons(buttons, al_color_name("white"));
			al_flip_display(); // cargamos el buffer en el display
			draw = false;	   // cambiamos el estado de draw
		}
	}
}