#include "game_sel_al.h"
#include "botones.h"

#define FRAMES 32
#define FPS 60

/*MODOS DE JUEGO A SELECCIONAR*/
enum game_modes {MIRRORED, BLANKING, NO_EMPTY, START};

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
    button_t  mirrored = { "MIRRORED",SCREEN_W / 4, SCREEN_H * 0.4, 100, 200, 30,
                    false, al_map_rgb(192,0,100), al_map_rgb(150,0,80),
                    elem->game_modes };

    button_t blanking = { "BLANKING" ,2 * SCREEN_W / 4, SCREEN_H * 0.4, 100, 200, 30,
                    false,al_map_rgb(192,0,100), al_map_rgb(150,0,80),
                    elem->game_modes };

    button_t no_empty = { "NO EMPTY" ,3 * SCREEN_W / 4, SCREEN_H * 0.4, 100, 200, 30,
                    false,al_map_rgb(192,0,100), al_map_rgb(150,0,80),
                    elem->game_modes };

    button_t start = { "START",SCREEN_W / 2, SCREEN_H * 0.8, 100, 40, 20,
                    false, al_map_rgb(100,110,200), al_map_rgb(100,0,200),
                    elem->buttons };


    button_t* botones[] = { &mirrored, &blanking, &no_empty,&start,NULL };

    ALLEGRO_BITMAP* pictures[] = { elem->mirrored, elem->blinking, elem->no_empty};
    ALLEGRO_BITMAP* pictures_prs[] = { elem->mirrored_prs, elem->blinking_prs, elem->no_empty_prs };

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

                    if (i == MIRRORED || i == BLANKING || i == NO_EMPTY)
                    {
                        botones[i]->color_prs = states[i] ? al_map_rgb(192, 0, 100) : al_map_rgb(200, 10, 240);
                    }

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
            botones[BLANKING]->color_uprs = game_mode->blanking ? al_map_rgb(120, 0, 60) : al_map_rgb(150, 0, 190);
            botones[MIRRORED]->color_uprs = game_mode->mirrored ? al_map_rgb(120, 0, 60) : al_map_rgb(150, 0, 190);
            botones[NO_EMPTY]->color_uprs = game_mode->no_empty ? al_map_rgb(120, 0, 60) : al_map_rgb(150, 0, 190);

            draw_buttons(botones, al_color_name("white"));

            int i;
            for (i = 0; i < 3; i++)
            {
                al_draw_bitmap(botones[i]->press? pictures_prs[i] : pictures[i], botones[i]->x_center - 46 , botones[i]->y_center - 60, ALLEGRO_ALIGN_CENTER);
            }


            al_flip_display(); //cargamos el buffer en el display
            draw = false; 
        }
    }
}

