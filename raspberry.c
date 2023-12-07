/*headers*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "joydrv.h"
#include "disdrv.h"
#include "raspberry.h"
#include "rules.h"
#include "pieces.h"
#include "score_ras.h"

enum game_mode_options
{
    MIRRORED,
    BLINKING,
    NOT_EMPTY,
    DIFFICULTY
};
enum highscore_state
{
    NAME,
    SCORE
};

/* pause_ras()
 * Función que realiza el menu de pausa. Muestra "PAUSE" pos espera a que se mueva el joystick en
 * cualquier dirección. Luego te deja seguir jugando ("PLAY"), terminar la partida ("MENU") o
 * apagar la pantalla ("OFF").
 * Recibe: window_state_t *state
 * Devuelve: -
 */
static void pause_ras(window_state_t *state);

/*INICIO()
 * Función encargada de inicializar la pantalla con la palabra "tetris" pos esperar hasta
 * que se presione el botón del joystick para empezar el juego.
 * Recibe: puntero a estado de la ventana
 * Devuelve: -
 */
void init(window_state_t *state)
{
    disp_init(); // inicializo el display
    joy_init();  // inicializo el joystick

    disp_clear(); // apaga el display por completo (preventivo)
    disp_update();

    disp_write((dcoord_t){2, 2}, D_ON); // dibuje una pantalla que escribe tetris
    disp_write((dcoord_t){3, 2}, D_ON);
    disp_write((dcoord_t){4, 2}, D_ON);
    disp_write((dcoord_t){6, 2}, D_ON);
    disp_write((dcoord_t){7, 2}, D_ON);
    disp_write((dcoord_t){8, 2}, D_ON);
    disp_write((dcoord_t){10, 2}, D_ON);
    disp_write((dcoord_t){11, 2}, D_ON);
    disp_write((dcoord_t){12, 2}, D_ON);
    disp_write((dcoord_t){2, 3}, D_ON);
    disp_write((dcoord_t){3, 3}, D_ON);
    disp_write((dcoord_t){4, 3}, D_ON);
    disp_write((dcoord_t){6, 3}, D_ON);
    disp_write((dcoord_t){10, 3}, D_ON);
    disp_write((dcoord_t){11, 3}, D_ON);
    disp_write((dcoord_t){12, 3}, D_ON);
    disp_write((dcoord_t){3, 4}, D_ON);
    disp_write((dcoord_t){6, 4}, D_ON);
    disp_write((dcoord_t){7, 4}, D_ON);
    disp_write((dcoord_t){11, 4}, D_ON);
    disp_write((dcoord_t){3, 5}, D_ON);
    disp_write((dcoord_t){6, 5}, D_ON);
    disp_write((dcoord_t){11, 5}, D_ON);
    disp_write((dcoord_t){3, 6}, D_ON);
    disp_write((dcoord_t){6, 6}, D_ON);
    disp_write((dcoord_t){7, 6}, D_ON);
    disp_write((dcoord_t){8, 6}, D_ON);
    disp_write((dcoord_t){11, 6}, D_ON);
    disp_write((dcoord_t){7, 8}, D_ON);
    disp_write((dcoord_t){8, 8}, D_ON);
    disp_write((dcoord_t){2, 9}, D_ON);
    disp_write((dcoord_t){3, 9}, D_ON);
    disp_write((dcoord_t){4, 9}, D_ON);
    disp_write((dcoord_t){5, 9}, D_ON);
    disp_write((dcoord_t){7, 9}, D_ON);
    disp_write((dcoord_t){8, 9}, D_ON);
    disp_write((dcoord_t){10, 9}, D_ON);
    disp_write((dcoord_t){11, 9}, D_ON);
    disp_write((dcoord_t){12, 9}, D_ON);
    disp_write((dcoord_t){2, 10}, D_ON);
    disp_write((dcoord_t){5, 10}, D_ON);
    disp_write((dcoord_t){10, 10}, D_ON);
    disp_write((dcoord_t){2, 11}, D_ON);
    disp_write((dcoord_t){3, 11}, D_ON);
    disp_write((dcoord_t){4, 11}, D_ON);
    disp_write((dcoord_t){5, 11}, D_ON);
    disp_write((dcoord_t){7, 11}, D_ON);
    disp_write((dcoord_t){8, 11}, D_ON);
    disp_write((dcoord_t){10, 11}, D_ON);
    disp_write((dcoord_t){11, 11}, D_ON);
    disp_write((dcoord_t){12, 11}, D_ON);
    disp_write((dcoord_t){2, 12}, D_ON);
    disp_write((dcoord_t){4, 12}, D_ON);
    disp_write((dcoord_t){7, 12}, D_ON);
    disp_write((dcoord_t){8, 12}, D_ON);
    disp_write((dcoord_t){12, 12}, D_ON);
    disp_write((dcoord_t){2, 13}, D_ON);
    disp_write((dcoord_t){5, 13}, D_ON);
    disp_write((dcoord_t){7, 13}, D_ON);
    disp_write((dcoord_t){8, 13}, D_ON);
    disp_write((dcoord_t){10, 13}, D_ON);
    disp_write((dcoord_t){11, 13}, D_ON);
    disp_write((dcoord_t){12, 13}, D_ON);

    disp_update();

    char direction = WAIT; // espero a que toquen el boton para iniciar
    while (!joystick(&direction))
        ;
    while (!joystick(&direction))
        ;

    direction = WAIT;
    *state = GAME_SEL;
    disp_clear(); // apaga el display por completo
    print_letter('P', 0, 0);
    print_letter('L', 9, 0);
    print_letter('A', 0, 8);
    print_letter('Y', 9, 8);
    disp_update();

    while (direction != BUTTON)
    {
        while (!joystick(&direction))
            ;

        if (direction == DOWN || direction == UP)
        {
            if (*state == GAME_SEL)
            {
                *state = HIGHSCORE;
                disp_clear(); // apaga el display por completo
                print_letter('H', 0, 0);
                print_letter('S', 9, 0);
                disp_update();
            }
            else
            {
                disp_clear(); // apaga el display por completo
                print_letter('P', 0, 0);
                print_letter('L', 9, 0);
                print_letter('A', 0, 8);
                print_letter('Y', 9, 8);
                disp_update();
                *state = GAME_SEL;
            }
        }
    }

    disp_clear(); // apaga el display por completo
    disp_update();
    wait(3);
}

