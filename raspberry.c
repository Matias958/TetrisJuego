/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: raspberry.c
*Descripcion: manejo funciones para la Raspberry 
*             (manejo joystick, display y distintos menus/pantallas)
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

/*HEADERS*/
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

#include "audio_ras.h"
#include "audio.h"
#include <pthread.h>


/*MACROS*/
enum game_mode_options
{
    MIRRORED,
    BLINKING,
    NOT_EMPTY,
    DIFFICULTY
};


/*PROTOTIPOS*/

/* pauseRas()
 * Función que realiza el menu de pausa. Muestra "PAUSE" y espera a que se mueva el joystick en
 * cualquier dirección. Luego te deja seguir jugando ("PLAY"), terminar la partida ("MENU") o
 * apagar la pantalla ("TRN OFF").
 * Recibe: window_state_t *state, puntero al estado de la ventana
 * Devuelve: -
 * 
 * Nota: Para cambiar opción mover hacia arriba ó abajo, para seleccionar usar el botón.
 */
static void pauseRas(window_state_t *state);


/*CÓDIGO*/

/* init()
 * Función encargada de inicializar la pantalla con la palabra "TETRIS" y esperar hasta
 * que se mueva el joystick en cualquier dirección. Luego te deja elegir entre empezar a 
 * jugar ("PLAY"), ver el highscore ("HS") o apagar la pantalla ("TRN OFF").
 * Recibe: window_state_t *state, puntero al estado de la ventana
 * Devuelve: -
 * 
 * Nota: Para cambiar opción mover hacia arriba ó abajo, para seleccionar usar el botón.
 */
void init(window_state_t *state)
{
    disp_init(); // inicializo el display
    joy_init();  // inicializo el joystick
    
    disp_clear(); // apaga el display por completo (preventivo)
    disp_update();

    initAudio();
    pthread_t musicTh1;
    pthread_create(&musicTh1,NULL,musicThread_menu,NULL);
    pthread_join(musicTh1,NULL);
    Audio*soundPlay=NULL;
    soundPlay = createAudio(PLAY_M, 0, SDL_MIX_MAXVOLUME);
    Audio*soundSelect=NULL;
    soundSelect = createAudio(SELECT_M, 0, SDL_MIX_MAXVOLUME);
    Audio*soundCursor=NULL;
    soundCursor = createAudio(CURSOR_M, 0, SDL_MIX_MAXVOLUME);

    disp_write((dcoord_t){2, 2}, D_ON); // dibuja una pantalla que escribe "TETRIS"
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

    playSoundFromMemory(soundPlay, SDL_MIX_MAXVOLUME);

    direction = WAIT;
    *state = GAME_SEL;
    disp_clear(); // apaga el display por completo

    printCharacter('P', 0, 0); //muestra opción de iniciar una partida
    printCharacter('L', 9, 0);
    printCharacter('A', 0, 8);
    printCharacter('Y', 9, 8);
    disp_update();

    while (direction != BUTTON) //espera a que se seleccione una opción con el botón
    {
        while (!joystick(&direction))
            ;
        
        if (direction == DOWN || direction == UP) // pasa por las diferentes opciones del menú
        {
            playSoundFromMemory(soundCursor, SDL_MIX_MAXVOLUME);
            if (*state == GAME_SEL)
            {
                *state = HIGHSCORE; // opción ver highscore
                disp_clear(); 
                printCharacter('H', 0, 0);
                printCharacter('S', 9, 0);
                disp_update();
            }
            else if (*state == HIGHSCORE)
            {
                *state = CLOSE_DISPLAY; // opción salir del juego
                disp_clear(); 
                printCharacter('T', 0, 0);
                printCharacter('R', 6, 0);
                printCharacter('N', 11, 0);
                printCharacter('O', 0, 8);
                printCharacter('F', 6, 8);
                printCharacter('F', 11, 8);
                disp_update();
            }
            
            else
            {
                *state = GAME_SEL; // opción de iniciar una partida
                disp_clear(); 
                printCharacter('P', 0, 0);
                printCharacter('L', 9, 0);
                printCharacter('A', 0, 8);
                printCharacter('Y', 9, 8);
                disp_update();
            }
        }
        
    }

    playSoundFromMemory(soundSelect, SDL_MIX_MAXVOLUME);
    SDL_Delay(500);
    
    disp_clear(); 
    disp_update();
    endAudio();
    freeAudio(soundPlay);
    freeAudio(soundCursor);
    freeAudio(soundSelect);

    wait(2); // espera 2 segundos
}

