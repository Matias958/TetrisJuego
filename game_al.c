#include <stdlib.h>
#include "game_al.h"
#include "botones.h"
#include "juego.h"


#define BOARD_WIDTH 12
#define BOARD_LENGHT 18

#define BOARD_START_X 300
#define BOARD_START_Y 100

#define SQUARE_SIZE 35
#define SQUARE_SIG_SIZE 35

#define TAMANO_DE_VENTANA_PUNTAJE_X  6 * SQUARE_SIG_SIZE
#define TAMANO_DE_VENTANA_PUNTAJE_Y 100
#define PUNTAJE_VENTANA_X (BOARD_START_X + BOARD_WIDTH * SQUARE_SIZE + 50)
#define PUNTAJE_VENTANA_Y BOARD_START_Y

#define SIZE_OF_NEXT_PIECE_WINDOW_X (TAMANO_DE_VENTANA_PUNTAJE_X)
#define SIZE_OF_NEXT_PIECE_WINDOW_Y 200
#define NEXT_PIECE_WINDOW_POS_X PUNTAJE_VENTANA_X
#define NEXT_PIECE_WINDOW_POS_Y (PUNTAJE_VENTANA_Y + TAMANO_DE_VENTANA_PUNTAJE_Y + 100) 

#define SIZE_OF_GAME_MODE_WINDOW_X 100
#define WINDOW_POS_MODE_X (BOARD_START_X - SIZE_OF_GAME_MODE_WINDOW_X)
#define WINDOW_POS_MODE_Y BOARD_START_Y


#define GIRAR_AL ALLEGRO_KEY_W
#define GIRAR_AL_2  ALLEGRO_KEY_UP	
#define DERECHA_AL ALLEGRO_KEY_D
#define DERECHA_AL_2 ALLEGRO_KEY_RIGHT
#define IZQUIERDA_AL ALLEGRO_KEY_A
#define IZQUIERDA_AL_2 ALLEGRO_KEY_LEFT
#define BAJAR_AL ALLEGRO_KEY_S
#define BAJAR_AL_2 ALLEGRO_KEY_DOWN
#define PAUSE ALLEGRO_KEY_ESCAPE
#define BAJAR_TODO ALLEGRO_KEY_SPACE

#define SIZE_OF_TITLE 200

enum bordes { NADA_B = BORDE + 1, PIEZA_I_B, PIEZA_J_B, PIEZA_L_B, PIEZA_O_B, PIEZA_S_B, PIEZA_T_B, PIEZA_Z_B, BORDE_B };
enum game_over_options { JUGAR, PUNTAJE };
enum pause_options { RESUME, QUIT };

static const int posPieza[7][4][2] = { { { SQUARE_SIG_SIZE, SQUARE_SIG_SIZE * 2.5},{SQUARE_SIG_SIZE * 2 ,SQUARE_SIG_SIZE * 2.5}, {3 * SQUARE_SIG_SIZE,SQUARE_SIG_SIZE * 2.5},{4 * SQUARE_SIG_SIZE,SQUARE_SIG_SIZE * 2.5} },  // I   0
									   { {SQUARE_SIG_SIZE * 1.5, 2 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 2.5, 2 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 3.5, 2 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 3.5 , 3 * SQUARE_SIG_SIZE} }, // J    0
									   { {SQUARE_SIG_SIZE * 1.5 , 3 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 1.5, 2 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 2.5, 2 * SQUARE_SIG_SIZE}, {SQUARE_SIG_SIZE * 3.5, 2 * SQUARE_SIG_SIZE} }, //L  0
									   { {SQUARE_SIG_SIZE * 2 , 2 * SQUARE_SIG_SIZE},{SQUARE_SIG_SIZE *2, 3 * SQUARE_SIG_SIZE}, {3 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE},{3 * SQUARE_SIG_SIZE, 3 * SQUARE_SIG_SIZE} }, //O    0
									   { {SQUARE_SIG_SIZE *1.5, 3 * SQUARE_SIG_SIZE},{2.5 * SQUARE_SIG_SIZE, 3 * SQUARE_SIG_SIZE}, {2.5 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE},{3.5 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE} }, //S
									   { {SQUARE_SIG_SIZE * 1.5, 2 * SQUARE_SIG_SIZE},{2.5 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE}, {3.5 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE},{2.5 * SQUARE_SIG_SIZE, 3 * SQUARE_SIG_SIZE} }, //T   0
									   { {3.5 * SQUARE_SIG_SIZE, 3 * SQUARE_SIG_SIZE},{2.5 * SQUARE_SIG_SIZE, 3 * SQUARE_SIG_SIZE}, {2.5 * SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE},{1.5* SQUARE_SIG_SIZE, 2 * SQUARE_SIG_SIZE} }, //Z   0
};


