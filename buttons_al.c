#include "buttons_al.h"

/*DRAW_BUTTONS()
 * Función encargada de dibujar todos los botones de un arreglo, colocando el texto en el color dado
 * Recibe: arreglo de botones a dibjuar y color de texto (en formato de ALLEGRO_COLOR)
 * Devuelve: -
 */
void drawButtons(button_t *buttons[], ALLEGRO_COLOR text)
{
        int i = 0;
        for (i = 0; buttons[i]; i++)
        {
                al_draw_filled_rounded_rectangle(buttons[i]->x_center - buttons[i]->width,
                                                 buttons[i]->y_center - buttons[i]->height, buttons[i]->x_center + buttons[i]->width,
                                                 buttons[i]->y_center + buttons[i]->height, buttons[i]->radius,
                                                 buttons[i]->radius, !buttons[i]->press ? buttons[i]->color_uprs : buttons[i]->color_prs);

                al_draw_rounded_rectangle(buttons[i]->x_center - buttons[i]->width,
                                          buttons[i]->y_center - buttons[i]->height, buttons[i]->x_center + buttons[i]->width,
                                          buttons[i]->y_center + buttons[i]->height, buttons[i]->radius, buttons[i]->radius, al_color_name("white"), 2);

                al_draw_text(buttons[i]->font, text, buttons[i]->x_center,
                             buttons[i]->y_center - buttons[i]->height * 0.75, 1, buttons[i]->name);
        }
}