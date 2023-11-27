#ifndef BUTTONS_AL_H
#define BUTTONS_AL_H

/************** HEADERS ***************/

#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_ttf.h"

/************** ESTRUCTURAS ***************/
typedef struct
{
    char* name;
    float x_center;
    float y_center;
    float width;
    float height;
    float radius;
    bool press;
    ALLEGRO_COLOR color_prs;
    ALLEGRO_COLOR color_uprs;
    ALLEGRO_FONT *font;
}button_t;

/************** PROTOTIPOS ***************/

/*DRAW_BUTTONS()
* Función encargada de dibujar todos los botones de un arreglo, colocando el texto en el color dado
* Recibe: arreglo de botones a dibjuar y color de texto (en formato de ALLEGRO_COLOR)
* Devuelve: -
 */
void draw_buttons(button_t *botones[],  ALLEGRO_COLOR text);

#endif 