static void draw_board(char board[BOARD_LENGHT][BOARD_WIDTH], char prediction_board[BOARD_LENGHT][BOARD_WIDTH], ALLEGRO_COLOR square_colors[], ALLEGRO_COLOR square_border_colors[]);
static void init_board_colors(ALLEGRO_COLOR square_colors[]);
static void init_board_border_colors(ALLEGRO_COLOR square_colors[]);
static void draw_active_modes(element_t *elem);
static void show_next_piece(ALLEGRO_COLOR square_colors[], ALLEGRO_COLOR square_border_colors[], element_t* elem);
static void mostrar_puntaje(element_t* elem, int puntaje);
static void es_tetris_animación(char filas_tetris[BOARD_LENGHT], ALLEGRO_COLOR square_colors[], element_t* elem);
static void game_over(window_state_t* state, element_t* elem, int puntaje, highscore_t *highscore);
static void draw_pause_menu(window_state_t* state, element_t* elem, bool* playing);

/* DRAW_BOARD()
 *
 *
 *
 *
 */

static void draw_board(char board[BOARD_LENGHT][BOARD_WIDTH], char prediction_board[BOARD_LENGHT][BOARD_WIDTH], ALLEGRO_COLOR square_colors[], ALLEGRO_COLOR square_border_colors[])
{
	int i;
	int j;
	for (i = 0; i < BOARD_LENGHT; i++)
	{
		for (j = 0; j < BOARD_WIDTH; j++)
		{
			float x1 = BOARD_START_X + j * SQUARE_SIZE;
			float y1 = BOARD_START_Y + i * SQUARE_SIZE;

			al_draw_filled_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, square_colors[board[i][j]]);

			al_draw_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, square_border_colors[board[i][j]], 2);
		}
	}

	//dibujamos la predicción de la caida de la pieza
	for (i = 0; i < BOARD_LENGHT; i++)
	{
		for (j = 0; j < BOARD_WIDTH; j++)
		{
			float x1 = BOARD_START_X + j * SQUARE_SIZE;
			float y1 = BOARD_START_Y + i * SQUARE_SIZE;

			if (prediction_board[i][j] != NADA && prediction_board[i][j] != board[i][j])
			{
				al_draw_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, square_border_colors[prediction_board[i][j]], 3);
			}
		}
	}

	al_flip_display();
}
static void mostrar_puntaje(element_t* elem, int puntaje)
{

	al_draw_text(elem->buttons_border, al_map_rgb(66, 67, 62), PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE_X / 2, PUNTAJE_VENTANA_Y - 3 * TAMANO_DE_VENTANA_PUNTAJE_Y / 5, ALLEGRO_ALIGN_CENTER, "SCORE");
	al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE_X / 2, PUNTAJE_VENTANA_Y - 3 * TAMANO_DE_VENTANA_PUNTAJE_Y / 5, ALLEGRO_ALIGN_CENTER, "SCORE");
	al_draw_filled_rectangle(PUNTAJE_VENTANA_X, PUNTAJE_VENTANA_Y, PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE_X, PUNTAJE_VENTANA_Y + TAMANO_DE_VENTANA_PUNTAJE_Y, al_map_rgb(66, 67, 62));
	al_draw_rectangle(PUNTAJE_VENTANA_X, PUNTAJE_VENTANA_Y, PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE_X, PUNTAJE_VENTANA_Y + TAMANO_DE_VENTANA_PUNTAJE_Y, al_map_rgb(124, 121, 108), 6);
	char buffer[6];
	_itoa_s(puntaje, buffer, 6, 10);
	al_draw_text(elem->buttons_border, al_map_rgb(0, 0, 0), PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE_X / 2, PUNTAJE_VENTANA_Y + TAMANO_DE_VENTANA_PUNTAJE_Y / 5, 1, buffer);
	al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE_X / 2, PUNTAJE_VENTANA_Y + TAMANO_DE_VENTANA_PUNTAJE_Y / 5, 1, buffer);
	al_flip_display();
}

