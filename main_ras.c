/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
 *Titulo: main_ras.c
 *Descripcion: Función principal para jugar en la raspberry
 *Autores: Facundo Torres
 *         Julieta Libertad Rodriguez
 *         Matias Minitti
 *         Ramiro Nieto Abascal
 */

/*HEADERS*/
#include <stdio.h>
#include <stdlib.h>

#include "raspberry.h"
#include "game_state.h"
#include "highscore.h"
#include "score_ras.h"

int main(void)
{
    highscore_t highscore; // inicializo variables generales
    if (!getHighscore(&highscore))
    {
        return EXIT_FAILURE;
    }

    window_state_t state = MENU;
    game_mode_t game_mode = {EASY, false, false, false};
    int score;

    while (state != CLOSE_DISPLAY)
    {
        switch (state)
        {
        case MENU:
            init(&state); // muestra una pantalla de inicio en el display y espera al boton
            break;
        case GAME:
            score = playGame_ras(game_mode, &highscore, &state);
            if (state == GAME)
            {
                score_ras(score, &highscore);
                game_over(&state);
            }
            break;
        case HIGHSCORE:
            showHighScores(&highscore,&state);
            break;
        case GAME_SEL:
            gameModeSel_ras(&state, &game_mode);
            break;
        default:
            break;
        }
    }
        
    return EXIT_SUCCESS;
};
