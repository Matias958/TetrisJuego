/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: audio_ras.c
*Descripcion: funciones utiles para el uso de threads para el 
*             manejo de audio en la raspberry
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#include "audio_ras.h"

void *musicThread_menu()
{
    playMusic(MENU_M, SDL_MIX_MAXVOLUME/3);

    return NULL;
}

void *musicThread_hs()
{
    playMusic(HIGHSCORE_M, SDL_MIX_MAXVOLUME/3);

    return NULL;
}

void *musicThread_game()
{
    playMusic(GAME_M, SDL_MIX_MAXVOLUME/5);

    return NULL;
}

void* musicThread_game_over()
{
    playMusic(GAME_OVER_M, SDL_MIX_MAXVOLUME/3);
    return NULL;
}

