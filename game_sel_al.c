#include "game_sel_al.h"
#include "botones.h"

#define LINES 4
#define NUMBER_OF_GAME_MODES 3

/*MODOS DE JUEGO A SELECCIONAR*/
enum game_modes {MIRRORED, BLANKING, NO_EMPTY, START, DIFFICULTY};

static const char* descriptions[][LINES] = { {"Swaps left and right", "buttons",""},
                                       {"The pieces on the", "game disapear" , "momentainusly from" , "the board"},
                                       {"The board is not", "empty at the", "beginning of the", "game"}};

/*P_GAME_MODE()
* Función encargada de crear y seleccionar el modo de juego elegido.
* Recibe: Estructura element_t; window_state_t y game_mode_t
* Devuelve: -
*/

void p_game_mode(element_t* elem, window_state_t* state, game_mode_t* game_mode)
{
    al_clear_to_color(al_map_rgb(20, 20, 20));
    al_draw_bitmap(elem->menu_backround, 0, 0, 0);
    
    //botones 
    button_t  mirrored = { "MIRRORED",SCREEN_W / 5, SCREEN_H * 0.4, 150, 200, 0,
                    false, al_map_rgb(20, 20, 20), al_map_rgb(0, 0, 0),
                    elem->game_modes };

    button_t blanking = { "BLINKING" ,SCREEN_W / 2, SCREEN_H * 0.4, 150, 200, 0,
                    false,al_map_rgb(20, 20, 20), al_map_rgb(0,0,0),
                    elem->game_modes };

    button_t no_empty = { "NOT EMPTY" ,4 * SCREEN_W / 5, SCREEN_H * 0.4, 150, 200, 0,
                    false,al_map_rgb(20, 20, 20), al_map_rgb(0,0,0),
                    elem->game_modes };

    button_t start = { "START",SCREEN_W / 2, SCREEN_H * 0.8, 100, 40, 20,
                    false, al_map_rgb(100,110,200), al_map_rgb(100,0,200),
                    elem->buttons };

    button_t difficulty = { "",SCREEN_W / 2, SCREEN_H * 0.925, 75, 30, 30,
                    false, al_map_rgb(0, 115, 190), al_map_rgb(0, 75, 205),
                    elem->buttons };


    button_t* botones[] = { &mirrored, &blanking, &no_empty, &start, &difficulty, NULL };

    ALLEGRO_BITMAP* pictures[] = { elem->mirrored, elem->blinking, elem->no_empty};
    ALLEGRO_BITMAP* pictures_prs[] = { elem->mirrored_prs, elem->blinking_prs, elem->no_empty_prs };
    ALLEGRO_BITMAP* pictures_logo[] = { elem->mirrored_logo, elem->blinking_logo, elem->no_empty_logo};

    bool states[] = { game_mode->mirrored, game_mode->blanking, game_mode->no_empty};

    draw_buttons(botones, al_color_name("white"));

    al_flip_display(); //cargamos el buffer en el display

    //esperamos a alguna selección
    ALLEGRO_EVENT ev;
    bool waitingForUpdate = true;
    bool draw = true;
    bool mouseClick = false;
    int veces = 0;

    while (waitingForUpdate)
    {

        al_get_next_event(elem->event_queue, &ev);//pedimos el evento que venga
        

        //analizamos si se cerró la ventana
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *state = CLOSE_DISPLAY;
            waitingForUpdate = false;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            mouseClick = false;
        }

        //analizamos si se pulso algún botón
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(botones[BLANKING]->press && !mouseClick)
            {
                game_mode->blanking = !game_mode->blanking; //se cambia el estado y el color cuando no esta pulsado
                states[BLANKING] = game_mode->blanking;
                al_play_sample(elem->effect_select, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                draw = true;
            }
            else if(botones[MIRRORED]->press && !mouseClick)
            {
                game_mode->mirrored = !game_mode->mirrored;
                states[MIRRORED] = game_mode->mirrored;
                al_play_sample(elem->effect_select, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                draw = true;
            }
            else if(botones[NO_EMPTY]->press && !mouseClick)
            {
                game_mode->no_empty = !game_mode->no_empty;
                states[NO_EMPTY] = game_mode->no_empty;
                al_play_sample(elem->effect_select, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                draw = true;
            }
            else if(botones[START]->press && !mouseClick)
            {
                *state = GAME;
                waitingForUpdate = false;
            }
            else if (botones[DIFFICULTY]->press && !mouseClick)
            {
                if (game_mode->difficulty < HARD)
                {
                    game_mode->difficulty++;
                }
                else
                {
                    game_mode->difficulty = EASY;
                }
                al_stop_sample(elem->effect_select);
                al_play_sample(elem->effect_select, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                draw = true;
            }
            mouseClick = true;

        }
        
        //vemos si se posicionó el mouse sobre un botón
        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            int i;
            for(i=0; botones[i]; i++)
            {   
                if (!botones[i]->press && (ev.mouse.x <= botones[i]->x_center + botones[i]->width
                    && ev.mouse.x >= botones[i]->x_center - botones[i]->width
                    && ev.mouse.y <= botones[i]->y_center + botones[i]->height
                    && ev.mouse.y >= botones[i]->y_center - botones[i]->height))
                {
                    if (!botones[i]->press) //si el botón cambia de estado, dibujamos
                    {
                        draw = true;
                    }
                    if (!mouseClick)
                    {
                        al_play_sample(elem->effect_cursor, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    botones[i]->press = true;// actualizamos el estado del botón
                }

                else if (botones[i]->press && (ev.mouse.x > botones[i]->x_center + botones[i]->width 
                   || ev.mouse.x < botones[i]->x_center - botones[i]->width
                   || ev.mouse.y > botones[i]->y_center + botones[i]->height
                   || ev.mouse.y < botones[i]->y_center - botones[i]->height))
                {
                    if(botones[i]->press)//si el botón cambia de estado, dibujamos
                    {
                        draw = true;
                    }
                    botones[i]->press = false;// actualizamos el estado del botón
                }

            }
        }

        if (++veces % 1000)
        {
            draw = true;
            veces = 0;
        }
                
        //redibujamos si es necesario
        if(draw)
        {
            int i;
            for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
            {
                botones[i]->color_uprs = states[i] ? al_map_rgb(215, 25, 70) : al_map_rgb(0, 0, 0);
                botones[i]->color_prs = states[i]? al_map_rgb(195, 45, 75) : al_map_rgb(20, 20, 20);
            }

            draw_buttons(botones, al_color_name("white"));

            for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
            {
                al_draw_bitmap(states[i]? pictures_prs[i] : pictures[i], botones[i]->x_center - botones[i]->width + 2, botones[i]->y_center - 98, ALLEGRO_ALIGN_CENTER);
                al_draw_rectangle(botones[i]->x_center - botones[i]->width, botones[i]->y_center + botones[i]->height,
                    botones[i]->x_center + botones[i]->width, botones[i]->y_center - botones[i]->height,
                    al_map_rgb(255, 255, 255), states[i] ? 6 : 4);

                if (botones[i]->press)
                {
                    al_set_target_bitmap(elem->modes_desc);

                    // Dibujar un rectángulo con transparencia
                    al_clear_to_color(al_map_rgba(10, 10, 10, 70));

                    al_set_target_backbuffer(elem->display);

                    al_draw_bitmap(elem->modes_desc, botones[i]->x_center - botones[i]->width + 2, botones[i]->y_center - 98, 0);
                    
                    int j;
                    for (j = 0; j < LINES; j++)
                    {
                        al_draw_text(elem->game_modes_description_border, al_map_rgb(10, 10, 10), botones[i]->x_center, botones[i]->y_center + j * 30, ALLEGRO_ALIGN_CENTER, descriptions[i][j]);
                        al_draw_text(elem->game_modes_description, al_map_rgb(255, 255, 255), botones[i]->x_center, botones[i]->y_center + j * 30, ALLEGRO_ALIGN_CENTER, descriptions[i][j]);
                    }

                }
            }

            for (i = 0; i < NUMBER_OF_GAME_MODES; i++)
            {
                al_set_target_bitmap(elem->border_logo);
                
                if (botones[i]->press)
                {
                    al_clear_to_color(states[i] ? al_map_rgb(210, 70, 100) : al_map_rgb(66, 67, 62));
                }
                else
                {
                    al_clear_to_color(states[i] ? al_map_rgb(210, 70, 100) : al_map_rgb(66, 67, 62));
                }
                al_draw_rectangle(0, 0, 75, 75, al_map_rgb(255, 255, 255), states[i]? 5 : 4);

                al_set_target_backbuffer(elem->display);

                al_draw_rotated_bitmap(elem->border_logo, al_get_bitmap_width(elem->border_logo) / 2.0, al_get_bitmap_height(elem->border_logo) / 2.0,
                                    botones[i]->x_center, botones[i]->y_center - botones[i]->height, ALLEGRO_PI / 4, 0);


                al_draw_bitmap(pictures_logo[i], botones[i]->x_center - 50, botones[i]->y_center - botones[i]->height - ((i == NO_EMPTY)? 50 : 42) , 0);
            }

            int numberOfStars = game_mode->difficulty;
            for (i = 0; i < 3; i++)
            {
                if (i < numberOfStars)
                {
                    al_draw_text(elem->difficulty_border, al_map_rgb(0, 0, 0), botones[DIFFICULTY]->x_center - 40 + i * 40, botones[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                    al_draw_text(elem->difficulty, al_map_rgb(200, 175, 0), botones[DIFFICULTY]->x_center - 40 + i * 40, botones[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                }
                else
                {
                    al_draw_text(elem->difficulty_border, al_map_rgb(0, 0, 0), botones[DIFFICULTY]->x_center - 40 + i * 40, botones[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                    al_draw_text(elem->difficulty, al_map_rgb(100, 100, 100), botones[DIFFICULTY]->x_center - 40 + i * 40, botones[DIFFICULTY]->y_center - 18, ALLEGRO_ALIGN_CENTER, "a");
                }
            }

            al_flip_display(); //cargamos el buffer en el display
            draw = false; 
        }
    }
}

