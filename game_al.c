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

#define TAMANO_DE_VENTANA_PUNTAJE_X 150
#define TAMANO_DE_VENTANA_PUNTAJE_Y 100
#define PUNTAJE_VENTANA_X (BOARD_START_X + BOARD_WIDTH * SQUARE_SIZE + 20)
#define PUNTAJE_VENTANA_Y BOARD_START_Y

#define GIRAR_AL ALLEGRO_KEY_W
#define DERECHA_AL ALLEGRO_KEY_D
#define IZQUIERDA_AL ALLEGRO_KEY_A
#define BAJAR_AL ALLEGRO_KEY_S
#define PAUSE ALLEGRO_KEY_ESCAPE
#define BAJAR_TODO ALLEGRO_KEY_SPACE

#define SIZE_OF_TITLE 200

enum bordes { NADA_B = BORDE + 1, PIEZA_I_B, PIEZA_J_B, PIEZA_L_B, PIEZA_O_B, PIEZA_S_B, PIEZA_T_B, PIEZA_Z_B, BORDE_B };
enum game_over_options { JUGAR, PUNTAJE }; 

static void draw_board(char board[BOARD_LENGHT][BOARD_WIDTH], ALLEGRO_COLOR square_colors[], ALLEGRO_COLOR square_border_colors[]);
static void init_board_colors(ALLEGRO_COLOR square_colors[]);
static void init_board_border_colors(ALLEGRO_COLOR square_colors[]);
static void draw_next_piece(char piece, ALLEGRO_COLOR square_colors[]);
static void mostrar_puntaje(element_t *elem, int puntaje);
static void es_tetris_animación(char filas_tetris[BOARD_LENGHT], ALLEGRO_COLOR square_colors[], element_t* elem);
static void game_over(window_state_t* state, element_t* elem, int puntaje);
static void draw_pause_menu(ALLEGRO_EVENT* ev, element_t* elem);

/* DRAW_BOARD()
 *
 *
 *
 *
 */

static void draw_board(char board[BOARD_LENGHT][BOARD_WIDTH], ALLEGRO_COLOR square_colors[], ALLEGRO_COLOR square_border_colors[])
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

    al_flip_display();
}
static void mostrar_puntaje(element_t *elem, int puntaje)
{

    al_draw_text(elem->buttons, al_map_rgb(255, 255, 255), PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE_X / 2, PUNTAJE_VENTANA_Y - 3 * TAMANO_DE_VENTANA_PUNTAJE_Y / 5, 1, "SCORE");
    al_draw_filled_rectangle(PUNTAJE_VENTANA_X, PUNTAJE_VENTANA_Y, PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE_X, PUNTAJE_VENTANA_Y + TAMANO_DE_VENTANA_PUNTAJE_Y, al_map_rgb(66, 67, 62));
    al_draw_rectangle(PUNTAJE_VENTANA_X, PUNTAJE_VENTANA_Y, PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE_X, PUNTAJE_VENTANA_Y + TAMANO_DE_VENTANA_PUNTAJE_Y, al_map_rgb(124, 121, 108), 6);
    char buffer[6];
    _itoa_s(puntaje, buffer,6, 10);
    al_draw_text(elem->buttons, al_map_rgb(124, 121, 108), PUNTAJE_VENTANA_X + TAMANO_DE_VENTANA_PUNTAJE_X / 2, PUNTAJE_VENTANA_Y + TAMANO_DE_VENTANA_PUNTAJE_Y / 5, 1, buffer);
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

void play_game(element_t *elem, game_mode_t mode, window_state_t *state)
{
    al_clear_to_color(al_map_rgb(20, 20, 20));
    al_stop_samples();
    al_play_sample(elem->effect_play, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    al_play_sample(elem->sample_game, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);


    // creamos e inicializamos un arreglo con los colores de las distintas piezas
    ALLEGRO_COLOR square_colors[9];
    ALLEGRO_COLOR square_border_colors[9];
    init_board_colors(square_colors); 
    init_board_border_colors(square_border_colors);

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
                al_play_sample(elem->effect_rotate, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case BAJAR_AL:
                playing = !jugarTetris('s', &pieza, matris, &puntaje);
                al_play_sample(elem->effect_move, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case DERECHA_AL:
                playing = !jugarTetris('d', &pieza, matris, &puntaje);
                al_play_sample(elem->effect_move, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case IZQUIERDA_AL:
                playing = !jugarTetris('a', &pieza, matris, &puntaje);
                al_play_sample(elem->effect_move, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case BAJAR_TODO:
                playing = !jugarTetris(' ', &pieza, matris, &puntaje);
                al_play_sample(elem->effect_landing, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break;
            case PAUSE:
                al_play_sample(elem->effect_pause, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                draw_pause_menu(&ev,elem);
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

            draw_board(matris_auxiliar, square_colors, square_border_colors);
            puntaje += borrarFila(matris, filas_tetris, &tetris);

            if (tetris)
            {
                al_play_sample(elem->effect_tetris, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
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

    if (*state != CLOSE_DISPLAY)
    {
        game_over(state, elem, puntaje);
    }
}

static void game_over(window_state_t* state, element_t* elem, int puntaje)
{
    al_clear_to_color(al_map_rgb(20, 20, 20));
    al_flip_display();

    al_stop_samples();
    al_play_sample(elem->effect_game_over, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

    char buffer[6];
    _itoa_s(puntaje, buffer, 6, 10);
    al_draw_text(elem->buttons, al_color_name("red"), SCREEN_W / 2 - 20, SCREEN_H / 6 + SIZE_OF_TITLE, ALLEGRO_ALIGN_CENTRE, "SCORE: ");
    al_draw_text(elem->buttons, al_color_name("red"), SCREEN_W / 2 + 50, SCREEN_H / 6 + SIZE_OF_TITLE, 0, buffer);

    int times;
    for (times = 0; times < 4; times++)
    {
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

    draw_buttons(botones, al_color_name("white"));

    al_flip_display();

    //esperamos a alguna selección
    ALLEGRO_EVENT ev;
    bool waitingForUpdate = true;
    bool draw = false;

    while (waitingForUpdate)
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
                waitingForUpdate = false;
            }
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

static void draw_pause_menu(ALLEGRO_EVENT *ev, element_t *elem)
{
    bool waitingForUpdate = true;
    while(waitingForUpdate)
    {

    }
}