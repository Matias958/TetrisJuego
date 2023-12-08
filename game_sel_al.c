/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: game_sel_al.h
*Descripcion: aspecto gráfico de la selección del
* modo de juego y la dificultad.
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

/************** HEADERS ***************/
#include "game_sel_al.h" 
#include "buttons_al.h"

/************** MACROS ***************/

#define LINES 4

/************** DEFINICIONES***************/

//posición de los botones en el arreglo
enum gameModes
{
    MIRRORED,
    BLINKING,
    NOT_EMPTY,
    START,
    DIFFICULTY
};

/************** VARIABLES GLOBALES***************/

//descripción del modo de juego
static const char *descriptions[][LINES] = {{"Swaps left and right", "buttons", "", ""},
                                            {"The pieces on the", "game disapear", "momentainusly from", "the board"},
                                            {"The board is not", "empty at the", "beginning of the", "game"}};

/*showGameModeSel()
 * Función de mostrar el aspecto gráfico de la selección del modo
 * de juego y la dificultad del mismo
 * Recibe: elem (elementos de Allegro), state (estructura que contiene
 * el estado de la ventana - game_state -: CLOSE_DISPLAY, MENU,
 * GAME_SEL, HIGHSCORE o GAME) y gameMode (estructura que almacena
 * la dificultad -EASY, MEDIUM o HARD- y los modos de juego activos).
 * Devuelve: -
 */
