#include "game_al.h"
#include "botones.h"
#include "juego.h"
#include <stdlib.h>

#define BOARD_WIDTH 12
#define BOARD_LENGHT 18

#define BOARD_START_X 300
#define BOARD_START_Y 100

#define SQUARE_SIZE 35

#define NEXT_PIECE_POS_X (BOARD_START_X + BOARD_WIDTH * SQUARE_SIZE)
#define NEXT_PIECE_POS_Y (BOARD_START_Y + BOARD_LENGHT * SQUARE_SIZE)

#define TAMANO_DE_VENTANA_PUNTAJE 100
#define PUNTAJE_VENTANA_X (BOARD_START_X + BOARD_WIDTH * SQUARE_SIZE + 20)
#define PUNTAJE_VENTANA_Y BOARD_START_Y

#define GIRAR_AL ALLEGRO_KEY_W
#define DERECHA_AL ALLEGRO_KEY_D
#define IZQUIERDA_AL ALLEGRO_KEY_A
#define BAJAR_AL ALLEGRO_KEY_S
#define PAUSE ALLEGRO_KEY_ESCAPE
#define BAJAR_TODO ALLEGRO_KEY_SPACE

static void draw_board(char board[BOARD_LENGHT][BOARD_WIDTH], ALLEGRO_COLOR square_colors[]);
static void init_board_colors(ALLEGRO_COLOR square_colors[9]);
static void draw_next_piece(char piece, ALLEGRO_COLOR square_colors[9]);
static void mostrar_puntaje(element_t *elem, int puntaje);
static void es_tetris_animación(char filas_tetris[BOARD_LENGHT], ALLEGRO_COLOR square_colors[], element_t* elem);

/* DRAW_BOARD()
 *
 *
 *
 *
 */

static void draw_board(char board[BOARD_LENGHT][BOARD_WIDTH], ALLEGRO_COLOR square_colors[])
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

            al_draw_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, square_colors[NADA], 2);
        }
    }

    al_flip_display();
}
static void mostrar_puntaje(element_t *elem, int puntaje)
{
    al_draw_filled_rectangle(PUNTAJE_VENTANA_X, PUNTAJE_VENTANA_Y, PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE, PUNTAJE_VENTANA_Y + TAMANO_DE_VENTANA_PUNTAJE, al_map_rgb(66, 67, 62));
    char buffer[6];
    _itoa_s(puntaje, buffer,6, 10);
    al_draw_text(elem->buttons, al_map_rgb(124, 121, 108), PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE / 2, PUNTAJE_VENTANA_Y + TAMANO_DE_VENTANA_PUNTAJE / 5, 1, buffer);
    al_flip_display();
}

static void es_tetris_animación(char filas_tetris[BOARD_LENGHT], ALLEGRO_COLOR square_colors[], element_t* elem)
{
    int i;
    int times;
    for (times = 0; times < 4; times++)
    {
        for (i = 0; filas_tetris[i] != FINAL_DEL_ARREGLO ; i++)
        {
            int j;
            for (j = 1; j < BOARD_WIDTH - 1; j++)
            {
                float x1 = BOARD_START_X + j * SQUARE_SIZE;
                float y1 = BOARD_START_Y + filas_tetris[i] * SQUARE_SIZE;

                al_draw_filled_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, times % 2 ? al_map_rgb(220, 20, 60) : al_map_rgb(35,235,195));
                al_draw_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, square_colors[NADA], 2);
            }
            al_draw_text(elem->font_in_game, al_map_rgb(255, 255, 255), BOARD_START_X + BOARD_WIDTH * SQUARE_SIZE,
                BOARD_START_Y + filas_tetris[i] * SQUARE_SIZE - SQUARE_SIZE + SQUARE_SIZE / 4, 0, "+100");
        }
        al_flip_display();
        al_rest(0.200);
    }
    al_clear_to_color(al_map_rgb(20, 20, 20));
}

static void draw_next_piece(char piece, ALLEGRO_COLOR square_colors[]) // falta terminar
{
    // int i;
    // int j;

    // for (i = 0; i < NEXT_PIECE_LENGHT; i++)
    // {
    //     for (j = 0; j < NEXT_PIECE_WIDTH; j++)
    //     {
    //         float x1 = NEXT_PIECE_POS_X + j * SQUARE_SIZE_WINDOWS;
    //         float y1 = NEXT_PIECE_POS_Y + i * SQUARE_SIZE_WINDOWS;
    //     }
    // }
}

