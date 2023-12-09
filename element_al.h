/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: element_al.h
*Descripcion: inicializacion y destruccion de
*            elementos de Allegro
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/

#ifndef ELEMENT_AL_H
#define ELEMENT_AL_H

/************** HEADERS ***************/
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_ttf.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h> //Extensiones con acodec .wav, .flac, .ogg, .it, .mod, .s3m, .xm.
#include <allegro5/allegro_image.h>

/************** MACROS ***************/

/*TAMAÑO DE LA PANTALLA*/
#define SCREEN_W 1260
#define SCREEN_H 720

/************** ESTRUCTURAS ***************/

/*element_t
* Estructura que contiene punteros a todos los elementos de Allegro
* utilizados en el programa.
*/
typedef struct
{
    ALLEGRO_DISPLAY *display;

    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_BITMAP *bitmapTrans;
    ALLEGRO_BITMAP *modesDescription;
    ALLEGRO_BITMAP *menuBackround;
    ALLEGRO_BITMAP *highscoreBackround;
    ALLEGRO_BITMAP *gameBackround;

    ALLEGRO_BITMAP *mirrored;
    ALLEGRO_BITMAP *blinking;
    ALLEGRO_BITMAP *notEmpty;

    ALLEGRO_BITMAP *mirroredPrs;
    ALLEGRO_BITMAP *blinkingPrs;
    ALLEGRO_BITMAP *notEmptyPrs;

    ALLEGRO_BITMAP *mirroredLogo;
    ALLEGRO_BITMAP *blinkingLogo;
    ALLEGRO_BITMAP *notEmptyLogo;
    ALLEGRO_BITMAP *borderLogo;

    ALLEGRO_BITMAP *controls;

    ALLEGRO_EVENT_QUEUE *eventQueue;

    ALLEGRO_TIMER *timerOn;
    ALLEGRO_TIMER *timerOff;
    ALLEGRO_TIMER *timerControls;

    ALLEGRO_FONT *title;
    ALLEGRO_FONT *titleBorder;
    ALLEGRO_FONT *buttons;
    ALLEGRO_FONT *buttonsBorder;
    ALLEGRO_FONT *gameModes;
    ALLEGRO_FONT *gameModesDescription;
    ALLEGRO_FONT *gameModesDescriptionBorder;
    ALLEGRO_FONT *difficulty;
    ALLEGRO_FONT *difficultyBorder;
    ALLEGRO_FONT *fontInGame;
    ALLEGRO_FONT *fontInGameBorder;
    ALLEGRO_FONT *gameOver;
    ALLEGRO_FONT *pauseMenu;
    ALLEGRO_FONT *highscoreNews;

    ALLEGRO_SAMPLE *sampleMenu;
    ALLEGRO_SAMPLE *sampleGame;
    ALLEGRO_SAMPLE *sampleGameOver;
    ALLEGRO_SAMPLE *sampleHighscore;

    ALLEGRO_SAMPLE_INSTANCE *sampleGameReg;

    ALLEGRO_SAMPLE *effectTetris;
    ALLEGRO_SAMPLE *effectPlay;
    ALLEGRO_SAMPLE *effectCursor;
    ALLEGRO_SAMPLE *effectSelect;
    ALLEGRO_SAMPLE *effectRotate;
    ALLEGRO_SAMPLE *effectMove;
    ALLEGRO_SAMPLE *effectHold;
    ALLEGRO_SAMPLE *effectCantHold;
    ALLEGRO_SAMPLE *effectLanding;
    ALLEGRO_SAMPLE *effectPause;
    ALLEGRO_SAMPLE *effectGameOver;
    ALLEGRO_SAMPLE *effectHighscore;
    ALLEGRO_SAMPLE *controlsMusic;
} element_t;

/************** PROTOTIPOS ***************/

/*initializeElements()
 * Función encargada de inicializar los elementos de allegro.
 * Recibe: Una estructura element_t con los elementos a inicializar.
 * Devuelve: EXIT_SUCCESS si logro inicializar todos los elementos
 *  EXIT_FAILURE de lo contrario.
 */
int initializeElements(element_t *elem);

/* destructorOfElements()
* Función encargada de destruir todos los elementos de Allegro
* que contiene la estructura element_t
* Recibe: Una estructura element_t con los elementos a destruir.
* Devuelve: EXIT_SUCCESS si logro destruir todos los elementos 
*/
int destructorOfElements(element_t *elem);

#endif 
