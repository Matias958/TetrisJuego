/*HEADERS*/

#include <stdio.h>
#include <stdlib.h>

#include "element_al.h"
#include "menu_al.h"
#include "game_sel_al.h"
#include "highscore_al.h"
#include "game_state.h"
#include "highscore.h"
#include "game_al.h"

int main(void)
{
    // ELEMENTOS DE ALLEGRO
    element_t elem;

    // ESTADO DEL DISPLAY
    window_state_t estado = MENU;

    // MODOS DE JUEGO Y DIFICULTAD
    game_mode_t game_mode = {EASY, false, false, false};

    // HIGHSCORE
    highscore_t highscore;
    if (!getHighscore(&highscore)) //cargo el highscore a la memoria
    {
        return EXIT_FAILURE;
    }

    if (initialize_al(&elem) == EXIT_FAILURE)
    {
        printf("ERROR: no se pudieron inicializar los elementos de Allegro\n");
        destructorOfElements(&elem);
        return EXIT_FAILURE; // si no pudo inicilizar correctamente,
    }

    while (estado != CLOSE_DISPLAY) //segun que boton se presiona, entra a un modo
    {
        switch (estado)
        {
        case MENU:
            showMenu(&elem, &estado);
            break;
        case GAME_SEL:
            showGameModeSel(&elem, &estado, &game_mode);
            break;
        case GAME:
            playGame(&elem, game_mode, &estado, &highscore);
            break;
        case HIGHSCORE:
            p_highscore(&elem, &highscore, &estado);
            break;
        }
    }

    destructorOfElements(&elem);
    return EXIT_SUCCESS;
}