/*JOYSTICK()
 * Función encargada de analizar el estado del joystick.
 * Recibe: un puntero a char donde se va a guardar el estado del joystick.
 * Devuelve: Un bool que indica si logro recolectar algun estado valido (true) o no (false).
 */
bool joystick(char *direction)
{
    static char prevDirection = WAIT;

    joyinfo_t coordenates = joy_read();

    if (coordenates.sw == J_PRESS)
    {
        *direction = BUTTON;
        // printf("boton\n");
    }
    else if (((-100 <= coordenates.x) && (coordenates.x <= 100)) && ((100 <= coordenates.y) && (coordenates.y <= 127)))
    {
        *direction = UP;
        // printf("arriba\n");
    }
    else if (((-100 <= coordenates.x) && (coordenates.x <= 100)) && ((-128 <= coordenates.y) && (coordenates.y <= -100)))
    {
        *direction = DOWN;
        // printf("abajo\n");
    }
    else if (((-128 <= coordenates.x) && (coordenates.x <= -100)) && ((-100 <= coordenates.y) && (coordenates.y <= 100)))
    {
        *direction = LEFT_RAS;
        // printf("izquierda\n");
    }
    else if (((100 <= coordenates.x) && (coordenates.x <= 127)) && ((-100 <= coordenates.y) && (coordenates.y <= 100)))
    {
        *direction = RIGHT_RAS;
        // printf("derecha\n");
    }
    else
    {
        *direction = WAIT;
    }

    if (*direction == BUTTON)
    {
        wait(1);
        coordenates = joy_read();
        if (coordenates.sw == J_PRESS)
        {
            *direction = LONG_PRESS;
        }
    }

    if (prevDirection == *direction)
    {
        return false;
    }
    else
    {
        prevDirection = *direction;
        return true;
    }
}

/*SHOW_DISPLAY()
 * Función encargada de ir actualizando la pantalla.
 * Recibe: Una matriz con el tablero de juego.
 * Devuelve: -
 */
