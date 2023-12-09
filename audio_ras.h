#ifndef AUDIO_RAS_H
#define AUDIO_RAS_H

/*HEADERS*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <SDL2/SDL.h>
#include "audio.h"

/*MACROS*/
#define MENU_M "audio/menu.wav"
#define HIGHSCORE_M "audio/highscore.wav"
#define GAME_M "audio/game.wav"
#define GAME_OVER_M "audio/game_over.wav"
#define CURSOR_M "audio/cursor.wav"
#define PLAY_M "audio/play.wav"
#define SELECT_M "audio/select.wav"
#define ROTATE_M "audio/rotate.wav"
#define SE_GAME_LANDING_M "audio/se_game_landing.wav"
#define SE_GAME_PAUSE_M "audio/se_game_pause.wav"
#define ME_GAMEOVER_M "audio/me_game_gameover.wav"
#define SE_GAME_MOVE_M "audio/se_game_move.wav"
#define TETRIS_M "audio/tetris.wav"

/*PROTOTIPOS*/
void *musicThread_menu();
void *musicThread_hs();
void *musicThread_game();
void* musicThread_game_over();


#endif // AUDIO_RAS_H