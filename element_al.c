/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
*Titulo: element_al.c
*Descripcion: inicializacion y destruccion de
*            elementos de Allegro
*Autores: Facundo Torres
*         Julieta Libertad Rodriguez
*         Matias Minitti
*         Ramiro Nieto Abascal
*/


/************** HEADERS ***************/
#include <stdio.h>
#include <stdlib.h>
#include "element_al.h"

/************** MACROS ***************/
#define FPS 10

/*initializeElements()
 * Función encargada de inicializar los elementos de allegro.
 * Recibe: Una estructura element_t con los elementos a inicializar.
 * Devuelve: EXIT_SUCCESS si logro inicializar todos los elementos
 *  EXIT_FAILURE de lo contrario.
 */
int initializeElements(element_t* elem)
{

    //inicializamos todos los elementos con NULL
    elem->bitmap = NULL;
    elem->bitmapTrans = NULL;
    elem->blinking = NULL;
    elem->blinkingLogo = NULL;
    elem->blinkingPrs = NULL;
    elem->borderLogo = NULL;
    elem->buttons = NULL;
    elem->buttonsBorder = NULL;
    elem->difficulty = NULL;
    elem->difficultyBorder = NULL;
    elem->display = NULL;
    elem->effectCursor = NULL;
    elem->effectGameOver = NULL;
    elem->effectHighscore = NULL;
    elem->effectLanding = NULL;
    elem->effectMove = NULL;
    elem->effectPause = NULL;
    elem->effectPlay = NULL;
    elem->effectRotate = NULL;
    elem->effectSelect = NULL;
    elem->effectTetris = NULL;
    elem->eventQueue = NULL;
    elem->fontInGame = NULL;
    elem->fontInGameBorder = NULL;
    elem->gameBackround = NULL;
    elem->gameModes = NULL;
    elem->gameModesDescription = NULL;
    elem->gameModesDescriptionBorder = NULL;
    elem->gameOver = NULL;
    elem->highscoreBackround = NULL;
    elem->highscoreNews = NULL;
    elem->menuBackround = NULL;
    elem->mirrored = NULL;
    elem->mirroredLogo = NULL;
    elem->mirroredPrs = NULL;
    elem->modesDescription = NULL;
    elem->notEmpty = NULL;
    elem->notEmptyLogo = NULL;
    elem->notEmptyPrs = NULL;
    elem->pauseMenu = NULL;
    elem->controls = NULL;
    elem->sampleGameOver = NULL;
    elem->sampleGameReg = NULL;
    elem->sampleHighscore = NULL;
    elem->sampleMenu = NULL;
    elem->timerOff = NULL;
    elem->timerOn = NULL;
    elem->timerControls = NULL;
    elem->title = NULL;
    elem->titleBorder = NULL;

    /*NOMBRE DE LA VENTANA*/
    al_set_new_window_title("TETRIS");

    /*INICIALIZACIÓN DEL SISTEMA*/
    if (!al_init())
    {
        fprintf(stderr, "Error al inicializar alegro!\n");
        return EXIT_FAILURE;
    }

    if (!al_install_keyboard())
    {
        fprintf(stderr, "Error al inicializar el teclado!\n");
        return EXIT_FAILURE;
    }

    if (!al_install_mouse())
    {
        fprintf(stderr, "Falla al inicializar el mouse!\n");
        return EXIT_FAILURE;
    }

    /*INICIALIZACIÓN DE TIMER*/
    elem->timerOn = al_create_timer(2.0); // crea el timer pero NO empieza a correr

    if (!elem->timerOn) // verificamos que se haya creado el timer
    {
        fprintf(stderr, "Fallo al crear el timer!\n");
        return EXIT_FAILURE;
    }

    elem->timerOff = al_create_timer(1.0); // crea el timer pero NO empieza a correr

    if (!elem->timerOff) // verificamos que se haya creado el timer
    {
        fprintf(stderr, "Fallo al crear el timer!\n");
        return EXIT_FAILURE;
    }

    elem->timerControls = al_create_timer(6.0);

    if (!elem->timerControls) // verificamos que se haya creado el timer
    {
        fprintf(stderr, "Fallo al crear el timer!\n");
        return EXIT_FAILURE;
    }


    /*INICIALIZACIÓN DE FUENTES*/
    if (!al_init_font_addon() || !al_init_ttf_addon()) // inicializamos la fuente
    {
        fprintf(stderr, "Falla al inicializar fuente\n");
        return EXIT_FAILURE;
    }

    elem->title = al_load_ttf_font("fonts/Retronoid.ttf", 180, 0);

    if (!elem->title)
    {
        fprintf(stderr, "Falla al crear la fuente del título\n");
        return EXIT_FAILURE;
    }

    elem->titleBorder = al_load_ttf_font("fonts/Retronoid.ttf", 184, 0);

    if (!elem->titleBorder)
    {
        fprintf(stderr, "Falla al crear la fuente del borde del título\n");
        return EXIT_FAILURE;
    }

    elem->buttons = al_load_ttf_font("fonts/game_over.ttf", 100, 0);

    if (!elem->buttons)
    {
        fprintf(stderr, "Falla al crear la fuente de los botones\n");
        return EXIT_FAILURE;
    }

    elem->buttonsBorder = al_load_ttf_font("fonts/game_over.ttf", 106, 0);

    if (!elem->buttonsBorder)
    {
        fprintf(stderr, "Falla al crear la fuente del borde de los botones\n");
        return EXIT_FAILURE;
    }

    elem->gameModesDescription = al_load_ttf_font("fonts/whitrabt.ttf", 25, 0);

    if (!elem->gameModesDescription)
    {
        fprintf(stderr, "Falla al crear la fuente de la descripción de modo de juego\n");
        return EXIT_FAILURE;
    }

    elem->gameModesDescriptionBorder = al_load_ttf_font("fonts/whitrabt.ttf", 25.75, 0);

    if (!elem->gameModesDescriptionBorder)
    {
        fprintf(stderr, "Falla al crear la fuente del borde de la descripción de modo de juego\n");
        return EXIT_FAILURE;
    }

    elem->gameModes = al_load_ttf_font("fonts/Ice Mirror in Winter Kei.ttf", 30, 0);

    if (!elem->gameModes)
    {
        fprintf(stderr, "Falla al crear la fuente de la selección de modo de juego\n");
        return EXIT_FAILURE;
    }

    elem->difficulty = al_load_ttf_font("fonts/Starborn.ttf", 30, 0);

    if (!elem->difficulty)
    {
        fprintf(stderr, "Falla al crear la fuente de la dificultad\n");
        return EXIT_FAILURE;
    }
    elem->difficultyBorder = al_load_ttf_font("fonts/Starborn.ttf", 35, 0);

    if (!elem->difficultyBorder)
    {
        fprintf(stderr, "Falla al crear la fuente del borde de la dificultad\n");
        return EXIT_FAILURE;
    }

    elem->fontInGame = al_load_ttf_font("fonts/AovelSansRounded-rdDL.ttf", 22, 0);

    if (!elem->fontInGame)
    {
        fprintf(stderr, "Falla al crear la fuente de puntaje en juego\n");
        return EXIT_FAILURE;
    }

    elem->fontInGameBorder = al_load_ttf_font("fonts/AovelSansRounded-rdDL.ttf", 24, 0);

    if (!elem->fontInGameBorder)
    {
        fprintf(stderr, "Falla al crear la fuente del borde del puntaje en juego\n");
        return EXIT_FAILURE;
    }

    elem->gameOver = al_load_ttf_font("fonts/game_over.ttf", 180, 0);

    if (!elem->gameOver)
    {
        fprintf(stderr, "Falla al crear la fuente del game over\n");
        return EXIT_FAILURE;
    }

    elem->pauseMenu = al_load_ttf_font("fonts/THE-GLITCH.ttf", 100, 0);

    if (!elem->pauseMenu)
    {
        fprintf(stderr, "Falla al crear la fuente del menu de pausa\n");
        return EXIT_FAILURE;
    }

    elem->highscoreNews = al_load_ttf_font("fonts/budmo jiggler.otf", 30, 0);

    if (!elem->highscoreNews)
    {
        fprintf(stderr, "Falla al crear la fuente de la noticia de highscore\n");
        return EXIT_FAILURE;
    }

    /*INICIAIZACIÓN DE AUDIO*/
    if (!al_install_audio()) // inicializamos el audio
    {
        fprintf(stderr, "Falla al inicializar audio!\n");
        return EXIT_FAILURE;
    }

    if (!al_init_acodec_addon())
    {
        fprintf(stderr, "Falla al inicializar audio codecs!\n");
        return EXIT_FAILURE;
    }

    if (!al_reserve_samples(3)) // reservamos 3 muestras
    {
        fprintf(stderr, "Falla al reservar muestras!\n");
        return EXIT_FAILURE;
    }

    elem->sampleMenu = al_load_sample("audio/menu.wav"); // cargamos el audio para el menu

    if (!elem->sampleMenu)
    {
        printf("No se cargo el audio del menu!\n");
        return EXIT_FAILURE;
    }

    elem->sampleGame = al_load_sample("audio/game.wav"); // cargamos el audio para el juego

    if (!elem->sampleGame)
    {
        printf("No se cargo el audio del juego!\n");
        return EXIT_FAILURE;
    }

    elem->sampleGameReg = al_create_sample_instance(elem->sampleGame);

    if (!elem->sampleGameReg)
    {
        fprintf(stderr, "Error al crear la instancia de sample regulable del juego.\n");
        return EXIT_FAILURE;
    }
    al_attach_sample_instance_to_mixer(elem->sampleGameReg, al_get_default_mixer());

    elem->sampleHighscore = al_load_sample("audio/highscore.wav"); // cargamos el audio para el menu de highscore

    if (!elem->sampleHighscore)
    {
        printf("No se cargo el audio de highscore!\n");
        return EXIT_FAILURE;
    }

    elem->effectTetris = al_load_sample("audio/tetris.wav"); // cargamos el audio para el efector de tetris
    if (!elem->effectTetris)
    {
        printf("No se cargo el audio del efecto: tetris\n");
        return EXIT_FAILURE;
    }

    elem->effectPlay = al_load_sample("audio/play.wav"); // cargamos el audio para el efecto de play
    if (!elem->effectPlay)
    {
        printf("No se cargo el audio del efecto: play\n");
        return EXIT_FAILURE;
    }

    elem->effectCursor = al_load_sample("audio/cursor.wav"); // cargamos el audio para el cursor
    if (!elem->effectCursor)
    {
        printf("No se cargo el audio del efecto: cursor\n");
        return EXIT_FAILURE;
    }

    elem->effectSelect = al_load_sample("audio/select.wav"); // cargamos el audio para el effect select
    if (!elem->effectCursor)
    {
        printf("No se cargo el audio del efecto: select\n");
        return EXIT_FAILURE;
    }

    elem->effectRotate = al_load_sample("audio/rotate.wav"); // cargamos el audio para el effect rotate
    if (!elem->effectRotate)
    {
        printf("No se cargo el audio del efecto: rotacion\n");
        return EXIT_FAILURE;
    }

    elem->effectMove = al_load_sample("audio/se_game_move.wav"); // cargamos el audio para el effect move
    if (!elem->effectMove)
    {
        printf("No se cargo el audio del efecto: movimiento\n");
        return EXIT_FAILURE;
    }

    elem->effectLanding = al_load_sample("audio/se_game_landing.wav"); // cargamos el audio para el effect landing
    if (!elem->effectLanding)
    {
        printf("No se cargo el audio del efecto: caida\n");
        return EXIT_FAILURE;
    }

    elem->effectPause = al_load_sample("audio/se_game_pause.wav"); // cargamos el audio para el effect pause
    if (!elem->effectLanding)
    {
        printf("No se cargo el audio del efecto: pausa\n");
        return EXIT_FAILURE;
    }

    elem->controlsMusic = al_load_sample("audio/controls.wav");
    if (!elem->controlsMusic)
    {
        printf("No se cargo el audio del audio de menu de controles\n");
        return EXIT_FAILURE;
    }

    elem->effectGameOver = al_load_sample("audio/me_game_gameover.wav");
    if (!elem->effectGameOver)
    {
        printf("No se cargo el audio del efecto: game over\n");
        return EXIT_FAILURE;
    }

    elem->sampleGameOver = al_load_sample("audio/game_over.wav");
    if (!elem->sampleGameOver)
    {
        printf("No se cargo el audio del audio de menu de game over\n");
        return EXIT_FAILURE;
    }

    elem->effectHighscore = al_load_sample("audio/se_game_perfect.wav");
    if (!elem->effectHighscore)
    {
        printf("No se cargo el audio del audio de la obtencion de un highscore\n");
        return EXIT_FAILURE;
    }

    /*PRIMITIVAS*/
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falla al inicializar primitivas!\n");
        return EXIT_FAILURE;
    }

    /*INICIALIZACIÓN DEL DISPLAY*/
    elem->display = al_create_display(SCREEN_W, SCREEN_H); // creamos un display de 1000 x 700

    if (!elem->display) // si el display no se creo...
    {
        fprintf(stderr, "Falla al crear el display!\n");
        return EXIT_FAILURE;
    }

    elem->bitmap = al_create_bitmap(SCREEN_W / 2, SCREEN_H / 2);
    if (!elem->bitmap)
    {
        fprintf(stderr, "Falla al crear el bitmap.\n");
        return EXIT_FAILURE;
    }

    elem->bitmapTrans = al_create_bitmap(SCREEN_W , SCREEN_H);
    if (!elem->bitmapTrans)
    {
        fprintf(stderr, "Falla al crear el bitmap de transicion.\n");
        return EXIT_FAILURE;
    }

    elem->modesDescription = al_create_bitmap(300, 300);
    if (!elem->modesDescription)
    {
        fprintf(stderr, "Falla al crear el bitmap de descripción de modo de juego.\n");
        return EXIT_FAILURE;
    }

    if (!al_init_image_addon())
    {
        fprintf(stderr, "Error al inicializar el sistema de imagenes de allegro.\n");
        return EXIT_FAILURE;
    }

    elem->menuBackround = al_load_bitmap("pictures/menu.bmp");
    if (!elem->menuBackround)
    {
        fprintf(stderr, "Falla al crear el bitmap del fondo del menu.\n");
        return EXIT_FAILURE;
    }

    elem->highscoreBackround = al_load_bitmap("pictures/highscore.bmp");
    if (!elem->highscoreBackround)
    {
        fprintf(stderr, "Falla al crear el bitmap del fondo de highscore.\n");
        return EXIT_FAILURE;
    }

    elem->gameBackround = al_load_bitmap("pictures/game.bmp");
    if (!elem->gameBackround)
    {
        fprintf(stderr, "Falla al crear el bitmap del fondo del juego.\n");
        return EXIT_FAILURE;
    }

    elem->controls = al_load_bitmap("pictures/controls.bmp");
    if (!elem->controls)
    {
        fprintf(stderr, "Falla al crear imagen de los controles del juego.\n");
        return EXIT_FAILURE;
    }

    elem->mirrored = al_load_bitmap("pictures/mirrored.bmp");
    if (!elem->mirrored)
    {
        fprintf(stderr, "Falla al crear el bitmap de mirrored.\n");
        return EXIT_FAILURE;
    }

    elem->blinking = al_load_bitmap("pictures/blinking.bmp");
    if (!elem->blinking)
    {
        fprintf(stderr, "Falla al crear el bitmap de blinking.\n");
        return EXIT_FAILURE;
    }

    elem->notEmpty = al_load_bitmap("pictures/no_empty.bmp");
    if (!elem->notEmpty)
    {
        fprintf(stderr, "Falla al crear el bitmap de no_empty.\n");
        return EXIT_FAILURE;
    }

    elem->mirroredPrs = al_load_bitmap("pictures/mirrored_prs.bmp");
    if (!elem->mirrored)
    {
        fprintf(stderr, "Falla al crear el bitmap de mirrored.\n");
        return EXIT_FAILURE;
    }

    elem->blinkingPrs = al_load_bitmap("pictures/blinking_prs.bmp");
    if (!elem->blinking)
    {
        fprintf(stderr, "Falla al crear el bitmap de blinking.\n");
        return EXIT_FAILURE;
    }

    elem->notEmptyPrs = al_load_bitmap("pictures/no_empty_prs.bmp");
    if (!elem->notEmpty)
    {
        fprintf(stderr, "Falla al crear el bitmap de no_empty.\n");
        return EXIT_FAILURE;
    }

    elem->notEmptyLogo = al_load_bitmap("pictures/not_empty_logo.bmp");
    if (!elem->notEmptyLogo)
    {
        fprintf(stderr, "Falla al crear el bitmap del logo de no_empty.\n");
        return EXIT_FAILURE;
    }

    elem->blinkingLogo = al_load_bitmap("pictures/blinking_logo.bmp");
    if (!elem->blinkingLogo)
    {
        fprintf(stderr, "Falla al crear el bitmap del logo de blinking.\n");
        return EXIT_FAILURE;
    }

    elem->mirroredLogo = al_load_bitmap("pictures/mirrored_logo.bmp");
    if (!elem->mirroredLogo)
    {
        fprintf(stderr, "Falla al crear el bitmap del logo de mirrored.\n");
        return EXIT_FAILURE;
    }

    elem->borderLogo = al_create_bitmap(75, 75);
    if (!elem->borderLogo)
    {
        fprintf(stderr, "Falla al crear el bitmap del borde de los logos.\n");
        return EXIT_FAILURE;
    }

    /*INICIALIZACION DE EVENTOS*/
    elem->eventQueue = al_create_event_queue(); // creamos la cola de eventos

    if (!elem->eventQueue) // si la cola de eventos no se creo...
    {
        fprintf(stderr, "Falla al crear la cola de eventos!\n");
        return EXIT_FAILURE;
    }

    //registramos los elementos en la cola de eventos
    al_register_event_source(elem->eventQueue, al_get_keyboard_event_source());
    al_register_event_source(elem->eventQueue, al_get_display_event_source(elem->display));
    al_register_event_source(elem->eventQueue, al_get_timer_event_source(elem->timerOn));
    al_register_event_source(elem->eventQueue, al_get_timer_event_source(elem->timerOff));
    al_register_event_source(elem->eventQueue, al_get_timer_event_source(elem->timerControls));
    al_register_event_source(elem->eventQueue, al_get_mouse_event_source());

    return EXIT_SUCCESS;
}


