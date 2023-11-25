#ifndef INICIALIZACION_AL_H
#define INICIALIZACION_AL_H

/************** HEADERS ***************/
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_ttf.h"
#include <allegro5/allegro_audio.h> 
#include <allegro5/allegro_acodec.h> //Extensiones con acodec .wav, .flac, .ogg, .it, .mod, .s3m, .xm.
#include <allegro5/allegro_image.h>

/************** MACROS ***************/

/*TAMAÑO DE LA PANTALLA*/
#define SCREEN_W  1260
#define SCREEN_H  720


/************** ESTRUCTURAS ***************/

typedef struct
{
    ALLEGRO_DISPLAY* display;

    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_BITMAP *menu_backround;
    ALLEGRO_BITMAP *highscore_backround;
    ALLEGRO_BITMAP *game_backround;
    ALLEGRO_BITMAP *mirrored;
    ALLEGRO_BITMAP *blinking;
    ALLEGRO_BITMAP *no_empty;

    ALLEGRO_BITMAP *mirrored_prs;
    ALLEGRO_BITMAP *blinking_prs;
    ALLEGRO_BITMAP *no_empty_prs;
    

    ALLEGRO_EVENT_QUEUE *event_queue;

    ALLEGRO_TIMER *timer_on;
    ALLEGRO_TIMER* timer_off;
    

    ALLEGRO_FONT *title;
    ALLEGRO_FONT* title_border;
    ALLEGRO_FONT *buttons;
    ALLEGRO_FONT *buttons_border;
    ALLEGRO_FONT *game_modes;
    ALLEGRO_FONT *font_in_game;
    ALLEGRO_FONT *font_in_game_border;
    ALLEGRO_FONT *game_over;
    ALLEGRO_FONT *pause_menu;
    ALLEGRO_FONT *highscore_news;

    ALLEGRO_SAMPLE *sample_menu;
    ALLEGRO_SAMPLE *sample_game;
    ALLEGRO_SAMPLE *sample_game_over;
    ALLEGRO_SAMPLE *sample_highscore;

    ALLEGRO_SAMPLE_INSTANCE *sample_game_reg;

    ALLEGRO_SAMPLE *effect_tetris;
    ALLEGRO_SAMPLE *effect_play;
    ALLEGRO_SAMPLE *effect_cursor;
    ALLEGRO_SAMPLE *effect_select;
    ALLEGRO_SAMPLE *effect_rotate;
    ALLEGRO_SAMPLE *effect_move;
    ALLEGRO_SAMPLE *effect_landing;
    ALLEGRO_SAMPLE *effect_pause;
    ALLEGRO_SAMPLE *effect_game_over;
    ALLEGRO_SAMPLE *effect_highscore;
}element_t;

/************** PROTOTIPOS ***************/

/*INICIALIZA_AL()
* Función encargada de inicializar los elementos de allegro.
* Recibe: Una estructura element_t con los elementos a inicializar.
* Devuelve: Un int que indica si se logró o no inicializar todo correctamente.
*/
int inicializa_al(element_t* elem); 

#endif // INICIALIZACION_AL_H