static void show_next_piece(ALLEGRO_COLOR square_colors[], ALLEGRO_COLOR square_border_colors[], element_t *elem)
{
	al_draw_text(elem->buttons_border, al_map_rgb(66, 67, 62), NEXT_PIECE_WINDOW_POS_X + SIZE_OF_NEXT_PIECE_WINDOW_X / 2, NEXT_PIECE_WINDOW_POS_Y- 65, ALLEGRO_ALIGN_CENTER, "NEXT PIECE");
	al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), NEXT_PIECE_WINDOW_POS_X + SIZE_OF_NEXT_PIECE_WINDOW_X / 2, NEXT_PIECE_WINDOW_POS_Y - 65, ALLEGRO_ALIGN_CENTER, "NEXT PIECE");
	al_draw_filled_rectangle(NEXT_PIECE_WINDOW_POS_X, NEXT_PIECE_WINDOW_POS_Y, NEXT_PIECE_WINDOW_POS_X + SIZE_OF_NEXT_PIECE_WINDOW_X, NEXT_PIECE_WINDOW_POS_Y + SIZE_OF_NEXT_PIECE_WINDOW_Y, al_map_rgb(66, 67, 62));
	al_draw_rectangle(NEXT_PIECE_WINDOW_POS_X, NEXT_PIECE_WINDOW_POS_Y, NEXT_PIECE_WINDOW_POS_X + SIZE_OF_NEXT_PIECE_WINDOW_X, NEXT_PIECE_WINDOW_POS_Y + SIZE_OF_NEXT_PIECE_WINDOW_Y, al_map_rgb(124, 121, 108), 6);

	int sig_pieza = getSigPieza();
	int i;

	for (i = 0; i < 4; i++)
	{
		al_draw_filled_rectangle(posPieza[sig_pieza-1][i][0] + NEXT_PIECE_WINDOW_POS_X, posPieza[sig_pieza - 1][i][1] + NEXT_PIECE_WINDOW_POS_Y, posPieza[sig_pieza - 1][i][0] + NEXT_PIECE_WINDOW_POS_X + SQUARE_SIG_SIZE , posPieza[sig_pieza - 1][i][1] + NEXT_PIECE_WINDOW_POS_Y + SQUARE_SIG_SIZE, square_colors[sig_pieza]);

		al_draw_rectangle(posPieza[sig_pieza - 1][i][0] + NEXT_PIECE_WINDOW_POS_X, posPieza[sig_pieza - 1][i][1] + NEXT_PIECE_WINDOW_POS_Y, posPieza[sig_pieza - 1][i][0] + NEXT_PIECE_WINDOW_POS_X + SQUARE_SIG_SIZE, posPieza[sig_pieza - 1][i][1] + NEXT_PIECE_WINDOW_POS_Y + SQUARE_SIG_SIZE, square_border_colors[sig_pieza], 2);
	}
	
	al_flip_display();
}

static void es_tetris_animación(char filas_tetris[BOARD_LENGHT], ALLEGRO_COLOR square_colors[], element_t* elem)
{
	int i;
	int times;
	for (times = 0; times < 4; times++)
	{
		for (i = 0; filas_tetris[i] != FINAL_DEL_ARREGLO; i++)
		{
			int j;
			for (j = 1; j < BOARD_WIDTH - 1; j++)
			{
				float x1 = BOARD_START_X + j * SQUARE_SIZE;
				float y1 = BOARD_START_Y + filas_tetris[i] * SQUARE_SIZE;

				al_draw_filled_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, times % 2 ? al_map_rgb(220, 20, 60) : al_map_rgb(35, 235, 195));
				al_draw_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, square_colors[NADA], 2);
			}
			al_draw_text(elem->font_in_game_border, al_map_rgb(66, 67, 62), BOARD_START_X + BOARD_WIDTH * SQUARE_SIZE,
				BOARD_START_Y + filas_tetris[i] * SQUARE_SIZE - SQUARE_SIZE + SQUARE_SIZE / 4, 0, "+100");

			al_draw_text(elem->font_in_game, al_map_rgb(255, 255, 255), BOARD_START_X + BOARD_WIDTH * SQUARE_SIZE,
				BOARD_START_Y + filas_tetris[i] * SQUARE_SIZE - SQUARE_SIZE + SQUARE_SIZE / 4, 0, "+100");
		}
		al_flip_display();
		al_rest(0.100);
	}
	al_draw_bitmap(elem->game_backround, 0, 0, 0);
}