// Función para destruir un display
static void destroyDisplay(ALLEGRO_DISPLAY *display)
{
    if (display)
    {
        al_destroy_display(display);
    }
}

// Función para destruir un bitmap
static void destroyBitmap(ALLEGRO_BITMAP *bitmap)
{
    if (bitmap)
    {
        al_destroy_bitmap(bitmap);
    }
}

// Función para destruir un eventQueue
static void destroyEventQueue(ALLEGRO_EVENT_QUEUE *eventQueue)
{
    if (eventQueue)
    {
        al_destroy_event_queue(eventQueue);
    }
}

// Función para destruir un timer
static void destroyTimer(ALLEGRO_TIMER *timer)
{
    if (timer)
    {
        al_destroy_timer(timer);
    }
}

// Función para destruir una fuente
static void destroyFont(ALLEGRO_FONT *font)
{
    if (font)
    {
        al_destroy_font(font);
    }
}

// Función para destruir un sample
static void destroySample(ALLEGRO_SAMPLE *sample)
{
    if (sample)
    {
        al_destroy_sample(sample);
    }
}

// Función para destruir una sample instance
static void destroySampleInstance(ALLEGRO_SAMPLE_INSTANCE *sample_instance)
{
    if (sample_instance)
    {
        al_destroy_sample_instance(sample_instance);
    }
}