void showDisplay(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], int type)
{
    disp_clear(); // limpio el display

    dcoord_t position;

    for (uint8_t j = 0; j <= DISP_MAX_Y; j++)
    {
        for (uint8_t i = 0; i < (DISP_MAX_X - 3); i++)
        {
            position.x = i;
            position.y = j;

            if (i == 0 || i == 11)
            {
                disp_write(position, D_ON);
            }
            else if (matrix[j + 1][i] != EMPTY)
            {
                disp_write(position, D_ON);
            }
        }
    }

    switch (type)
    {
    case PIECE_I:
        disp_write((dcoord_t){14, 1}, D_ON);
        disp_write((dcoord_t){14, 2}, D_ON);
        disp_write((dcoord_t){14, 3}, D_ON);
        disp_write((dcoord_t){14, 4}, D_ON);
        break;
    case PIECE_J:
        disp_write((dcoord_t){14, 1}, D_ON);
        disp_write((dcoord_t){14, 2}, D_ON);
        disp_write((dcoord_t){14, 3}, D_ON);
        disp_write((dcoord_t){13, 3}, D_ON);
        break;
    case PIECE_L:
        disp_write((dcoord_t){13, 1}, D_ON);
        disp_write((dcoord_t){13, 2}, D_ON);
        disp_write((dcoord_t){14, 3}, D_ON);
        disp_write((dcoord_t){13, 3}, D_ON);
        break;
    case PIECE_O:
        disp_write((dcoord_t){13, 1}, D_ON);
        disp_write((dcoord_t){14, 1}, D_ON);
        disp_write((dcoord_t){13, 2}, D_ON);
        disp_write((dcoord_t){14, 2}, D_ON);
        break;
    case PIECE_S:
        disp_write((dcoord_t){14, 1}, D_ON);
        disp_write((dcoord_t){15, 1}, D_ON);
        disp_write((dcoord_t){13, 2}, D_ON);
        disp_write((dcoord_t){14, 2}, D_ON);
        break;
    case PIECE_T:
        disp_write((dcoord_t){14, 1}, D_ON);
        disp_write((dcoord_t){13, 2}, D_ON);
        disp_write((dcoord_t){14, 2}, D_ON);
        disp_write((dcoord_t){15, 2}, D_ON);
        break;
    case PIECE_Z:
        disp_write((dcoord_t){13, 1}, D_ON);
        disp_write((dcoord_t){14, 1}, D_ON);
        disp_write((dcoord_t){14, 2}, D_ON);
        disp_write((dcoord_t){15, 2}, D_ON);
        break;
    default:
        break;
    }
    disp_update();
    return;
}

void gameModeSel_ras(window_state_t *state, game_mode_t *gameMode)
{
    disp_clear();
    disp_update();

    print_letter('M', 0, 0);
    print_letter('D', 6, 0);
    print_letter('E', 12, 0);

    print_letter('S', 0, 8);
    print_letter('E', 6, 8);
    print_letter('L', 11, 8);

    disp_update();

    char direction = WAIT;
    while (!joystick(&direction))
        ;
    while (!joystick(&direction))
        ;

    bool *states[] = {&gameMode->mirrored, &gameMode->blinking, &gameMode->notEmpty};
    int i = MIRRORED;
    bool draw = true;

    while (*state != MENU && *state != GAME)
    {
        while (!joystick(&direction))
            ;

        if (direction == UP || direction == DOWN)
        {
            if (direction == UP)
            {
                if (i != MIRRORED)
                {
                    i--;
                }
                else
                {
                    i = DIFFICULTY;
                }
                draw = true;
            }
            else
            {
                if (i != DIFFICULTY)
                {
                    i++;
                }
                else
                {
                    i = MIRRORED;
                }
                draw = true;
            }
        }

        else if (direction == BUTTON)
        {
            switch (i)
            {
            case DIFFICULTY:
                if (gameMode->difficulty != HARD)
                {
                    gameMode->difficulty++;
                }
                else
                {
                    gameMode->difficulty = EASY;
                }
                draw = true;
                break;
            default:
                *states[i] = !*states[i];
                draw = true;
                break;
            }
        }

        else if (direction == LEFT_RAS)
        {
            *state = MENU;
        }

        else if (direction == RIGHT_RAS)
        {
            *state = GAME;
        }

        if (draw)
        {
            switch (i)
            {
            case MIRRORED:
                disp_clear();
                print_letter('M', 0, 0);
                print_letter('R', 6, 0);
                print_letter('R', 11, 0);

                print_letter(*states[i] ? 'X' : 'O', 6, 8);

                disp_update();
                break;
            case BLINKING:
                disp_clear();
                print_letter('B', 0, 0);
                print_letter('L', 6, 0);
                print_letter('K', 11, 0);

                print_letter(*states[i] ? 'X' : 'O', 6, 8);

                disp_update();
                break;

            case NOT_EMPTY:
                disp_clear();
                print_letter('N', 0, 0);
                print_letter('O', 6, 0);
                print_letter('E', 11, 0);

                print_letter(*states[i] ? 'X' : 'O', 6, 8);

                disp_update();
                break;

            case DIFFICULTY:
                disp_clear();
                print_letter('D', 0, 0);
                print_letter('I', 6, 0);
                print_letter('F', 11, 0);

                print_letter('X', 0, 8);
                print_letter(gameMode->difficulty >= MEDIUM ? 'X' : 'O', 6, 8);
                print_letter(gameMode->difficulty == HARD ? 'X' : 'O', 11, 8);

                disp_update();
                break;
            }
            draw = false;
        }
    }

    disp_clear();
    disp_update();
    wait(1);
}