static void draw_active_modes(element_t *elem) // falta terminar
{
	//al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), WINDOW_POS_MODE_X,  - 3 * TAMANO_DE_VENTANA_PUNTAJE_Y / 5, 1, "SCORE");
	al_draw_filled_rectangle(PUNTAJE_VENTANA_X, PUNTAJE_VENTANA_Y, PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE_X, PUNTAJE_VENTANA_Y + TAMANO_DE_VENTANA_PUNTAJE_Y, al_map_rgb(66, 67, 62));
	al_draw_rectangle(PUNTAJE_VENTANA_X, PUNTAJE_VENTANA_Y, PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE_X, PUNTAJE_VENTANA_Y + TAMANO_DE_VENTANA_PUNTAJE_Y, al_map_rgb(124, 121, 108), 6);
}

static void init_board_colors(ALLEGRO_COLOR square_colors[])
{
	square_colors[NADA] = al_map_rgb(66, 67, 62);
	square_colors[PIEZA_I] = al_map_rgb(0, 255, 255);
	square_colors[PIEZA_J] = al_map_rgb(0, 200, 245);
	square_colors[PIEZA_O] = al_map_rgb(255, 255, 0);
	square_colors[PIEZA_L] = al_map_rgb(250, 150, 50);
	square_colors[PIEZA_S] = al_map_rgb(0, 255, 127);
	square_colors[PIEZA_Z] = al_map_rgb(250, 50, 50);
	square_colors[PIEZA_T] = al_map_rgb(200, 30, 200);
	square_colors[BORDE] = al_map_rgb(124, 121, 108);
}

static void init_board_border_colors(ALLEGRO_COLOR square_colors[])
{
	square_colors[NADA] = al_map_rgb(124, 121, 108);
	square_colors[PIEZA_I] = al_map_rgb(0, 150, 150);
	square_colors[PIEZA_J] = al_map_rgb(0, 125, 150);
	square_colors[PIEZA_O] = al_map_rgb(150, 150, 0);
	square_colors[PIEZA_L] = al_map_rgb(200, 110, 0);
	square_colors[PIEZA_S] = al_map_rgb(0, 155, 80);
	square_colors[PIEZA_Z] = al_map_rgb(255, 0, 0);
	square_colors[PIEZA_T] = al_map_rgb(128, 0, 128);
	square_colors[BORDE] = al_map_rgb(66, 67, 62);
}

