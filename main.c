/*HEADERS*/

#include <stdio.h>
#include <stdlib.h>

#include "inicializacion_al.h"
#include "menu_al.h"
#include "game_sel_al.h"
#include "highscore_al.h"
#include "game_state_al.h"
#include "highscore.h"




int main(void)
{
    //ELEMENTOS DE ALLEGRO
    element_t elem;

    //ESTADO DEL DISPLAY
    window_state_t estado = MENU;

    //MODOS DE JUEGO Y DIFICULTAD
    game_mode_t game_mode = {EASY, false, false, false};

    //HIGHSCORE
    highscore_t highscore;
    if (!get_highscore(&highscore))
    {
        return EXIT_FAILURE;
    }
    
    if(inicializa_al(&elem) == EXIT_FAILURE)
    {
        printf("ERROR: no se pudieron inicializar los elementos de Allegro\n");
        return EXIT_FAILURE; //si no pudo inicilizar correctamente, 
    }

    while(estado != CLOSE_DISPLAY)
    {
        switch (estado)
        {
        case MENU:
            p_menu(&elem, &estado);
            break;
        case GAME_SEL:
            p_game_mode(&elem, &estado, &game_mode);
            break;
        case GAME:
            play_game(&elem, game_mode, &estado, &highscore);
            break;
        case HIGHSCORE:
            p_highscore(&elem, &highscore, &estado);
            break;
        }
    }
    return EXIT_SUCCESS;
}
