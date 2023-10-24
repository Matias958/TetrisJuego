#include "botones.h"

/*DRAW_BUTTONS()
* Función encargada de dibujar todos los botones de un arreglo, colocando el texto en el color dado
* Recibe: arreglo de botones a dibjuar y color de texto (en formato de ALLEGRO_COLOR)
* Devuelve: -
 */
void draw_buttons(button_t *botones[],  ALLEGRO_COLOR text)
{
    int i=0;
    for(i=0; botones[i];i++)
    {
        al_draw_filled_rounded_rectangle(botones[i]->x_center - botones[i]->width,
                botones[i]->y_center - botones[i]->height, botones[i]->x_center + botones[i]->width,
                botones[i]->y_center + botones[i]->height, botones[i]->radius, 
                botones[i]->radius, !botones[i]->press? botones[i]->color_uprs : botones[i]->color_prs);
        
        al_draw_rounded_rectangle(botones[i]->x_center - botones[i]->width,
                botones[i]->y_center - botones[i]->height, botones[i]->x_center + botones[i]->width,
                botones[i]->y_center + botones[i]->height, botones[i]->radius, botones[i]->radius, al_color_name("white"),2);
        
        al_draw_text(botones[i]->font,text, botones[i]->x_center,
                botones[i]->y_center- botones[i]->height*0.75, 1, botones[i]->name);
    }
}