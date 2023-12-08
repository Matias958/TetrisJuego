/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: highscore_al.c
*Descripcion: aspecto gráfico en la muestra de
*           puntajes altos en Allegro
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

/************** HEADERS ***************/
#include <stdlib.h>
#include <stdio.h>
#include "highscore_al.h"
#include "buttons_al.h"

/*showHighScores()
* Función encargada de mostrar el TOP 5 historico del presente juego
* Recibe: elem (estructura que contiene los elementos de Allegro), highscore 
* (información actual del TOP5) y state (estructura que contiene el estado de 
* la ventana - game_state -: CLOSE_DISPLAY, MENU, GAME_SEL, HIGHSCORE o GAME).
* Devuelve: -
*/
void showHighScores(element_t *elem, highscore_t *highscore, window_state_t *state)
{
    ALLEGRO_EVENT ev;
    al_stop_samples();
    al_play_sample(elem->sampleHighscore, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    
    button_t play = { "PLAY", SCREEN_W / 2, SCREEN_H * 0.9, 100, 40, 20,
                     false, al_map_rgb(190, 171, 30), al_map_rgb(124, 109, 20),
                     elem->buttons };

    button_t* buttons[] = { &play, NULL };


    int trans;
    for (trans = 255; trans > 0; trans -= 2)
    {
        al_get_next_event(elem->eventQueue, &ev);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *state = CLOSE_DISPLAY;
            return;
        }

        al_draw_bitmap(elem->highscoreBackround, 0, 0, 0);

        al_draw_filled_rectangle(SCREEN_W / 5, SCREEN_H / 3, 4 * SCREEN_W / 5, 11 * SCREEN_H / 14,
            al_map_rgb(120, 110, 40));
        al_draw_rectangle(SCREEN_W / 5 + 10, SCREEN_H / 3 + 10, 4 * SCREEN_W / 5 - 10, 11 * SCREEN_H / 14 - 10,
            al_map_rgb(255, 255, 255), 5);

        al_draw_text(elem->title, al_map_rgb(255, 255, 255), SCREEN_W / 2, 0, ALLEGRO_ALIGN_CENTRE, "HALL OF FAME");

        al_draw_text(elem->highscoreNews, al_map_rgb(60, 50, 5), SCREEN_W / 4 + 20, 5 * SCREEN_H / 12 - 40,
            ALLEGRO_ALIGN_CENTER, "POSITION");
        al_draw_text(elem->highscoreNews, al_map_rgb(60, 50, 5), SCREEN_W / 2, 5 * SCREEN_H / 12 - 40,
            ALLEGRO_ALIGN_CENTER, "NAME");
        al_draw_text(elem->highscoreNews, al_map_rgb(60, 50, 5), 3 * SCREEN_W / 4, 5 * SCREEN_H / 12 - 40, 2, "SCORE");

        //muestro nombres
        int i;
        for (i = 0; i < NUMBER_OF_PLAYERS; i++)
        {
            char position[3] = { '#', i + 1 + '0', '\0' };
            al_draw_text(elem->highscoreNews, al_map_rgb(255, 255, 255), SCREEN_W / 4, 5 * SCREEN_H / 12 + 50 * i,
                0, position);

            al_draw_text(elem->highscoreNews, al_map_rgb(255, 255, 255), SCREEN_W / 2, 5 * SCREEN_H / 12 + 50 * i,
                ALLEGRO_ALIGN_CENTER, highscore->nameOfHighscores[i]);

            char score[10];
            snprintf(score, sizeof(score), "% d", highscore->highscores[i]);
            al_draw_text(elem->highscoreNews, al_map_rgb(255, 255, 255), 3 * SCREEN_W / 4, 5 * SCREEN_H / 12 + 50 * i,
                2, score);
        }
        drawButtons(buttons, al_color_name("white"));

        al_set_target_bitmap(elem->bitmapTrans);

        al_clear_to_color(al_map_rgba(0, 0, 0, trans));

        al_set_target_backbuffer(elem->display);
        al_draw_bitmap(elem->bitmapTrans, 0, 0, 0);

        al_flip_display();
    }

    // esperamos a alguna selecci�n
    bool waitingForUpdate = true;
    bool draw = true;
    int times = 0;

    while (waitingForUpdate)
    {

        al_get_next_event(elem->eventQueue, &ev); // pedimos el evento que venga

        // analizamos si se cerro la ventana
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *state = CLOSE_DISPLAY;
            waitingForUpdate = false;
        }

        // analizamos si se pulso algun boton
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && buttons[0]->press)
        {
            *state = GAME_SEL;
            al_play_sample(elem->effectPlay, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            al_rest(0.4);
            al_stop_samples();
            al_play_sample(elem->sampleMenu, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
            waitingForUpdate = false;
        }

        // vemos si se posicion� el mouse sobre un bot�n
        else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            int i;
            for (i = 0; buttons[i]; i++)
            {
                if (!buttons[i]->press && (ev.mouse.x <= buttons[i]->x_center + buttons[i]->width 
                    && ev.mouse.x >= buttons[i]->x_center - buttons[i]->width 
                    && ev.mouse.y <= buttons[i]->y_center + buttons[i]->height 
                    && ev.mouse.y >= buttons[i]->y_center - buttons[i]->height))
                {
                    if (!buttons[i]->press) // si el boton cambia de estado, dibujamos
                    {
                        draw = true;
                    }
                    al_play_sample(elem->effectCursor, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    buttons[i]->press = true; // actualizamos el estado del boton
                }

                else if (buttons[i]->press && (ev.mouse.x > buttons[i]->x_center + buttons[i]->width 
                        ||ev.mouse.x < buttons[i]->x_center - buttons[i]->width 
                        || ev.mouse.y > buttons[i]->y_center + buttons[i]->height 
                        || ev.mouse.y < buttons[i]->y_center - buttons[i]->height))
                {
                    if (buttons[i]->press) // si el boton cambia de estado, dibujamos
                    {
                        draw = true;
                    }
                    buttons[i]->press = false; // actualizamos el estado del boton
                }
            }
        }

        if (++times % 1000)
        {
            draw = true,
            times = 0;
        }

        // redibujamos si es necesario
        if (draw)
        {
            drawButtons(buttons, al_color_name("white"));
            al_flip_display(); // cargamos el buffer en el display
            draw = false;
        }
    }

    if (*state != CLOSE_DISPLAY)
    {
        int trans;
        for (trans = 0; trans < 255; trans += 2)
        {
            al_draw_bitmap(elem->highscoreBackround, 0, 0, 0);

            al_draw_filled_rectangle(SCREEN_W / 5, SCREEN_H / 3, 4 * SCREEN_W / 5, 11 * SCREEN_H / 14,
                al_map_rgb(120, 110, 40));
            al_draw_rectangle(SCREEN_W / 5 + 10, SCREEN_H / 3 + 10, 4 * SCREEN_W / 5 - 10, 11 * SCREEN_H / 14 - 10,
                al_map_rgb(255, 255, 255), 5);

            al_draw_text(elem->title, al_map_rgb(255, 255, 255), SCREEN_W / 2, 0, ALLEGRO_ALIGN_CENTRE, "HALL OF FAME");

            al_draw_text(elem->highscoreNews, al_map_rgb(60, 50, 5), SCREEN_W / 4 + 20, 5 * SCREEN_H / 12 - 40,
                ALLEGRO_ALIGN_CENTER, "POSITION");
            al_draw_text(elem->highscoreNews, al_map_rgb(60, 50, 5), SCREEN_W / 2, 5 * SCREEN_H / 12 - 40,
                ALLEGRO_ALIGN_CENTER, "NAME");
            al_draw_text(elem->highscoreNews, al_map_rgb(60, 50, 5), 3 * SCREEN_W / 4, 5 * SCREEN_H / 12 - 40, 2, "SCORE");

            //muestro nombres
            int i;
            for (i = 0; i < NUMBER_OF_PLAYERS; i++)
            {
                char position[3] = { '#', i + 1 + '0', '\0' };
                al_draw_text(elem->highscoreNews, al_map_rgb(255, 255, 255), SCREEN_W / 4, 5 * SCREEN_H / 12 + 50 * i,
                    0, position);

                al_draw_text(elem->highscoreNews, al_map_rgb(255, 255, 255), SCREEN_W / 2, 5 * SCREEN_H / 12 + 50 * i,
                    ALLEGRO_ALIGN_CENTER, highscore->nameOfHighscores[i]);

                char score[10];
                snprintf(score, sizeof(score), "% d", highscore->highscores[i]);
                al_draw_text(elem->highscoreNews, al_map_rgb(255, 255, 255), 3 * SCREEN_W / 4, 5 * SCREEN_H / 12 + 50 * i,
                    2, score);
            }
            drawButtons(buttons, al_color_name("white"));

            al_set_target_bitmap(elem->bitmapTrans);

            al_clear_to_color(al_map_rgba(0, 0, 0, trans));

            al_set_target_backbuffer(elem->display);
            al_draw_bitmap(elem->bitmapTrans, 0, 0, 0);

            al_flip_display();
        }
    }
}