void play_game(element_t* elem, game_mode_t mode, window_state_t* state, highscore_t *highscore)
{
	al_clear_to_color(al_map_rgb(20, 20, 20));
	al_draw_bitmap(elem->game_backround, 0, 0, 0);
	al_stop_samples();
	al_play_sample(elem->effect_play, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_play_sample_instance(elem->sample_game_reg);

	// creamos e inicializamos un arreglo con los colores de las distintas piezas
	ALLEGRO_COLOR square_colors[9];
	ALLEGRO_COLOR square_border_colors[9];
	init_board_colors(square_colors);
	init_board_border_colors(square_border_colors);

	srand(time(NULL));
	inicializarTiempo();

	char matris[BOARD_LENGHT][BOARD_WIDTH];
	char matris_auxiliar[BOARD_LENGHT][BOARD_WIDTH];
	char matris_prediccion[BOARD_LENGHT][BOARD_WIDTH];
	char blinking_matrix[BOARD_LENGHT][BOARD_WIDTH];

	char filas_tetris[BOARD_LENGHT];

	for (int i = 0; i < BOARD_LENGHT; i++) // llena de 0 la matriz el interior y define los bordes
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (i == 0 || i == 17 || j == 0 || j == 11)
			{
				matris[i][j] = BORDE;
				blinking_matrix[i][j] = BORDE;
			}
			else
			{
				matris[i][j] = NADA;
				blinking_matrix[i][j] = NADA;
			}
		}
	}

	if (mode.no_empty)
	{
		crearTablero(matris);
	}
	int puntaje = 0;
	int veces = 0;

	inicializarTiempo();
	inicializarPieza();
	bloque_t pieza = Crear_Pieza();
	bloque_t pieza_prediccion = pieza;

	ALLEGRO_EVENT ev;
	if (mode.blanking)
	{
		al_start_timer(elem->timer_on);
	}
	bool playing = true;
	bool draw = true;
	bool pause = false;
	bool tetris = false;
	bool off = false;

	while (playing)
	{
		if (!al_get_sample_instance_playing(elem->sample_game_reg))
		{
			al_play_sample_instance(elem->sample_game_reg);
		}

		if (al_get_next_event(elem->event_queue, &ev)) // pedimos el evento que venga
		{

			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case GIRAR_AL_2:
				case GIRAR_AL:
					playing = !jugarTetris('w', &pieza, matris, &puntaje, mode);
					al_play_sample(elem->effect_rotate, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				case BAJAR_AL_2:
				case BAJAR_AL:
					playing = !jugarTetris('s', &pieza, matris, &puntaje, mode);
					al_play_sample(elem->effect_move, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				case DERECHA_AL_2:
				case DERECHA_AL:
					playing = !jugarTetris('d', &pieza, matris, &puntaje, mode);
					al_play_sample(elem->effect_move, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				case IZQUIERDA_AL_2:
				case IZQUIERDA_AL:
					playing = !jugarTetris('a', &pieza, matris, &puntaje, mode);
					al_play_sample(elem->effect_move, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				case BAJAR_TODO:
					playing = !jugarTetris(' ', &pieza, matris, &puntaje, mode);
					al_play_sample(elem->effect_landing, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					break;
				case PAUSE:
					draw_pause_menu(state, elem, &playing);
					al_draw_bitmap(elem->game_backround, 0, 0, 0);
					al_flip_display();
					break;
				}

				draw = true;
			}

			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				*state = CLOSE_DISPLAY;
				playing = false;
			}

			if (mode.blanking && ev.type == ALLEGRO_EVENT_TIMER)
			{
				if (ev.timer.source == elem->timer_off)
				{
					off = false;
					al_stop_timer(elem->timer_off);
					al_start_timer(elem->timer_on);
				}
				else if (ev.timer.source == elem->timer_on)
				{
					off = true;
					al_stop_timer(elem->timer_on);
					al_start_timer(elem->timer_off);
					draw_board(blinking_matrix, blinking_matrix, square_colors, square_border_colors);
				}
			}
		}


		if (playing && *state == GAME)
		{
			playing = !jugarTetris('\0', &pieza, matris, &puntaje, mode); // actualizamos
		}

		veces++;

		if (veces % 1000 || tetris)
		{
			veces = 0;
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
					matris_auxiliar[i][j] = matris[i][j];
					matris_prediccion[i][j] = matris[i][j];
				}
			}

			//veamos donde caeria la pieza
			pieza_prediccion = pieza;
			bool flag_bajar = Bajar_Pieza(&pieza_prediccion, matris_prediccion);
			while (flag_bajar)
			{
				flag_bajar = Bajar_Pieza(&pieza_prediccion, matris_prediccion);
			}
			Estacionar(&pieza_prediccion, matris_prediccion);


			Estacionar(&pieza, matris_auxiliar); // estacionamos la pieza que se esta moviendo para visualizarla

			if (!off)
			{
				draw_board(matris_auxiliar, matris_prediccion, square_colors, square_border_colors);
			}

			puntaje += borrarFila(matris, filas_tetris, &tetris);

			if (tetris)
			{
				al_play_sample(elem->effect_tetris, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				es_tetris_animación(filas_tetris, square_colors, elem);
				if (!off)
				{
					draw_board(matris_auxiliar, matris_prediccion, square_colors, square_border_colors);
				}
				tetris = false;
			}

			mostrar_puntaje(elem, puntaje);
			show_next_piece(square_colors, square_border_colors, elem);

			draw = false;
		}

	}

	al_stop_sample_instance(elem->sample_game_reg);


	if (mode.blanking)
	{
		al_stop_timer(elem->timer_on);
		al_stop_timer(elem->timer_off);
		draw_board(matris_auxiliar, matris_prediccion, square_colors, square_border_colors);
	}

	if (*state != CLOSE_DISPLAY)
	{
		game_over(state, elem, puntaje, highscore);
	}
}

