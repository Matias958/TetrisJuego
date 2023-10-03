/*HEADERS*/
#include "menu_al.h"
#include "botones.h"

/*POSICÓN DEL TÍTULO EN LA PANTALLA*/
#define CENTER_X (SCREEN_W * 0.10)
#define CENTER_Y (SCREEN_H * 0.25)
#define STEP 120

/*MENU*/
enum menu_options {PLAY, HIGHSCORE};


menu_state_t p_menu(element_t * elem)
{
    //música
    al_play_sample(elem->sample_menu, 3.0, 1.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
    
    //brillo de fondo
    al_clear_to_color(al_map_rgb(20, 20, 20));
    
    //título 
    char *title[] = {"T", "E", "T", "R", "I", "S"};
    char *colors[] = {"red", "green", "orange", "violet", "blue", "yellow"};
    int step[]={180, 290, 400, 520, 640, 700};
          
    int i;
    for(i=0; i<6;i++)
    {
        al_draw_text(elem->title,al_color_name(colors[i]), CENTER_X+ step[i], CENTER_Y, 0, title[i]);
    }
    
    //botones 
    button_t play = {"JUGAR",SCREEN_W/2, SCREEN_H*0.65, 130, 40, 20,
                    false, al_map_rgb(100,110,200), al_map_rgb(100,0,200),
                    elem->buttons};
    
    button_t highscore = {"HIGHSCORE" ,SCREEN_W/2, SCREEN_H*0.80, 130, 40, 20,
                    false,al_map_rgb(100,110,200), al_map_rgb(100,0,200),
                    elem->buttons};
    
    button_t *botones[] = {&play, &highscore, NULL};
    
    draw_buttons(botones, al_color_name("white"));
    
    al_flip_display(); //cargamos el buffer en el display
    
    //esperamos a alguna selección
    ALLEGRO_EVENT ev;
    menu_state_t estado = {false, false, false};
    bool draw = false;
            
    while(!estado.window && !estado.play && !estado.highscore)
    {
        al_get_next_event(elem->event_queue, &ev);//pedimos el evento que venga
        
        //analizamos si se cerró la ventana
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            estado.window = true;
        }
        
        //vemos si se posicionó el mouse sobre un botón
        else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
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
        
        //analizamos si se pulso algún botón
        else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(ev.mouse.x <= botones[PLAY]->x_center + botones[PLAY]->width 
                && ev.mouse.x >= botones[PLAY]->x_center - botones[PLAY]->width
                && ev.mouse.y <= botones[PLAY]->y_center + botones[PLAY]->height
                && ev.mouse.y >= botones[PLAY]->y_center - botones[PLAY]->height)
            {
                estado.play = true;
            }
            
            else if(ev.mouse.x <= botones[HIGHSCORE]->x_center + botones[HIGHSCORE]->width 
                && ev.mouse.x >= botones[HIGHSCORE]->x_center - botones[HIGHSCORE]->width
                && ev.mouse.y <= botones[HIGHSCORE]->y_center + botones[HIGHSCORE]->height
                && ev.mouse.y >= botones[HIGHSCORE]->y_center - botones[HIGHSCORE]->height)
            {
                estado.highscore = true;
            } 
        }
        
        //redibujamos si es necesario
        if(draw)
        {
            draw_buttons(botones, al_color_name("white"));      
            al_flip_display(); //cargamos el buffer en el display
            draw = false; //cambiamos el estado de draw
        }
    }
    
    return estado;
}