void showGameModeSel(element_t *elem, window_state_t *state, game_mode_t *gameMode)
{
    al_clear_to_color(al_map_rgb(20, 20, 20));
    al_draw_bitmap(elem->menuBackround, 0, 0, 0);

    // botones
    button_t mirrored = {"MIRRORED", SCREEN_W / 5, SCREEN_H * 0.4, 150, 200, 0,
                         false, al_map_rgb(20, 20, 20), al_map_rgb(0, 0, 0),
                         elem->gameModes};

    button_t blinking = {"BLINKING", SCREEN_W / 2, SCREEN_H * 0.4, 150, 200, 0,
                         false, al_map_rgb(20, 20, 20), al_map_rgb(0, 0, 0),
                         elem->gameModes};

    button_t notEmpty = {"NOT EMPTY", 4 * SCREEN_W / 5, SCREEN_H * 0.4, 150, 200, 0,
                         false, al_map_rgb(20, 20, 20), al_map_rgb(0, 0, 0),
                         elem->gameModes};

    button_t start = {"START", SCREEN_W / 2, SCREEN_H * 0.8, 100, 40, 20,
                      false, al_map_rgb(100, 110, 200), al_map_rgb(100, 0, 200),
                      elem->buttons};

    button_t difficulty = {"", SCREEN_W / 2, SCREEN_H * 0.925, 75, 30, 30,
                           false, al_map_rgb(0, 115, 190), al_map_rgb(0, 75, 205),
                           elem->buttons};

    button_t *buttons[] = {&mirrored, &blinking, &notEmpty, &start, &difficulty, NULL};

    ALLEGRO_BITMAP *pictures[] = {elem->mirrored, elem->blinking, elem->notEmpty};
    ALLEGRO_BITMAP *pictures_prs[] = {elem->mirroredPrs, elem->blinkingPrs, elem->notEmptyPrs};
    ALLEGRO_BITMAP *pictures_logo[] = {elem->mirroredLogo, elem->blinkingLogo, elem->notEmptyLogo};

    bool states[] = {gameMode->mirrored, gameMode->blinking, gameMode->notEmpty};

    drawButtons(buttons, al_color_name("white"));

    // esperamos a alguna selección
    ALLEGRO_EVENT ev;
    bool waitingForUpdate = true;
    bool draw = true;
    bool mouseClick = false;
    int times = 0;

    int trans;
    for (trans = 255; trans > 0; trans --)
    {
        al_get_next_event(elem->eventQueue, &ev);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *state = CLOSE_DISPLAY;
            return;
        }

        al_draw_bitmap(elem->menuBackround, 0, 0, 0);

        int i;
        for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
        {
            buttons[i]->color_uprs = states[i] ? al_map_rgb(215, 25, 70) : al_map_rgb(0, 0, 0);
            buttons[i]->color_prs = states[i] ? al_map_rgb(195, 45, 75) : al_map_rgb(20, 20, 20);
        }

        drawButtons(buttons, al_color_name("white"));

        for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
        {
            al_draw_bitmap(states[i] ? pictures_prs[i] : pictures[i], buttons[i]->x_center - buttons[i]->width + 2,
                buttons[i]->y_center - 98, ALLEGRO_ALIGN_CENTER);
            al_draw_rectangle(buttons[i]->x_center - buttons[i]->width, buttons[i]->y_center + buttons[i]->height,
                buttons[i]->x_center + buttons[i]->width, buttons[i]->y_center - buttons[i]->height,
                al_map_rgb(255, 255, 255), states[i] ? 6 : 4);

            if (buttons[i]->press)
            {
                al_set_target_bitmap(elem->modesDescription);

                // Dibujar un rectángulo con transparencia
                al_clear_to_color(al_map_rgba(10, 10, 10, 70));

                al_set_target_backbuffer(elem->display);

                al_draw_bitmap(elem->modesDescription, buttons[i]->x_center - buttons[i]->width + 2,
                    buttons[i]->y_center - 98, 0);

                int j;
                for (j = 0; j < LINES; j++)
                {
                    al_draw_text(elem->gameModesDescriptionBorder, al_map_rgb(10, 10, 10), buttons[i]->x_center,
                        buttons[i]->y_center + j * 30, ALLEGRO_ALIGN_CENTER, descriptions[i][j]);
                    al_draw_text(elem->gameModesDescription, al_map_rgb(255, 255, 255), buttons[i]->x_center,
                        buttons[i]->y_center + j * 30, ALLEGRO_ALIGN_CENTER, descriptions[i][j]);
                }
            }
        }

        for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
        {
            al_set_target_bitmap(elem->borderLogo);

            if (buttons[i]->press)
            {
                al_clear_to_color(states[i] ? al_map_rgb(210, 70, 100) : al_map_rgb(66, 67, 62));
            }
            else
            {
                al_clear_to_color(states[i] ? al_map_rgb(210, 70, 100) : al_map_rgb(66, 67, 62));
            }
            al_draw_rectangle(0, 0, 75, 75, al_map_rgb(255, 255, 255), states[i] ? 5 : 4);

            al_set_target_backbuffer(elem->display);

            al_draw_rotated_bitmap(elem->borderLogo, al_get_bitmap_width(elem->borderLogo) / 2.0,
                al_get_bitmap_height(elem->borderLogo) / 2.0, buttons[i]->x_center,
                buttons[i]->y_center - buttons[i]->height, ALLEGRO_PI / 4, 0);

            al_draw_bitmap(pictures_logo[i], buttons[i]->x_center - 50,
                buttons[i]->y_center - buttons[i]->height - ((i == NOT_EMPTY) ? 50 : 42), 0);
        }

        int numberOfStars = gameMode->difficulty;
        for (i = 0; i < 3; i++)
        {
            if (i < numberOfStars)
            {
                al_draw_text(elem->difficultyBorder, al_map_rgb(0, 0, 0), buttons[DIFFICULTY]->x_center - 40 + i * 40,
                    buttons[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                al_draw_text(elem->difficulty, al_map_rgb(200, 175, 0), buttons[DIFFICULTY]->x_center - 40 + i * 40,
                    buttons[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
            }
            else
            {
                al_draw_text(elem->difficultyBorder, al_map_rgb(0, 0, 0), buttons[DIFFICULTY]->x_center - 40 + i * 40,
                    buttons[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                al_draw_text(elem->difficulty, al_map_rgb(100, 100, 100), buttons[DIFFICULTY]->x_center - 40 + i * 40,
                    buttons[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
            }
        }

        al_set_target_bitmap(elem->bitmapTrans);

        al_clear_to_color(al_map_rgba(0, 0, 0, trans));

        al_set_target_backbuffer(elem->display);
        al_draw_bitmap(elem->bitmapTrans, 0, 0, 0);

        al_flip_display();
    }

    while (waitingForUpdate)
    {

        al_get_next_event(elem->eventQueue, &ev); // pedimos el evento que venga

        // analizamos si se cerró la ventana
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *state = CLOSE_DISPLAY;
            waitingForUpdate = false;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            mouseClick = false;
        }

        // analizamos si se pulso algún botón
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (buttons[BLINKING]->press && !mouseClick)
            {
                gameMode->blinking = !gameMode->blinking; // se cambia el estado y el color cuando no esta pulsado
                states[BLINKING] = gameMode->blinking;
                while(!al_play_sample(elem->effectSelect, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
                draw = true;
            }
            else if (buttons[MIRRORED]->press && !mouseClick)
            {
                gameMode->mirrored = !gameMode->mirrored;
                states[MIRRORED] = gameMode->mirrored;
                while(!al_play_sample(elem->effectSelect, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
                draw = true;
            }
            else if (buttons[NOT_EMPTY]->press && !mouseClick)
            {
                gameMode->notEmpty = !gameMode->notEmpty;
                states[NOT_EMPTY] = gameMode->notEmpty;
                while(!al_play_sample(elem->effectSelect, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
                draw = true;
            }
            else if (buttons[START]->press && !mouseClick)
            {
                *state = GAME;
                waitingForUpdate = false;
            }
            else if (buttons[DIFFICULTY]->press && !mouseClick)
            {
                if (gameMode->difficulty < HARD)
                {
                    gameMode->difficulty++;
                }
                else
                {
                    gameMode->difficulty = EASY;
                }
                while(!al_play_sample(elem->effectSelect, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
                draw = true;
            }
            mouseClick = true;
        }

        // vemos si se posicionó el mouse sobre un botón
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
                    if (!buttons[i]->press) // si el botón cambia de estado, dibujamos
                    {
                        draw = true;
                    }
                    if (!mouseClick)
                    {
                        while(!al_play_sample(elem->effectCursor, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL));
                    }
                    buttons[i]->press = true; // actualizamos el estado del botón
                }

                else if (buttons[i]->press && (ev.mouse.x > buttons[i]->x_center + buttons[i]->width 
                        || ev.mouse.x < buttons[i]->x_center - buttons[i]->width 
                        || ev.mouse.y > buttons[i]->y_center + buttons[i]->height 
                        || ev.mouse.y < buttons[i]->y_center - buttons[i]->height))
                {
                    if (buttons[i]->press) // si el botón cambia de estado, dibujamos
                    {
                        draw = true;
                    }
                    buttons[i]->press = false; // actualizamos el estado del botón
                }
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
            int i;
            for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
            {
                buttons[i]->color_uprs = states[i] ? al_map_rgb(215, 25, 70) : al_map_rgb(0, 0, 0);
                buttons[i]->color_prs = states[i] ? al_map_rgb(195, 45, 75) : al_map_rgb(20, 20, 20);
            }

            drawButtons(buttons, al_color_name("white"));

            for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
            {
                al_draw_bitmap(states[i] ? pictures_prs[i] : pictures[i], buttons[i]->x_center - buttons[i]->width + 2,
                               buttons[i]->y_center - 98, ALLEGRO_ALIGN_CENTER);
                al_draw_rectangle(buttons[i]->x_center - buttons[i]->width, buttons[i]->y_center + buttons[i]->height,
                                  buttons[i]->x_center + buttons[i]->width, buttons[i]->y_center - buttons[i]->height,
                                  al_map_rgb(255, 255, 255), states[i] ? 6 : 4);

                if (buttons[i]->press)
                {
                    al_set_target_bitmap(elem->modesDescription);

                    // Dibujar un rectángulo con transparencia
                    al_clear_to_color(al_map_rgba(10, 10, 10, 70));

                    al_set_target_backbuffer(elem->display);

                    al_draw_bitmap(elem->modesDescription, buttons[i]->x_center - buttons[i]->width + 2, 
                                   buttons[i]->y_center - 98, 0);

                    int j;
                    for (j = 0; j < LINES; j++)
                    {
                        al_draw_text(elem->gameModesDescriptionBorder, al_map_rgb(10, 10, 10), buttons[i]->x_center, 
                                     buttons[i]->y_center + j * 30, ALLEGRO_ALIGN_CENTER, descriptions[i][j]);
                        al_draw_text(elem->gameModesDescription, al_map_rgb(255, 255, 255), buttons[i]->x_center, 
                                     buttons[i]->y_center + j * 30, ALLEGRO_ALIGN_CENTER, descriptions[i][j]);
                    }
                }
            }

            for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
            {
                al_set_target_bitmap(elem->borderLogo);

                if (buttons[i]->press)
                {
                    al_clear_to_color(states[i] ? al_map_rgb(210, 70, 100) : al_map_rgb(66, 67, 62));
                }
                else
                {
                    al_clear_to_color(states[i] ? al_map_rgb(210, 70, 100) : al_map_rgb(66, 67, 62));
                }
                al_draw_rectangle(0, 0, 75, 75, al_map_rgb(255, 255, 255), states[i] ? 5 : 4);

                al_set_target_backbuffer(elem->display);

                al_draw_rotated_bitmap(elem->borderLogo, al_get_bitmap_width(elem->borderLogo) / 2.0, 
                                        al_get_bitmap_height(elem->borderLogo) / 2.0, buttons[i]->x_center, 
                                        buttons[i]->y_center - buttons[i]->height, ALLEGRO_PI / 4, 0);

                al_draw_bitmap(pictures_logo[i], buttons[i]->x_center - 50, 
                               buttons[i]->y_center - buttons[i]->height - ((i == NOT_EMPTY) ? 50 : 42), 0);
            }

            int numberOfStars = gameMode->difficulty;
            for (i = 0; i < 3; i++)
            {
                if (i < numberOfStars)
                {
                    al_draw_text(elem->difficultyBorder, al_map_rgb(0, 0, 0), buttons[DIFFICULTY]->x_center - 40 + i * 40,
                                buttons[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                    al_draw_text(elem->difficulty, al_map_rgb(200, 175, 0), buttons[DIFFICULTY]->x_center - 40 + i * 40,
                                buttons[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                }
                else
                {
                    al_draw_text(elem->difficultyBorder, al_map_rgb(0, 0, 0), buttons[DIFFICULTY]->x_center - 40 + i * 40, 
                                buttons[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                    al_draw_text(elem->difficulty, al_map_rgb(100, 100, 100), buttons[DIFFICULTY]->x_center - 40 + i * 40, 
                                buttons[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                }
            }

            al_flip_display(); // cargamos el buffer en el display
            draw = false;
        }
    }

    if (*state != CLOSE_DISPLAY)
    {
        int trans;
        for (trans = 0; trans < 255; trans += 2)
        {
            al_get_next_event(elem->eventQueue, &ev);
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                *state = CLOSE_DISPLAY;
                return;
            }

            al_draw_bitmap(elem->menuBackround, 0, 0, 0);

            int i;
            for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
            {
                buttons[i]->color_uprs = states[i] ? al_map_rgb(215, 25, 70) : al_map_rgb(0, 0, 0);
                buttons[i]->color_prs = states[i] ? al_map_rgb(195, 45, 75) : al_map_rgb(20, 20, 20);
            }

            drawButtons(buttons, al_color_name("white"));

            for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
            {
                al_draw_bitmap(states[i] ? pictures_prs[i] : pictures[i], buttons[i]->x_center - buttons[i]->width + 2,
                    buttons[i]->y_center - 98, ALLEGRO_ALIGN_CENTER);
                al_draw_rectangle(buttons[i]->x_center - buttons[i]->width, buttons[i]->y_center + buttons[i]->height,
                    buttons[i]->x_center + buttons[i]->width, buttons[i]->y_center - buttons[i]->height,
                    al_map_rgb(255, 255, 255), states[i] ? 6 : 4);

                if (buttons[i]->press)
                {
                    al_set_target_bitmap(elem->modesDescription);

                    // Dibujar un rectángulo con transparencia
                    al_clear_to_color(al_map_rgba(10, 10, 10, 70));

                    al_set_target_backbuffer(elem->display);

                    al_draw_bitmap(elem->modesDescription, buttons[i]->x_center - buttons[i]->width + 2,
                        buttons[i]->y_center - 98, 0);

                    int j;
                    for (j = 0; j < LINES; j++)
                    {
                        al_draw_text(elem->gameModesDescriptionBorder, al_map_rgb(10, 10, 10), buttons[i]->x_center,
                            buttons[i]->y_center + j * 30, ALLEGRO_ALIGN_CENTER, descriptions[i][j]);
                        al_draw_text(elem->gameModesDescription, al_map_rgb(255, 255, 255), buttons[i]->x_center,
                            buttons[i]->y_center + j * 30, ALLEGRO_ALIGN_CENTER, descriptions[i][j]);
                    }
                }
            }

            for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
            {
                al_set_target_bitmap(elem->borderLogo);

                if (buttons[i]->press)
                {
                    al_clear_to_color(states[i] ? al_map_rgb(210, 70, 100) : al_map_rgb(66, 67, 62));
                }
                else
                {
                    al_clear_to_color(states[i] ? al_map_rgb(210, 70, 100) : al_map_rgb(66, 67, 62));
                }
                al_draw_rectangle(0, 0, 75, 75, al_map_rgb(255, 255, 255), states[i] ? 5 : 4);

                al_set_target_backbuffer(elem->display);

                al_draw_rotated_bitmap(elem->borderLogo, al_get_bitmap_width(elem->borderLogo) / 2.0,
                    al_get_bitmap_height(elem->borderLogo) / 2.0, buttons[i]->x_center,
                    buttons[i]->y_center - buttons[i]->height, ALLEGRO_PI / 4, 0);

                al_draw_bitmap(pictures_logo[i], buttons[i]->x_center - 50,
                    buttons[i]->y_center - buttons[i]->height - ((i == NOT_EMPTY) ? 50 : 42), 0);
            }

            int numberOfStars = gameMode->difficulty;
            for (i = 0; i < 3; i++)
            {
                if (i < numberOfStars)
                {
                    al_draw_text(elem->difficultyBorder, al_map_rgb(0, 0, 0), buttons[DIFFICULTY]->x_center - 40 + i * 40,
                        buttons[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                    al_draw_text(elem->difficulty, al_map_rgb(200, 175, 0), buttons[DIFFICULTY]->x_center - 40 + i * 40,
                        buttons[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                }
                else
                {
                    al_draw_text(elem->difficultyBorder, al_map_rgb(0, 0, 0), buttons[DIFFICULTY]->x_center - 40 + i * 40,
                        buttons[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                    al_draw_text(elem->difficulty, al_map_rgb(100, 100, 100), buttons[DIFFICULTY]->x_center - 40 + i * 40,
                        buttons[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                }
            }

            al_set_target_bitmap(elem->bitmapTrans);

            al_clear_to_color(al_map_rgba(0, 0, 0, trans));

            al_set_target_backbuffer(elem->display);
            al_draw_bitmap(elem->bitmapTrans, 0, 0, 0);

            al_flip_display();
        }
    }
}