static void init_board_colors(ALLEGRO_COLOR square_colors[])
{
    
    square_colors[NADA] = al_map_rgb(66, 67, 62);
    square_colors[PIEZA_I] = al_map_rgb(0, 255, 255);
    square_colors[PIEZA_J] = al_map_rgb(0, 0, 255);
    square_colors[PIEZA_O] = al_map_rgb(255, 255, 0);
    square_colors[PIEZA_L] = al_map_rgb(255, 127, 0);
    square_colors[PIEZA_S] = al_map_rgb(0, 255, 0);
    square_colors[PIEZA_Z] = al_map_rgb(255, 0, 0);
    square_colors[PIEZA_T] = al_map_rgb(128, 0, 128);
    square_colors[BORDE] = al_map_rgb(124, 121, 108);
}

void play_game(element_t *elem, game_mode_t mode, window_state_t *state)
{
    al_clear_to_color(al_map_rgb(20, 20, 20));
    al_stop_samples();
    al_play_sample(elem->effect_play, 1.0, 1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_play_sample(elem->sample_game, 1.0, 1.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);


    // creamos e inicializamos un arreglo con los colores de las distintas piezas
    ALLEGRO_COLOR square_colors[9];
    init_board_colors(square_colors); 
    srand(time(NULL));
    inicializarTiempo();

    char matris[BOARD_LENGHT][BOARD_WIDTH];
    char matris_auxiliar[BOARD_LENGHT][BOARD_WIDTH];

    char filas_tetris[BOARD_LENGHT];

    for (int i = 0; i < BOARD_LENGHT; i++) // llena de 0 la matriz el interior y define los bordes
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (i == 0 || i == 17 || j == 0 || j == 11)
            {
                matris[i][j] = BORDE;
            }
            else
            {
                matris[i][j] = NADA;
            }
        }
    }

    if(mode.no_empty)
    {
        crearTablero(matris);
    }
    int puntaje = 0;
    int veces = 0;

    inicializarTiempo();
    bloque_t pieza = Crear_Pieza();

    ALLEGRO_EVENT ev;
    bool playing = true;
    bool draw = true;
    bool pause = false;
    bool tetris = false;

    button_t pause_botton = {"JUGAR", SCREEN_W / 2, SCREEN_H * 0.65, 130, 40, 20,
                            false, al_map_rgb(100, 110, 200), al_map_rgb(100, 0, 200),
                            elem->buttons};

    while (playing)
    {
        al_get_next_event(elem->event_queue, &ev); // pedimos el evento que venga

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case GIRAR_AL:
                playing = !jugarTetris('w', &pieza, matris, &puntaje);
                al_play_sample(elem->effect_rotate, 1.0, 1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case BAJAR_AL:
                playing = !jugarTetris('s', &pieza, matris, &puntaje);
                al_play_sample(elem->effect_move, 1.0, 1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case DERECHA_AL:
                playing = !jugarTetris('d', &pieza, matris, &puntaje);
                al_play_sample(elem->effect_move, 1.0, 1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case IZQUIERDA_AL:
                playing = !jugarTetris('a', &pieza, matris, &puntaje);
                al_play_sample(elem->effect_move, 1.0, 1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case BAJAR_TODO:
                playing = !jugarTetris(' ', &pieza, matris, &puntaje);
                al_play_sample(elem->effect_landing, 1.0, 1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case PAUSE:
                pause = !pause;
                break;
            }

            draw = true;
        }

        if (!pause) // si no está pausado, actualizamos el juego
        {
            playing = !jugarTetris('\0', &pieza, matris, &puntaje); // actualizamos
        }

        veces++;

        if (veces % 1000 || tetris)
        {
            veces = 0;
            draw = true;
        }

        if (draw && playing)
        {
            if (!pause)
            {
                int i, j;
                // copia la matris de juego en una auxiliar para mostrar
                for (i = 0; i < BOARD_LENGHT; i++)
                {
                    for (j = 0; j < BOARD_WIDTH; j++)
                    {
                        matris_auxiliar[i][j] = matris[i][j];
                    }
                }

                Estacionar(&pieza, matris_auxiliar); // estacionamos la pieza que se esta moviendo para visualizarla
            }

            draw_board(matris_auxiliar, square_colors);
            puntaje += borrarFila(matris, filas_tetris, &tetris);

            if (tetris)
            {
                al_play_sample(elem->effect_tetris, 1.0, 1.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                es_tetris_animación(filas_tetris, square_colors, elem);
                tetris = false;
            }

            mostrar_puntaje(elem, puntaje);

            draw = false;
        }

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *state = CLOSE_DISPLAY;
            playing = false;
        }
    }
    *state = CLOSE_DISPLAY; // poner una pantalla de game over
}

static void draw_pause_menu(ALLEGRO_EVENT *ev, element_t *elem)
{

}