static void game_over(window_state_t* state, element_t* elem, int puntaje, highscore_t* highScore)
{
	ALLEGRO_EVENT ev;
	al_clear_to_color(al_map_rgb(20, 20, 20));
	al_draw_bitmap(elem->game_backround, 0, 0, 0);
	al_flip_display();

	al_stop_samples();
	al_play_sample(elem->effect_game_over, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

	int times;
	for (times = 0; times < 4; times++)
	{
		al_draw_text(elem->title_border, al_color_name("black"), SCREEN_W / 2, SCREEN_H / 6, 1, "GAME OVER");
		al_draw_text(elem->title, times % 2 ? al_color_name("white") : al_color_name("red"), SCREEN_W / 2, SCREEN_H / 6, 1, "GAME OVER");
		al_rest(0.300);
		al_flip_display();
	}

	// al_play_sample(elem->effect_game_over, 1.0, 1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_play_sample(elem->sample_game_over, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

	//botones 
	button_t play = { "PLAY AGAIN",SCREEN_W / 2, SCREEN_H * 0.65, 130, 40, 20,
					false, al_map_rgb(100,110,200), al_map_rgb(100,0,200),
					elem->buttons };

	button_t highscore = { "HIGHSCORE" ,SCREEN_W / 2, SCREEN_H * 0.80, 130, 40, 20,
					false,al_map_rgb(100,110,200), al_map_rgb(100,0,200),
					elem->buttons };

	button_t* botones[] = { &play, &highscore, NULL };

	char buffer[6];
	_itoa_s(puntaje, buffer, 6, 10);

	int position = is_highscore(puntaje, highScore);
	char buffer2[4];
	_itoa_s(position, buffer2, 4, 10);

	if (position <= NUMBER_OF_PLAYERS)
	{
		al_play_sample(elem->effect_highscore, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		char name[4] = "   ";
		int c = 0;
		bool waiting = true;
		while (waiting)
		{
			al_clear_to_color(al_map_rgb(20, 20, 20));
			al_draw_bitmap(elem->game_backround, 0, 0, 0);

			al_draw_text(elem->title_border, al_color_name("black"), SCREEN_W / 2, SCREEN_H / 6, 1, "GAME OVER");
			al_draw_text(elem->title, al_color_name("white"), SCREEN_W / 2, SCREEN_H / 6, 1, "GAME OVER");
			draw_buttons(botones, al_color_name("white"));

			al_draw_text(elem->buttons, al_color_name("red"), SCREEN_W / 2 - 40, SCREEN_H / 6 + SIZE_OF_TITLE, ALLEGRO_ALIGN_CENTRE, "SCORE: ");
			al_draw_text(elem->buttons, al_color_name("red"), SCREEN_W / 2 + 30, SCREEN_H / 6 + SIZE_OF_TITLE, 0, buffer);

			al_draw_text(elem->highscore_news, al_color_name("yellow"), SCREEN_W / 2 - 10, SCREEN_H / 6 + SIZE_OF_TITLE + 45, ALLEGRO_ALIGN_CENTRE, "New #");
			al_draw_text(elem->highscore_news, al_color_name("yellow"), SCREEN_W / 2 + 50, SCREEN_H / 6 + SIZE_OF_TITLE + 45, ALLEGRO_ALIGN_CENTRE, buffer2);

			al_set_target_bitmap(elem->bitmap);

			// Dibujar un rectángulo con transparencia
			al_clear_to_color(al_map_rgba(66, 67, 62, 230));

			al_set_target_backbuffer(elem->display);


			// Dibujar el bitmap en el display
			al_draw_bitmap(elem->bitmap, SCREEN_W / 4, SCREEN_H / 4, 0);
			al_draw_rectangle(SCREEN_W / 4, SCREEN_H / 4, SCREEN_W / 4 + SCREEN_W / 2, SCREEN_H / 4 + SCREEN_H / 2, al_map_rgb(255, 255, 255), 4);
			al_draw_text(elem->pause_menu, al_map_rgb(190, 171, 30), SCREEN_W / 2, SCREEN_H * 0.30, ALLEGRO_ALIGN_CENTRE, "HIGHSCORE");

			al_draw_text(elem->buttons, al_map_rgb(190, 171, 30), SCREEN_W / 2, SCREEN_H * 0.30 + 70, ALLEGRO_ALIGN_CENTRE, "Please enter your name: ");

			al_get_next_event(elem->event_queue, &ev);

			//analizamos si se cerró la ventana
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				waiting = false;
				*state = CLOSE_DISPLAY;
			}

			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
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

		al_play_sample(elem->effect_highscore, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		set_highscore(highScore, puntaje, name);
	}

	al_clear_to_color(al_map_rgb(20, 20, 20));

	al_draw_bitmap(elem->game_backround, 0, 0, 0);

	draw_buttons(botones, al_color_name("white"));

	al_draw_text(elem->title_border, al_color_name("black"), SCREEN_W / 2, SCREEN_H / 6, 1, "GAME OVER");
	al_draw_text(elem->title, al_color_name("white"), SCREEN_W / 2, SCREEN_H / 6, 1, "GAME OVER");

	al_draw_text(elem->buttons_border, al_color_name("black"), SCREEN_W / 2 - 40, SCREEN_H / 6 + SIZE_OF_TITLE, ALLEGRO_ALIGN_CENTRE, "SCORE: ");
	al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), SCREEN_W / 2 - 40, SCREEN_H / 6 + SIZE_OF_TITLE, ALLEGRO_ALIGN_CENTRE, "SCORE: ");

	al_draw_text(elem->buttons_border, al_color_name("black"), SCREEN_W / 2 + 30, SCREEN_H / 6 + SIZE_OF_TITLE, 0, buffer);
	al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), SCREEN_W / 2 + 30, SCREEN_H / 6 + SIZE_OF_TITLE, 0, buffer);

	if (position <= NUMBER_OF_PLAYERS)
	{
		al_draw_text(elem->highscore_news, al_color_name("yellow"), SCREEN_W / 2 - 10, SCREEN_H / 6 + SIZE_OF_TITLE + 45, ALLEGRO_ALIGN_CENTRE, "New #");
		al_draw_text(elem->highscore_news, al_color_name("yellow"), SCREEN_W / 2 + 50, SCREEN_H / 6 + SIZE_OF_TITLE + 45, ALLEGRO_ALIGN_CENTRE, buffer2);
	}
	al_flip_display();

	//esperamos a alguna selección
	bool waitingForUpdate = true;
	bool draw = false;
	int veces = 0;

	while (waitingForUpdate && *state != CLOSE_DISPLAY)
	{
		al_get_next_event(elem->event_queue, &ev);//pedimos el evento que venga

		//analizamos si se cerró la ventana
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			*state = CLOSE_DISPLAY;
			waitingForUpdate = false;
		}

		//vemos si se posicionó el mouse sobre un botón
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			int i;
			for (i = 0; botones[i]; i++)
			{
				if (!botones[i]->press && (ev.mouse.x <= botones[i]->x_center + botones[i]->width
					&& ev.mouse.x >= botones[i]->x_center - botones[i]->width
					&& ev.mouse.y <= botones[i]->y_center + botones[i]->height
					&& ev.mouse.y >= botones[i]->y_center - botones[i]->height))
				{
					if (!botones[i]->press) //si el botón cambia de estado, dibujamos
					{
						draw = true;
					}
					botones[i]->press = true;// actualizamos el estado del botón
					al_play_sample(elem->effect_cursor, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}

				else if (botones[i]->press && (ev.mouse.x > botones[i]->x_center + botones[i]->width
					|| ev.mouse.x < botones[i]->x_center - botones[i]->width
					|| ev.mouse.y > botones[i]->y_center + botones[i]->height
					|| ev.mouse.y < botones[i]->y_center - botones[i]->height))
				{
					if (botones[i]->press)//si el botón cambia de estado, dibujamos
					{
						draw = true;
					}
					botones[i]->press = false;// actualizamos el estado del botón
				}

			}
		}

		//analizamos si se pulso algún botón
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.x <= botones[JUGAR]->x_center + botones[JUGAR]->width
				&& ev.mouse.x >= botones[JUGAR]->x_center - botones[JUGAR]->width
				&& ev.mouse.y <= botones[JUGAR]->y_center + botones[JUGAR]->height
				&& ev.mouse.y >= botones[JUGAR]->y_center - botones[JUGAR]->height)
			{
				*state = GAME_SEL;
				al_play_sample(elem->effect_play, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				al_rest(0.4);
				al_stop_samples();
				al_play_sample(elem->sample_menu, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
				waitingForUpdate = false;
			}

			else if (ev.mouse.x <= botones[PUNTAJE]->x_center + botones[PUNTAJE]->width
				&& ev.mouse.x >= botones[PUNTAJE]->x_center - botones[PUNTAJE]->width
				&& ev.mouse.y <= botones[PUNTAJE]->y_center + botones[PUNTAJE]->height
				&& ev.mouse.y >= botones[PUNTAJE]->y_center - botones[PUNTAJE]->height)
			{
				*state = HIGHSCORE;
				al_play_sample(elem->effect_play, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				al_rest(0.6);
				waitingForUpdate = false;
			}
		}

		if (++veces % 1000)
		{
			draw = true;
			veces = 0;
		}

		//redibujamos si es necesario
		if (draw)
		{
			draw_buttons(botones, al_color_name("white"));
			al_flip_display(); //cargamos el buffer en el display
			draw = false; //cambiamos el estado de draw
		}
	}

}

