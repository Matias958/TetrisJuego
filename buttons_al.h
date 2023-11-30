/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: buttons_al.c
*Descripcion: dibujo de botones en Allegro
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#ifndef BUTTONS_AL_H
#define BUTTONS_AL_H

/************** HEADERS ***************/

#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_ttf.h"

/************** ESTRUCTURAS ***************/

/*button_t
* Estructura que contiene toda la información de un boton
*/
typedef struct
{
    char *name;
    float x_center;
    float y_center;
    float width;
    float height;
    float radius;
    bool press;
    ALLEGRO_COLOR color_prs;
    ALLEGRO_COLOR color_uprs;
    ALLEGRO_FONT *font;
} button_t;

/************** PROTOTIPOS ***************/

/*drawButtons()
 * Función encargada de dibujar todos los botones de un arreglo, colocando el texto en el color dado
 * Recibe: buttons (arreglo de botones a dibjuar) y textColor (color de texto)
 * Devuelve: -
 */
void drawButtons(button_t *buttons[], ALLEGRO_COLOR textColor);

#endif
