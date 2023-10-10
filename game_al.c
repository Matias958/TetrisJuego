#include "game_al.h"
#include "botones.h"
#include "juego.h"

#define BOARD_WIDTH 12
#define BOARD_LENGHT 18

#define BOARD_START_X 300
#define BOARD_START_Y 100

#define SQUARE_SIZE 35

#define NEXT_PIECE_POS_X (BOARD_START_X + BOARD_WIDTH * SQUARE_SIZE)
#define NEXT_PIECE_POS_Y (BOARD_START_Y + BOARD_LENGHT * SQUARE_SIZE)

#define NEXT_PIECE_WIDTH   10
#define NEXT_PIECE_LENGHT  10

#define SQUARE_SIZE_WINDOWS 15

#define GIRAR_AL     ALLEGRO_KEY_W
#define DERECHA_AL   ALLEGRO_KEY_D
#define IZQUIERDA_AL ALLEGRO_KEY_A
#define BAJAR_AL     ALLEGRO_KEY_S

enum pieces_code {EMPTY, I, J, O, L, S, Z, T, WALL};

static void draw_board(char board[BOARD_LENGHT][BOARD_WIDTH], ALLEGRO_COLOR square_colors[]);
static void init_board_colors(ALLEGRO_COLOR square_colors[9]);
static void draw_next_piece(char piece, ALLEGRO_COLOR square_colors[9]);

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
    for(i=0; i < BOARD_LENGHT; i++)
    {
        for(j=0; j < BOARD_WIDTH; j++)
        {
            float x1 = BOARD_START_X + j * SQUARE_SIZE;
            float y1 = BOARD_START_Y + i * SQUARE_SIZE;
            
            al_draw_filled_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, square_colors[board[i][j]]);

            al_draw_rectangle(x1, y1, x1 + SQUARE_SIZE, y1 - SQUARE_SIZE, square_colors[EMPTY],2);
        }
    }
    
    
    al_flip_display();
    
}

static void draw_next_piece(char piece,ALLEGRO_COLOR square_colors[] ) //falta terminar
{
    int i;
    int j;
    
    for(i=0; i < NEXT_PIECE_LENGHT; i++)
    {
        for(j=0; j < NEXT_PIECE_WIDTH ; j++)
        {
            float x1 = NEXT_PIECE_POS_X + j * SQUARE_SIZE_WINDOWS;
            float y1 = NEXT_PIECE_POS_Y + i * SQUARE_SIZE_WINDOWS;
            
            
        }
    }
        
}


static void init_board_colors(ALLEGRO_COLOR square_colors[])
{
    square_colors[EMPTY] = al_map_rgb(18,55,107);
    square_colors[I] = al_map_rgb(0,255,255);
    square_colors[J] = al_map_rgb(0,0,255);
    square_colors[O] = al_map_rgb(255,255,0);
    square_colors[L] = al_map_rgb(255,127,0);
    square_colors[S] = al_map_rgb(0,255,0);
    square_colors[Z] = al_map_rgb(255,0,0);
    square_colors[T] = al_map_rgb(128,0,128);
    square_colors[WALL] = al_map_rgb(11,13,23);
}

void play_game(element_t *elem, game_mode_t mode, window_state_t *state)
{
    al_clear_to_color(al_map_rgb(20, 20, 20));

    //creamos e inicializamos un arreglo con los colores de las distintas piezas
    ALLEGRO_COLOR square_colors[9];
    init_board_colors(square_colors);
    
    ALLEGRO_EVENT ev;
    bool playing = true;
    bool draw = true;

    srand(time(NULL));
    inicializarTiempo();
    char matris[18][12];
    for (int i = 0; i < 18; i++)  //llena de 0 la matriz el interior y define los bordes
    {
        for (int j = 0; j < 12; j++)
        {
            if (i==0 || i==17 || j==0 || j==11)
            {
                matris[i][j]=BORDE;
            }
            else
            {
                matris[i][j]=NADA;
            }
            
        }
    }
    int puntaje = 0;

    bloque_t pieza = Crear_Pieza();

    while(playing)
    {
        al_get_next_event(elem->event_queue, &ev);//pedimos el evento que venga

        if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
                case GIRAR_AL:
                    playing = !jugarTetris('w', &pieza, matris, &puntaje);
                    break;
                case BAJAR_AL:
                    playing = !jugarTetris('s', &pieza, matris, &puntaje);
                    break;
                case DERECHA_AL:
                    playing = !jugarTetris('d', &pieza, matris, &puntaje);
                    break;
                case IZQUIERDA_AL:
                    playing = !jugarTetris('a', &pieza, matris, &puntaje);
                    break;
            }

            draw = true;
        }

        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *state = CLOSE_DISPLAY;
            playing = false;
        }



        if(draw)
        {
            draw_board(matris, square_colors);
            draw = false;
        }
    }
}