/* joystick()
 * Función encargada de analizar el estado del joystick.
 * Recibe: un puntero a char donde se va a guardar el estado del joystick.
 * Devuelve: Un bool que indica si logro recolectar algun estado valido (true) o no (false).
 * 
 * Nota: estados posibles: apuntar hacia arriba, abajo, derecha, izquierda, presionar el botón
 * mantener presionado el botón.
 */
bool joystick(char *direction)
{
    static char prevDirection = WAIT;

    joyinfo_t coordenates = joy_read();

    if (coordenates.sw == J_PRESS)
    {
        *direction = BUTTON;
        
    }
    else if (((-100 <= coordenates.x) && (coordenates.x <= 100)) && ((100 <= coordenates.y) && (coordenates.y <= 127)))
    {
        *direction = UP;
        
    }
    else if (((-100 <= coordenates.x) && (coordenates.x <= 100)) && ((-128 <= coordenates.y) && (coordenates.y <= -100)))
    {
        *direction = DOWN;
        
    }
    else if (((-128 <= coordenates.x) && (coordenates.x <= -100)) && ((-100 <= coordenates.y) && (coordenates.y <= 100)))
    {
        *direction = LEFT_RAS;
        
    }
    else if (((100 <= coordenates.x) && (coordenates.x <= 127)) && ((-100 <= coordenates.y) && (coordenates.y <= 100)))
    {
        *direction = RIGHT_RAS;
        
    }
    else
    {
        *direction = WAIT;
    }

    if (*direction == BUTTON) // si el botón estaba pulsado, se fija que siga estando pulsado luego de 1 seg
    {
        wait(1);
        coordenates = joy_read();
        if (coordenates.sw == J_PRESS)
        {
            *direction = LONG_PRESS;
        }
    }

    if (prevDirection == *direction) // analiza si se hizo un movimiento del joystick valido o no
    {
        return false;
    }
    else
    {
        prevDirection = *direction;
        return true;
    }
}

/* showDisplay()
 * Función encargada de ir actualizando la pantalla durante el juego.
 * Recibe: Una matriz con el tablero de juego y un int con el tipo de pieza siguiente.
 * Devuelve: -
 */