static void draw_pause_menu(window_state_t* state, element_t* elem, bool* playing)
{
	al_play_sample(elem->effect_pause, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_set_sample_instance_gain(elem->sample_game_reg, 0.2);

	ALLEGRO_EVENT ev;
	bool waitingForUpdate = true;
	bool draw = true;

	al_set_target_bitmap(elem->bitmap);

	// Dibujar un rectángulo rojo con transparencia
	al_clear_to_color(al_map_rgba(66, 67, 62, 140));

	al_set_target_backbuffer(elem->display);


	// Dibujar el bitmap en el display
	al_draw_bitmap(elem->bitmap, SCREEN_W / 4, SCREEN_H / 4, 0);
	al_draw_rectangle(SCREEN_W / 4, SCREEN_H / 4, SCREEN_W / 4 + SCREEN_W / 2, SCREEN_H / 4 +SCREEN_H / 2, al_map_rgb(255, 255, 255), 4);
	al_draw_text(elem->pause_menu, al_map_rgb(195, 44, 23), SCREEN_W / 2, SCREEN_H * 0.30, ALLEGRO_ALIGN_CENTRE, "PAUSE");

	//botones 
	button_t resume = { "RESUME", SCREEN_W / 2, SCREEN_H * 0.50, 130, 40, 20,
					false, al_map_rgb(100,110,200), al_map_rgb(100,0,200),
					elem->buttons };

	button_t quit = { "QUIT" ,SCREEN_W / 2, SCREEN_H * 0.65, 130, 40, 20,
					false, al_map_rgb(231, 87, 65), al_map_rgb(195, 44, 23),
					elem->buttons };

	button_t* botones[] = { &resume, &quit, NULL };
	al_flip_display();

	int veces = 0;
	while (waitingForUpdate)
	{
		if (!al_get_sample_instance_playing(elem->sample_game_reg))
		{
			al_play_sample_instance(elem->sample_game_reg);
			al_set_sample_instance_gain(elem->sample_game_reg, 0.2);
		}

		al_get_next_event(elem->event_queue, &ev);//pedimos el evento que venga

		//analizamos si se cerró la ventana
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			*state = CLOSE_DISPLAY;
			waitingForUpdate = false;
			*playing = false;
		}

		//vemos si se posicionó el mouse sobre un botón
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			int i;
			for (i = 0; botones[i]; i++)
			{
				if (!botones[i]->press && (ev.mouse.x <= botones[i]->x_center + botones[i]->width
					&& ev.mouse.x >= botones[i]->x_center - botones[i]->width
					&& ev.mouse.y <= botones[i]->y_center + botones[i]->height
					&& ev.mouse.y >= botones[i]->y_center - botones[i]->height))
				{
					if (!botones[i]->press) //si el botón cambia de estado, dibujamos
					{
						draw = true;
					}
					botones[i]->press = true;// actualizamos el estado del botón
					al_play_sample(elem->effect_cursor, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				}

				else if (botones[i]->press && (ev.mouse.x > botones[i]->x_center + botones[i]->width
					|| ev.mouse.x < botones[i]->x_center - botones[i]->width
					|| ev.mouse.y > botones[i]->y_center + botones[i]->height
					|| ev.mouse.y < botones[i]->y_center - botones[i]->height))
				{
					if (botones[i]->press)//si el botón cambia de estado, dibujamos
					{
						draw = true;
					}
					botones[i]->press = false;// actualizamos el estado del botón
				}

			}
		}

		//analizamos si se pulso algún botón
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.x <= botones[RESUME]->x_center + botones[RESUME]->width
				&& ev.mouse.x >= botones[RESUME]->x_center - botones[RESUME]->width
				&& ev.mouse.y <= botones[RESUME]->y_center + botones[RESUME]->height
				&& ev.mouse.y >= botones[RESUME]->y_center - botones[RESUME]->height)
			{
				al_play_sample(elem->effect_pause, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				al_rest(0.4);
				al_set_sample_instance_gain(elem->sample_game_reg, 1.0);
				waitingForUpdate = false;
			}

			else if (ev.mouse.x <= botones[QUIT]->x_center + botones[QUIT]->width
				&& ev.mouse.x >= botones[QUIT]->x_center - botones[QUIT]->width
				&& ev.mouse.y <= botones[QUIT]->y_center + botones[QUIT]->height
				&& ev.mouse.y >= botones[QUIT]->y_center - botones[QUIT]->height)
			{
				al_play_sample(elem->effect_play, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				al_rest(0.4);
				waitingForUpdate = false;
				*playing = false;
			}
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == PAUSE)
		{
			al_play_sample(elem->effect_pause, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			al_rest(0.4);
			al_set_sample_instance_gain(elem->sample_game_reg, 1.0);
			waitingForUpdate = false;

		}

		if (++veces % 1000)
		{
			draw = true;
			veces = 0;
		}

		//redibujamos si es necesario
		if (draw)
		{
			draw_buttons(botones, al_color_name("white"));
			al_flip_display(); //cargamos el buffer en el display
			draw = false; //cambiamos el estado de draw
		}
	}
}