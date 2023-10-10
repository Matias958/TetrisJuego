#include "game_sel_al.h"
#include "botones.h"

/*MODOS DE JUEGO A SELECCIONAR*/
enum game_modes {MIRRORED, BLANKING, NO_EMPTY, START};

void p_game_mode(element_t *elem, window_state_t *state, game_mode_t *game_mode)
{
    al_clear_to_color(al_map_rgb(20, 20, 20));
        
    //botones 
    button_t  mirrored = {"MIRRORED",SCREEN_W/4, SCREEN_H*0.4, 100, 200, 30,
                    false, al_map_rgb(100,110,200), al_map_rgb(201,193,181),
                    elem->game_modes};
    
    button_t blanking = {"BLANKING" ,2*SCREEN_W/4, SCREEN_H*0.4, 100, 200, 30,
                    false,al_map_rgb(100,110,200), al_map_rgb(201,193,181),
                    elem->game_modes};
    
    button_t no_empty = {"NO EMPTY" ,3*SCREEN_W/4, SCREEN_H*0.4, 100, 200, 30,
                    false,al_map_rgb(100,110,200), al_map_rgb(201,193,181),
                    elem->game_modes};
    
    button_t start = {"START",SCREEN_W/2, SCREEN_H*0.8, 100, 40, 20,
                    false, al_map_rgb(100,110,200), al_map_rgb(100,0,200),
                    elem->buttons};
    
    
    button_t *botones[] = {&mirrored, &blanking, &no_empty,&start,NULL};

    draw_buttons(botones, al_color_name("white"));
    
    al_flip_display(); //cargamos el buffer en el display
    
    //esperamos a alguna selección
    ALLEGRO_EVENT ev;
    bool waitingForUpdate = true;
    bool draw = false;
            
    while(waitingForUpdate)
    {
        al_get_next_event(elem->event_queue, &ev);//pedimos el evento que venga
        
        //analizamos si se cerró la ventana
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            *state = CLOSE_DISPLAY;
            waitingForUpdate = false;
        }

        //analizamos si se pulso algún botón
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            if(botones[BLANKING]->press)
            {
                game_mode->blanking = !game_mode->blanking; //se cambia el estado y el color cuando no esta pulsado
                botones[BLANKING]->color_uprs = game_mode->blanking? al_map_rgb(17,108,110) : al_map_rgb(201,193,181);
                draw = true;
            }
            else if(botones[MIRRORED]->press)
            {
                game_mode->mirrored = !game_mode->mirrored;
                botones[MIRRORED]->color_uprs = game_mode->mirrored? al_map_rgb(17,108,110) : al_map_rgb(201,193,181);
                draw = true;
            }
            else if(botones[NO_EMPTY]->press)
            {
                game_mode->no_empty = !game_mode->no_empty;
                botones[NO_EMPTY]->color_uprs = game_mode->no_empty? al_map_rgb(17,108,110) : al_map_rgb(201,193,181);
                draw = true;
            }
            else if(botones[START]->press)
            {
                *state = GAME;
                waitingForUpdate = false;
            }
        }
        
        //vemos si se posicionó el mouse sobre un botón
        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            int i;
            for(i=0; botones[i]; i++)
            {   
                if(!botones[i]->press && (ev.mouse.x <= botones[i]->x_center + botones[i]->width 
                   && ev.mouse.x >= botones[i]->x_center - botones[i]->width
                   && ev.mouse.y <= botones[i]->y_center + botones[i]->height
                   && ev.mouse.y >= botones[i]->y_center - botones[i]->height))
                {
                    if(!botones[i]->press) //si el botón cambia de estado, dibujamos
                    {
                        draw = true;
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
                
        //redibujamos si es necesario
        if(draw)
        {
            draw_buttons(botones, al_color_name("white"));      
            al_flip_display(); //cargamos el buffer en el display
            draw = false; 
        }
    }
}

