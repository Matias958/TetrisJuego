/*HEADERS*/

/*ALLEGRO*/
#include "inicializacion_al.h"
#include "menu_al.h"
#include "game_sel_al.h"

/**/
/*BIBLIOTECAS STANDARD*/
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    ALLEGRO_EVENT ev;
    bool close_display;
    bool menu;
    bool game_sel;
    bool highscore;
    bool game;
}window_state_t;

int main(int argc, char * argv[])
{
    //ELEMENTOS DE ALLEGRO
    element_t elem = {NULL, NULL, NULL, NULL, NULL, NULL, NULL}; 
    window_state_t estado = {.close_display = false, true, false, false, false};
    game_mode_t modo;
    
    if(inicializa_al(&elem) == EXIT_FAILURE)
    {
        printf("ERROR: no se pudieron inicializar los elementos de Allegro\n");
        return EXIT_FAILURE; //si no pudo inicilizar correctamente, 
    }
    
    while(!estado.close_display)
    {
        if(estado.menu)
        {
            /*MENU*/
            menu_state_t estado_menu = p_menu(&elem);
            
            estado.close_display = estado_menu.window;
            estado.game_sel = estado_menu.play;
            estado.highscore = estado_menu.highscore;
            
            estado.menu = false;
        }
        
        else if(estado.game_sel)
        {
            modo = p_game_mode(&elem);
            
            estado.close_display = modo.window;
            estado.game = modo.start;
            
            estado.game_sel = false;
        }
        
        else if(estado.game)
        {
            play_game(&elem, modo);
        }
        
        if(al_get_next_event(elem.event_queue, &estado.ev))
        {
            switch(estado.ev.type)
                /*EVENTOS DE DISPLAY*/
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                {
                    estado.close_display = true;
                }
        }
    }
    return EXIT_SUCCESS;
}