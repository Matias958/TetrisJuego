/*HEADERS*/
#include "menu_al.h"
#include "buttons_al.h"

/*POSICÓN DEL TÍTULO EN LA PANTALLA*/
#define CENTER_X (SCREEN_W * 0.10)
#define CENTER_Y (SCREEN_H * 0.25)
#define STEP 120

enum menuOptions
{
    PLAY,
    SCORE
}; // menu

/* SHOW_MENU
* Función encargada de mostrar e inicializar la pantalla del menu de inicio.
* Recibe: puntero a una estructura element_t y una window_state_t
* Devuelve: -
*/
void showMenu(element_t *elem, window_state_t *state)
{
    // música
    al_play_sample(elem->sampleMenu, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    // brillo de fondo
    al_clear_to_color(al_map_rgb(20, 20, 20));
    al_draw_bitmap(elem->menuBackround, 0, 0, 0);

    // título
    char *title[] = {"T", "E", "T", "R", "I", "S"};
    ALLEGRO_COLOR colors[] = {al_map_rgb(250, 50, 50),
                              al_map_rgb(0, 255, 127),
                              al_map_rgb(250, 150, 50),
                              al_map_rgb(255, 255, 0),
                              al_map_rgb(0, 200, 245),
                              al_map_rgb(200, 30, 200)};
    // ALLEGRO_COLOR *colors[] = {"red", "green", "orange", "violet", "blue", "yellow"};
    int step[] = {180, 290, 400, 520, 640, 700};

    int i;
    for (i = 0; i < 6; i++)
    {
        al_draw_text(elem->titleBorder, al_color_name("black"), CENTER_X + step[i], CENTER_Y, 0, title[i]);
        al_draw_text(elem->title, colors[i], CENTER_X + step[i], CENTER_Y, 0, title[i]);
    }

    // botones
    button_t play = {"PLAY", SCREEN_W / 2, SCREEN_H * 0.65, 130, 40, 20,
                     false, al_map_rgb(100, 110, 200), al_map_rgb(100, 0, 200),
                     elem->buttons};

    button_t highscore = {"HIGHSCORE", SCREEN_W / 2, SCREEN_H * 0.80, 130, 40, 20,
                          false, al_map_rgb(100, 110, 200), al_map_rgb(100, 0, 200),
                          elem->buttons};

    button_t *buttons[] = {&play, &highscore, NULL};

    drawButtons(buttons, al_color_name("white"));

    al_flip_display(); // cargamos el buffer en el display

    // esperamos a alguna selección
    ALLEGRO_EVENT ev;
    bool waitingForUpdate = true;
    bool draw = false;
    int times = 0;

    while (waitingForUpdate)
    {
        al_get_next_event(elem->eventQueue, &ev); // pedimos el evento que venga

        // analizamos si se cerró la ventana
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *state = CLOSE_DISPLAY;
            waitingForUpdate = false;
        }

        // vemos si se posicionó el mouse sobre un botón
        else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            for (i = 0; buttons[i]; i++)
            {
                if (!buttons[i]->press && (ev.mouse.x <= buttons[i]->x_center + buttons[i]->width && ev.mouse.x >= buttons[i]->x_center - buttons[i]->width && ev.mouse.y <= buttons[i]->y_center + buttons[i]->height && ev.mouse.y >= buttons[i]->y_center - buttons[i]->height))
                {
                    if (!buttons[i]->press) // si el botón cambia de estado, dibujamos
                    {
                        draw = true;
                    }
                    buttons[i]->press = true; // actualizamos el estado del botón
                    al_play_sample(elem->effectCursor, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                }

                else if (buttons[i]->press && (ev.mouse.x > buttons[i]->x_center + buttons[i]->width || ev.mouse.x < buttons[i]->x_center - buttons[i]->width || ev.mouse.y > buttons[i]->y_center + buttons[i]->height || ev.mouse.y < buttons[i]->y_center - buttons[i]->height))
                {
                    if (buttons[i]->press) // si el botón cambia de estado, dibujamos
                    {
                        draw = true;
                    }
                    buttons[i]->press = false; // actualizamos el estado del botón
                }
            }
        }

        // analizamos si se pulso algún botón
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (ev.mouse.x <= buttons[PLAY]->x_center + buttons[PLAY]->width && ev.mouse.x >= buttons[PLAY]->x_center - buttons[PLAY]->width && ev.mouse.y <= buttons[PLAY]->y_center + buttons[PLAY]->height && ev.mouse.y >= buttons[PLAY]->y_center - buttons[PLAY]->height)
            {
                *state = GAME_SEL;
                al_play_sample(elem->effectPlay, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                waitingForUpdate = false;
            }

            else if (ev.mouse.x <= buttons[SCORE]->x_center + buttons[SCORE]->width && ev.mouse.x >= buttons[SCORE]->x_center - buttons[SCORE]->width && ev.mouse.y <= buttons[SCORE]->y_center + buttons[SCORE]->height && ev.mouse.y >= buttons[SCORE]->y_center - buttons[SCORE]->height)
            {
                *state = HIGHSCORE;
                al_play_sample(elem->effectPlay, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                al_rest(0.4);
                waitingForUpdate = false;
            }
        }

        if (++times % 1000)
        {
            draw = true;
            times = 0;
        }

        // redibujamos si es necesario
        if (draw)
        {
            drawButtons(buttons, al_color_name("white"));
            al_flip_display(); // cargamos el buffer en el display
            draw = false;      // cambiamos el estado de draw
        }
    }
}