void showDisplay(char matrix[HEIGHT_OF_BOARD][WIDTH_OF_BOARD], int type)
{
    disp_clear(); // limpio el display

    dcoord_t position;

    for (uint8_t j = 0; j <= DISP_MAX_Y; j++) //dibuja el tablero con los bordes
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

    switch (type) //dibuja la siguiente pieza
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

/* gameModeSelRas()
 * Función encargada de seleccionar el modo de juego, inicializa la pantalla con la palabra "MDE
 * SEL" y espera hasta que se mueva el joystick en cualquier dirección. Luego te deja elegir los
 * diferentes modos de juego.
 * Recibe: Un puntero a window_state_t con el estado de la ventana y uno a game_mode_t con el modo
 * de juego de la partida.
 * Devuelve: -
 * 
 * Nota: Permite elegir dificultad del 1-3 ("DIF"), modo Not Empty ("NOE"), Blinking ("BLK")
 * y Mirrored ("MRR").
 * 
 * Nota: Para cambiar opción mover hacia arriba ó abajo, para seleccionar usar el botón 
 * ("X": seleccionado, "O":no seleccionado). Para empezar la partida  mover el joystick hacia
 * la derecha y para volver al menú hacia la izquierda.
 */
void gameModeSelRas(window_state_t *state, game_mode_t *gameMode)
{
    disp_clear();
    disp_update();
    
    initAudio();
    pthread_t musicTh1;
    pthread_create(&musicTh1,NULL,musicThread_menu,NULL);
    pthread_join(musicTh1,NULL);
    Audio*soundPlay=NULL;
    soundPlay = createAudio(PLAY_M, 0, SDL_MIX_MAXVOLUME);
    Audio*soundSelect=NULL;
    soundSelect = createAudio(SELECT_M, 0, SDL_MIX_MAXVOLUME);
    Audio*soundCursor=NULL;
    soundCursor = createAudio(CURSOR_M, 0, SDL_MIX_MAXVOLUME);

    printCharacter('M', 0, 0); //pone pantalla inicial
    printCharacter('D', 6, 0);
    printCharacter('E', 12, 0);

    printCharacter('S', 0, 8);
    printCharacter('E', 6, 8);
    printCharacter('L', 11, 8);

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

        if (direction == UP || direction == DOWN) //modifica modo de juego a seleccionar
        {
            playSoundFromMemory(soundCursor, SDL_MIX_MAXVOLUME);
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

        else if (direction == BUTTON) // va modificando que modos de juego estan activos
        {
             playSoundFromMemory(soundSelect, SDL_MIX_MAXVOLUME);
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

        else if (direction == LEFT_RAS) //vuelve al menú si se mueve a la izq
        {
            *state = MENU;
        }

        else if (direction == RIGHT_RAS) //inicia partida si se mueve a la der
        {
            *state = GAME;
            playSoundFromMemory(soundPlay, SDL_MIX_MAXVOLUME);
            SDL_Delay(500);

        }

        if (draw) //va actualizando pantalla
        {
            switch (i)
            {
            case MIRRORED:
                disp_clear();
                printCharacter('M', 0, 0);
                printCharacter('R', 6, 0);
                printCharacter('R', 11, 0);

                printCharacter(*states[i] ? 'X' : 'O', 6, 8);

                disp_update();
                break;
            case BLINKING:
                disp_clear();
                printCharacter('B', 0, 0);
                printCharacter('L', 6, 0);
                printCharacter('K', 11, 0);

                printCharacter(*states[i] ? 'X' : 'O', 6, 8);

                disp_update();
                break;

            case NOT_EMPTY:
                disp_clear();
                printCharacter('N', 0, 0);
                printCharacter('O', 6, 0);
                printCharacter('E', 12, 0);

                printCharacter(*states[i] ? 'X' : 'O', 6, 8);

                disp_update();
                break;

            case DIFFICULTY:
                disp_clear();
                printCharacter('D', 0, 0);
                printCharacter('I', 6, 0);
                printCharacter('F', 11, 0);

                printCharacter('X', 0, 8);
                printCharacter(gameMode->difficulty >= MEDIUM ? 'X' : 'O', 6, 8);
                printCharacter(gameMode->difficulty == HARD ? 'X' : 'O', 11, 8);

                disp_update();
                break;
            }
            draw = false;
        }
    }

    disp_clear();
    disp_update();
    endAudio();
    freeAudio(soundPlay);
    freeAudio(soundCursor);
    freeAudio(soundSelect);
    wait(1);
}

/* playGameRas()
 * Función encargada de manejar el juego, muestra tablero de juego actual y siguiente pieza y 
 * permite realizar movimientos o ir al menu de pausa.
 * Recibe: Una estuctura game_mode_t con el modo de juego seleccionado, un puntero a highscore_t
 * con el highscore actual y un puntero a window_state_t con el estado de la ventana.
 * Devuelve: un int con el puntaje de la partida.
 * 
 * Nota: Las direcciones abajo, derecha, izquierda del joystick permiten mover la pieza en dichas
 * direcciones (invirtiendo der-izq si se encuentra en modo "Mirrored"), arriba te permite girar
 * la pieza 90°, el botón  permite hacer un "hard drop" de la pieza y mantener pulsado el botón
 * lleva al menú de pausa.
 * 
 */
int playGameRas(game_mode_t mode, highscore_t *highscore, window_state_t *state)
{
    initAudio();
    pthread_t musicTh;
    pthread_create(&musicTh,NULL,musicThread_game,NULL);
    pthread_join(musicTh,NULL);
    Audio*soundRotate=NULL;
    soundRotate = createAudio(ROTATE_M, 0, SDL_MIX_MAXVOLUME);
    Audio*soundLand=NULL;
    soundLand = createAudio(SE_GAME_LANDING_M, 0, SDL_MIX_MAXVOLUME);
    Audio*soundPause=NULL;
    soundPause = createAudio(SE_GAME_PAUSE_M, 0, SDL_MIX_MAXVOLUME);
    Audio*soundMove=NULL;
    soundMove = createAudio(SE_GAME_MOVE_M, 0, SDL_MIX_MAXVOLUME);
    Audio*soundGameOver=NULL;
    soundGameOver = createAudio(ME_GAMEOVER_M, 0, SDL_MIX_MAXVOLUME);
    Audio*soundTetris=NULL;
    soundTetris = createAudio(TETRIS_M, 0, SDL_MIX_MAXVOLUME);


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
            if (movement != LONG_PRESS) //si no hizo pausa juega con el movimiento elegido
            {
                match = playTetris(movement, &piece, matrix, &score, mode);
                draw = true;
                if(movement == BUTTON)
                {
                    playSoundFromMemory(soundLand, SDL_MIX_MAXVOLUME);
                }
                else if(movement == UP)
                {
                    playSoundFromMemory(soundRotate, SDL_MIX_MAXVOLUME);
    
                }
                else
                {
                    playSoundFromMemory(soundMove, SDL_MIX_MAXVOLUME);
                }
            }
            else
            {   
                playSoundFromMemory(soundPause, SDL_MIX_MAXVOLUME);
                SDL_Delay(2000);
                pauseRas(state);
                if (*state != GAME)
                {
                    endAudio();
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

        if (tetris) //si elimino una ó más lineas hace la animación correspondiente y actualiza el display
        {
            playSoundFromMemory(soundTetris, SDL_MIX_MAXVOLUME);
            tetrisAnimation(rows_tetris);
            showDisplay(auxiliaryMatrix, getNextPiece());
            tetris = false;
            draw = true;
        }
    }

    disp_clear();
    disp_update();
    playSoundFromMemory(soundGameOver, SDL_MIX_MAXVOLUME);
    SDL_Delay(2000);

    endAudio();
    freeAudio(soundLand);
    freeAudio(soundRotate);
    freeAudio(soundPause);
    freeAudio(soundGameOver);
    freeAudio(soundMove);
    freeAudio(soundTetris);
    return score;
}

/* wait()
 * Función encargada de esperar un determinado tiempo.
 * Recibe: Un float con el tiempo en segundos a esperar.
 * Devuelve: -
 * 
 */
void wait(float time)
{
    long int initialNumberOfClocks = clock();
    long int currentNumberOfCloks = clock();

    while (time >= ((float)(currentNumberOfCloks - initialNumberOfClocks)) / CLOCKS_PER_SEC)
    {
        currentNumberOfCloks = clock();
    }
}

/* tetrisAnimation()
 * Función encargada de hacer una animación cuando se elimina una o más filas (hace parpadear esas
 * filas antes de que se borren).
 * Recibe: Un arreglo de char con las filas que se borraron
 * Devuelve: -
 * 
 */
void tetrisAnimation(char rows_tetris[HEIGHT_OF_BOARD])
{
    
    int m;
    int veces;

    for (veces = 0; veces < 6; veces++) //cant de veces que parpadea
    {
        for (m = 0; rows_tetris[m] != (char)END_OF_ARRAY; m++)
        {
            for (uint8_t n = 1; n < WIDTH_OF_BOARD - 1; n++)
            {
                disp_write((dcoord_t){n, (uint8_t)(rows_tetris[m] - 1)}, veces % 2 ? D_ON : D_OFF);
            }
        }
        wait(0.3);
        disp_update();
    }
}

/*gameOver()
 * Función encargada de manejar el menú de game_over. Imprime "END" en la pantalla y espera a que
 * muevan el joystick. Luego permite elegir entre ir al menú inicial ("MENU") o terminar el juego/
 * apagar el display ("TRN OFF")
 * Recibe: un puntero a window_state_t con el estado de la ventana
 * Devuelve: -
 * 
 * Nota: Para cambiar opción mover hacia arriba ó abajo, para seleccionar usar el botón.
 */
void gameOver(window_state_t *state)
{
    disp_clear();
    disp_update();

    initAudio();
    pthread_t musicTh;
    pthread_create(&musicTh,NULL,musicThread_game_over,NULL); 
    pthread_join(musicTh,NULL);
    Audio*soundSelect=NULL;
    soundSelect = createAudio(SELECT_M, 0, SDL_MIX_MAXVOLUME);
    Audio*soundCursor=NULL;
    soundCursor = createAudio(CURSOR_M, 0, SDL_MIX_MAXVOLUME);


    printCharacter('E', 0, 5); //muestra pantalla "END"
    printCharacter('N', 5, 5);
    printCharacter('D', 11, 5);

    disp_update();

    wait(2);

    char direction = WAIT; 
    while (!joystick(&direction))
        ;
    while (!joystick(&direction))
        ;
    
    *state = MENU;
    disp_clear();
    printCharacter('M', 0, 0); // opción menú
    printCharacter('E', 9, 0);
    printCharacter('N', 0, 8);
    printCharacter('U', 9, 8);

    disp_update();

    while (direction != BUTTON) //espera a que se seleccione una opción
    {
        while (!joystick(&direction))
            ;

        if (direction == DOWN || direction == UP) //modifica opción a seleccionar
        {
            playSoundFromMemory(soundCursor, SDL_MIX_MAXVOLUME);
            if (*state == MENU)
            {
                *state = CLOSE_DISPLAY;
                disp_clear();
                printCharacter('T', 0, 0); //opcion apagar display
                printCharacter('R', 6, 0);
                printCharacter('N', 11, 0);
                printCharacter('O', 0, 8);
                printCharacter('F', 6, 8);
                printCharacter('F', 11, 8);
                disp_update();
            }
            else
            {
                *state = MENU;
                disp_clear();
                printCharacter('M', 0, 0); //opcion ir al menú
                printCharacter('E', 9, 0);
                printCharacter('N', 0, 8);
                printCharacter('U', 9, 8);

                disp_update();
            }
        }
    }

    playSoundFromMemory(soundSelect, SDL_MIX_MAXVOLUME);
    SDL_Delay(500);
    
    disp_clear(); 
    disp_update();
    endAudio();
    freeAudio(soundCursor);
    freeAudio(soundSelect);
    wait(0.5);
}

/* pauseRas()
 * Función que realiza el menu de pausa. Muestra "PAUSE" pos espera a que se mueva el joystick en
 * cualquier dirección. Luego te deja seguir jugando ("PLAY"), terminar la partida ("MENU") o
 * apagar la pantalla ("TRN OFF").
 * Recibe: window_state_t *state, puntero al estado de la ventana
 * Devuelve: -
 * 
 * Nota: Para cambiar opción mover hacia arriba ó abajo, para seleccionar usar el botón.
 */
static void pauseRas(window_state_t *state)
{
    disp_clear();
    pauseAudio();

    printCharacter('P', 0, 0); //muestra pantalla "PAUSE"
    printCharacter('A', 5, 0);
    printCharacter('U', 10, 0);
    printCharacter('S', 0, 8);
    printCharacter('E', 5, 8);
    disp_update();

    wait(1);
    char direction = WAIT; // espero a que toquen el boton para iniciar
    while (!joystick(&direction))
        ;
    while (!joystick(&direction))
        ;

    direction = WAIT;
    *state = GAME;
    disp_clear(); 
    printCharacter('P', 0, 0); //opción seguir jugando
    printCharacter('L', 9, 0);
    printCharacter('A', 0, 8);
    printCharacter('Y', 9, 8);
    disp_update();

    while (direction != BUTTON) //espera a que se seleccione una opción
    {
        while (!joystick(&direction))
            ;

        if (direction == DOWN || direction == UP) //cambia opción a seleccionar
        {
            if (*state == GAME)
            {
                *state = MENU;
                disp_clear(); 
                printCharacter('M', 0, 0); //opción ir al menu
                printCharacter('E', 9, 0);
                printCharacter('N', 0, 8);
                printCharacter('U', 9, 8);
                disp_update();
            }
            else if (*state == MENU)
            {
                *state = CLOSE_DISPLAY;
                disp_clear();
                printCharacter('T', 0, 0); // opción apagar display
                printCharacter('R', 6, 0);
                printCharacter('N', 11, 0);
                printCharacter('O', 0, 8);
                printCharacter('F', 6, 8);
                printCharacter('F', 11, 8);
                disp_update();
            }
            else
            {
                *state = GAME;
                disp_clear(); 
                printCharacter('P', 0, 0); // opción seguir jugando
                printCharacter('L', 9, 0);
                printCharacter('A', 0, 8);
                printCharacter('Y', 9, 8);
                disp_update();
            }
        }
    }

    disp_clear(); // apaga el display por completo
    disp_update();
    wait(1);
    unpauseAudio();
}


