/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: buttons_al.c
*Descripcion: dibujo de botones en Allegro
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#include "buttons_al.h"

/*drawButtons()
 * Función encargada de dibujar todos los botones de un arreglo, colocando el texto en el color dado
 * Recibe: buttons (arreglo de botones a dibjuar) y textColor (color de texto)
 * Devuelve: -
 */
void drawButtons(button_t *buttons[], ALLEGRO_COLOR textColor)
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

                al_draw_text(buttons[i]->font, textColor, buttons[i]->x_center,
                             buttons[i]->y_center - buttons[i]->height * 0.75, 1, buttons[i]->name);
        }
}