/* destructorOfElements()
* Función encargada de destruir todos los elementos de Allegro
* que contiene la estructura element_t
* Recibe: Una estructura element_t con los elementos a destruir.
* Devuelve: EXIT_SUCCESS si logro destruir todos los elementos 
*/
int destructorOfElements(element_t *elem)
{
    destroyDisplay(elem->display);

    destroyBitmap(elem->bitmap);
    destroyBitmap(elem->modesDescription);
    destroyBitmap(elem->menuBackround);
    destroyBitmap(elem->highscoreBackround);
    destroyBitmap(elem->gameBackround);
    destroyBitmap(elem->mirrored);
    destroyBitmap(elem->blinking);
    destroyBitmap(elem->notEmpty);
    destroyBitmap(elem->mirroredPrs);
    destroyBitmap(elem->blinkingPrs);
    destroyBitmap(elem->notEmptyPrs);
    destroyBitmap(elem->mirroredLogo);
    destroyBitmap(elem->blinkingLogo);
    destroyBitmap(elem->notEmptyLogo);
    destroyBitmap(elem->borderLogo);
    destroyBitmap(elem->controls);

    destroyEventQueue(elem->eventQueue);

    destroyTimer(elem->timerOn);
    destroyTimer(elem->timerOff);
    destroyTimer(elem->timerControls);

    destroyFont(elem->title);
    destroyFont(elem->titleBorder);
    destroyFont(elem->buttons);
    destroyFont(elem->buttonsBorder);
    destroyFont(elem->gameModes);
    destroyFont(elem->gameModesDescription);
    destroyFont(elem->gameModesDescriptionBorder);
    destroyFont(elem->difficulty);
    destroyFont(elem->difficultyBorder);
    destroyFont(elem->fontInGame);
    destroyFont(elem->fontInGameBorder);
    destroyFont(elem->gameOver);
    destroyFont(elem->pauseMenu);
    destroyFont(elem->highscoreNews);

    destroySample(elem->sampleMenu);
    destroySample(elem->sampleGame);
    destroySample(elem->sampleGameOver);
    destroySample(elem->sampleHighscore);
    destroySample(elem->controlsMusic);

    destroySampleInstance(elem->sampleGameReg);

    destroySample(elem->effectTetris);
    destroySample(elem->effectPlay);
    destroySample(elem->effectCursor);
    destroySample(elem->effectSelect);
    destroySample(elem->effectRotate);
    destroySample(elem->effectMove);
    destroySample(elem->effectLanding);
    destroySample(elem->effectPause);
    destroySample(elem->effectGameOver);
    destroySample(elem->effectHighscore);

    al_uninstall_system();
    return EXIT_SUCCESS;
}
