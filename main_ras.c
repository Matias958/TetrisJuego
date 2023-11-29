/*HEADERS*/

/*BIBLIOTECAS STANDARD*/
#include <stdio.h>
#include <stdlib.h>

#include "rules.h"
#include "raspberry.h"
#include "disdrv.h"
#include "joydrv.h"
#include "game_state.h"
#include "highscore.h"

int main(void)
{
    char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]; // crea la matriz del juego

    init(); // muestra una pantalla de init en el display y espera al boton

    highscore_t highscore; // inicializo variables generales
    if (!get_highscore(&highscore))
    {
        return EXIT_FAILURE;
    }
    char i = '\0';
    bool play = true;
    int num_match = 0;

    while (play)
    {

        int score = 0; // inicializa variables partida
        bool tetris;
        char rows_tetris[18];
        bool match = true;
        num_match++;
        initTime();
        game_mode_t game_mode = {EASY, false, false, false};
        piece_t piece = createPiece();
        show_display(matrix);

        while (match)
        {
            char movement = joystick();
            match = jugarTetris(movement, &piece, matrix, &score, game_mode);
            show_display(matrix);
            score += deleteLine(matrix, rows_tetris, &tetris);

            // Agregar pausa
        }

        disp_clear(); // borra display
        disp_update();

        // en caso de ser necesario agrega el puntaje de la partida al highscore
        // y si es el puntaje más alto lo muestra en el display
        int new_highscore = is_highscore(score, &highscore);
        if (new_highscore)
        {
            if (!set_highscore(&highscore, score, "RAS" + num_match))
            {
                return EXIT_FAILURE;
            }
            if (new_highscore == 1)
            {
                print_highscore();
            }
        }

        // espera a que el jugador decida empezar una nueva partida o terminar el juego
        while (i != BUTTON)
        {
            i = joystick();
            if (i == DOWN)
            {
                play = false;
            }
        }
    }
    return EXIT_SUCCESS;
};