int playGame_ras(game_mode_t mode, highscore_t *highscore, window_state_t *state)
{
    // inicializo la semilla pos el timer
    srand(time(NULL));

    char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD]; // creo la matriz del juego
    char blinkingMatrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD];
    char auxiliaryMatrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD];

    for (int i = 0; i < HEIGHT_OF_BOARD; i++) // llena de 0  el interior de la matriz pos define los bordes
    {
        for (int j = 0; j < WIDTH_OF_BOARD; j++)
        {
            if (i == 0 || i == 17 || j == 0 || j == 11)
            {
                matrix[i][j] = BORDER;
                blinkingMatrix[i][j] = BORDER;
            }
            else
            {
                matrix[i][j] = EMPTY;
                blinkingMatrix[i][j] = EMPTY;
            }
        }
    }

    if (mode.notEmpty) // llena con piezas el tablero si es necesario
    {
        createBoardforNotEmpty(matrix);
    }

    // inicializo el tiempo pos creo la primera pieza
    initTime();
    piece_t piece = createPiece();
    initPiece();

    bool match = false;
    bool draw = false;
    int score = 0;
    int times = 0;
    char movement = '\0';
    bool tetris = false;
    char rows_tetris[HEIGHT_OF_BOARD];

    while (!match)
    {
        if (joystick(&movement))
        {
            if (movement != LONG_PRESS)
            {
                match = playTetris(movement, &piece, matrix, &score, mode);
                draw = true;
            }
            else
            {
                pause_ras(state);
                if (*state != GAME)
                {
                    return score;
                }
            }
        }

        match = playTetris('\0', &piece, matrix, &score, mode); // se fija de ver si es necesario bajar en una la pieza

        if (times++ % 1000)
        {
            draw = true;
            times = 0;
        }

        if (draw)
        {
            for (int i = 0; i < HEIGHT_OF_BOARD; i++)
            {
                for (int j = 0; j < WIDTH_OF_BOARD; j++)
                {
                    auxiliaryMatrix[i][j] = matrix[i][j];
                }
            }

            parkPiece(&piece, auxiliaryMatrix); // estacionamos la pieza que se esta moviendo para visualizarla

            showDisplay(auxiliaryMatrix, getNextPiece());

            score += deleteLine(matrix, rows_tetris, &tetris);

            draw = false;
        }

        if (tetris)
        {
            tetrisAnimation(rows_tetris);
            showDisplay(auxiliaryMatrix, getNextPiece());
            tetris = false;
            draw = true;
        }
    }

    return score;
}

void wait(float time)
{
    long int initialNumberOfClocks = clock();
    long int currentNumberOfCloks = clock();

    while (time >= ((float)(currentNumberOfCloks - initialNumberOfClocks)) / CLOCKS_PER_SEC)
    {
        currentNumberOfCloks = clock();
    }
}

void tetrisAnimation(char rows_tetris[HEIGHT_OF_BOARD])
{
    int m;
    int veces;

    for (veces = 0; veces < 6; veces++)
    {
        for (m = 0; rows_tetris[m] != (char)END_OF_ARRAY; m++)
        {
            for (uint8_t n = 1; n < WIDTH_OF_BOARD - 1; n++)
            {
                disp_write((dcoord_t){n, (uint8_t)(rows_tetris[m] - 1)}, veces % 2 ? D_ON : D_OFF);
                // printf("%c\n", rows_tetris[m]);
            }
        }
        wait(0.3);
        disp_update();
    }
}

/*game_over()
 * Función encargada de imprimir una "END" en la pantalla pos esperar a que se presione el boton
 * (nueva partida) o se mueva hacia abajo el joystick (salir juego)
 * Recibe: -
 * Devuelve: un bool que indica si se inicia una nueva partida (true) o se sale del juego (false)
 */
