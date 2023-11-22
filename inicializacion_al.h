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

/************** MACROS ***************/

/*TAMAÑO DE LA PANTALLA*/
#define SCREEN_W  1260
#define SCREEN_H  720


/************** ESTRUCTURAS ***************/

typedef struct
{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP* bitmap;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;

    ALLEGRO_FONT *title;
    ALLEGRO_FONT *buttons;
    ALLEGRO_FONT *game_modes;
    ALLEGRO_FONT *font_in_game;
    ALLEGRO_FONT *game_over;
    ALLEGRO_FONT *pause_menu;

    ALLEGRO_SAMPLE *sample_menu;
    ALLEGRO_SAMPLE *sample_game;
    ALLEGRO_SAMPLE* sample_game_over;

    ALLEGRO_SAMPLE *effect_tetris;
    ALLEGRO_SAMPLE *effect_play;
    ALLEGRO_SAMPLE *effect_cursor;
    ALLEGRO_SAMPLE *effect_select;
    ALLEGRO_SAMPLE *effect_rotate;
    ALLEGRO_SAMPLE *effect_move;
    ALLEGRO_SAMPLE *effect_landing;
    ALLEGRO_SAMPLE *effect_pause;
    ALLEGRO_SAMPLE *effect_game_over;
}element_t;

/************** PROTOTIPOS ***************/

/*INICIALIZA_AL()
* Función encargada de inicializar los elementos de allegro.
* Recibe: Una estructura element_t con los elementos a inicializar.
* Devuelve: Un int que indica si se logró o no inicializar todo correctamente.
*/
int inicializa_al(element_t* elem); 

#endif // INICIALIZACION_AL_H