void game_over(window_state_t *state)
{
    disp_clear();
    disp_update();

    print_letter('E', 0, 5);
    print_letter('N', 5, 5);
    print_letter('D', 11, 5);

    disp_update();

    wait(2);

    char direction = WAIT; // espero a que toquen el boton para volver a
    while (!joystick(&direction))
        ;
    while (!joystick(&direction))
        ;

    *state = MENU;
    disp_clear();
    print_letter('M', 0, 0);
    print_letter('E', 9, 0);
    print_letter('N', 0, 8);
    print_letter('U', 9, 8);

    disp_update();

    while (direction != BUTTON)
    {
        while (!joystick(&direction))
            ;

        if (direction == DOWN || direction == UP)
        {
            if (*state == MENU)
            {
                *state = CLOSE_DISPLAY;
                disp_clear();
                print_letter('O', 0, 5);
                print_letter('F', 6, 5);
                print_letter('F', 11, 5);
                disp_update();
            }
            else
            {
                *state = MENU;
                disp_clear();
                print_letter('M', 0, 0);
                print_letter('E', 9, 0);
                print_letter('N', 0, 8);
                print_letter('U', 9, 8);

                disp_update();
            }
        }
    }

    disp_clear(); // apaga el display por completo
    disp_update();
    wait(0.5);
}

/* pause_ras()
 * Función que realiza el menu de pausa. Muestra "PAUSE" pos espera a que se mueva el joystick en
 * cualquier dirección. Luego te deja seguir jugando ("PLAY"), terminar la partida ("MENU") o
 * apagar la pantalla ("OFF").
 * Recibe: window_state_t *state
 * Devuelve: -
 */
static void pause_ras(window_state_t *state)
{
    disp_clear();
    print_letter('P', 0, 0);
    print_letter('A', 5, 0);
    print_letter('U', 10, 0);
    print_letter('S', 0, 8);
    print_letter('E', 5, 8);
    disp_update();

    wait(1);
    char direction = WAIT; // espero a que toquen el boton para iniciar
    while (!joystick(&direction))
        ;
    while (!joystick(&direction))
        ;

    direction = WAIT;
    *state = GAME;
    disp_clear(); // apaga el display por completo
    print_letter('P', 0, 0);
    print_letter('L', 9, 0);
    print_letter('A', 0, 8);
    print_letter('Y', 9, 8);
    disp_update();

    while (direction != BUTTON)
    {
        while (!joystick(&direction))
            ;

        if (direction == DOWN || direction == UP)
        {
            if (*state == GAME)
            {
                *state = MENU;
                disp_clear(); // apaga el display por completo
                print_letter('M', 0, 0);
                print_letter('E', 9, 0);
                print_letter('N', 0, 8);
                print_letter('U', 9, 8);
                disp_update();
            }
            else if (*state == MENU)
            {
                *state = CLOSE_DISPLAY;
                disp_clear();
                print_letter('O', 0, 5);
                print_letter('F', 6, 5);
                print_letter('F', 11, 5);
                disp_update();
            }
            else
            {
                *state = GAME;
                disp_clear(); // apaga el display por completo
                print_letter('P', 0, 0);
                print_letter('L', 9, 0);
                print_letter('A', 0, 8);
                print_letter('Y', 9, 8);
                disp_update();
            }
        }
    }

    disp_clear(); // apaga el display por completo
    disp_update();
    wait(1);
}

void showHighScores(highscore_t *highscore, window_state_t *state)
{

    disp_clear();
    disp_update();

    // muestro nombres
    int i, pos = 0, winState = NAME;
    char direction;
    char buffer[4];
    bool draw = true;
    joystick(&direction);

    while (*state != GAME_SEL)
    {
        if (direction == DOWN)
        {
            pos++;
            pos %= NUMBER_OF_PLAYERS;
            draw = true;
        }
        else if (direction == UP)
        {
            pos--;
            if (pos < 0)
            {
                pos = NUMBER_OF_PLAYERS - 1;
            }
            draw = true;
        }

        else if(direction == RIGHT_RAS)
        {
            if(winState == NAME)
            {
                winState = SCORE;
                draw = true;
            }
        }

        else if(direction == LEFT_RAS)
        {
            if(winState == NAME)
            {
                *state = GAME_SEL;
            }
            else
            {
                winState = NAME;
                draw = true;
            }
        }

        if (draw)
        {
            if (winState == NAME)
            {
                disp_clear();
                print_num(pos + 1, 0, 0);
                for (i = 0; i < CHARACTERS; i++)
                {
                    print_letter(highscore->nameOfHighscores[pos][i], i * 5, 8);
                }
                disp_update();
            }
            else
            {
                disp_clear();
                snprintf(buffer, sizeof(buffer), "%d", highscore->highscores[pos]);
                for (i = 0; i < 2; i++)
                {
                    print_num(buffer[i] - '0', i * 8, 0);
                }

                for (i = 2; i < 4; i++)
                {
                    print_num(buffer[i] - '0', (i-2) * 8, 8);
                }
                disp_update();
            }

            draw = false;
        }
        while(!joystick(&direction));
    }

    disp_clear();
    disp_update();
    wait(1);
}

