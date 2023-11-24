/*HEADERS*/
#include <stdio.h>
#include <stdlib.h>
#include "inicializacion_al.h"  


#define FPS 10

/*INICIALIZA_AL()
* Función encargada de inicializar los elementos de allegro.
* Recibe: Una estructura element_t con los elementos a inicializar.
* Devuelve: Un int que indica si se logró o no inicializar todo correctamente.
*/
int inicializa_al(element_t* elem) 
{
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
    elem->timer_on = al_create_timer(2.0);//crea el timer pero NO empieza a correr
    
    if (!elem->timer_on) //verificamos que se haya creado el timer
    {
        fprintf(stderr, "Fallo al crear el timer!\n");
        return EXIT_FAILURE;
    }

    elem->timer_off = al_create_timer(1.0);//crea el timer pero NO empieza a correr

    if (!elem->timer_off) //verificamos que se haya creado el timer
    {
        fprintf(stderr, "Fallo al crear el timer!\n");
        return EXIT_FAILURE;
    }
   
    
    
    /*INICIALIZACIÓN DE FUENTES*/
    if(!al_init_font_addon() || !al_init_ttf_addon())//inicializamos la fuente
    {
        fprintf(stderr, "Falla al inicializar fuente");
        return EXIT_FAILURE;
    }
    
    elem->title = al_load_ttf_font("fonts/Retronoid.ttf", 180,0);

    if(!elem->title)
    {
        fprintf(stderr, "Falla al crear la fuente del título");
        al_destroy_font(elem->title);
        return EXIT_FAILURE; 
    }
    
    elem->buttons = al_load_ttf_font("fonts/game_over.ttf", 100,0);
    
    if(!elem->buttons)
    {
        fprintf(stderr, "Falla al crear la fuente de los botones");
        al_destroy_font(elem->buttons);
        return EXIT_FAILURE; 
    }
    
    elem->game_modes = al_load_ttf_font("fonts/Ice Mirror in Winter Kei.ttf", 20,0);

    if(!elem->title)
    {
        fprintf(stderr, "Falla al crear la fuente de la selección de modo de juego");
        al_destroy_font(elem->title);
        return EXIT_FAILURE; 
    }

    elem->font_in_game = al_load_ttf_font("fonts/AovelSansRounded-rdDL.ttf", 22,0);

    if(!elem->font_in_game)
    {
        fprintf(stderr, "Falla al crear la fuente de puntaje en juego");
        al_destroy_font(elem->font_in_game);
        return EXIT_FAILURE; 
    }

    elem->game_over = al_load_ttf_font("fonts/game_over.ttf", 180, 0);

    if (!elem->game_over)
    {
        fprintf(stderr, "Falla al crear la fuente del game over");
        al_destroy_font(elem->game_over);
        return EXIT_FAILURE;
    }

    elem->pause_menu = al_load_ttf_font("fonts/THE-GLITCH.ttf", 100, 0);

    if (!elem->pause_menu)
    {
        fprintf(stderr, "Falla al crear la fuente del menu de pausa");
        al_destroy_font(elem->pause_menu);
        return EXIT_FAILURE;
    }

    elem->highscore_news = al_load_ttf_font("fonts/budmo jiggler.otf", 30, 0);

    if (!elem->highscore_news)
    {
        fprintf(stderr, "Falla al crear la fuente de la noticia de highscore");
        al_destroy_font(elem->highscore_news);
        return EXIT_FAILURE;
    }
    
    /*INICIAIZACIÓN DE AUDIO*/
    if (!al_install_audio())//inicializamos el audio
    {
        fprintf(stderr, "Falla al inicializar audio!\n");
        return EXIT_FAILURE;
    }
  
    if(!al_init_acodec_addon()) 
    {
        fprintf(stderr, "Falla al inicializar audio codecs!\n");
        return EXIT_FAILURE;
    }

    if(!al_reserve_samples(3)) //reservamos 3 muestras
    {
        fprintf(stderr, "Falla al reservar muestras!\n");
        return EXIT_FAILURE;
    }

    elem->sample_menu = al_load_sample("audio/menu.wav"); //cargamos el audio para el menu

    if(!elem->sample_menu) 
    {
        printf("No se cargo el audio del menu!\n");
        return EXIT_FAILURE;
    }
    
    elem->sample_game = al_load_sample("audio/game.wav"); //cargamos el audio para el juego

    if(!elem->sample_game) 
    {
        printf("No se cargo el audio del juego!\n");
        return EXIT_FAILURE;
    }

    elem->sample_game_reg = al_create_sample_instance(elem->sample_game);

    if (!elem->sample_game_reg) {
        fprintf(stderr, "Error al crear la instancia de sample regulable del juego.\n");
        return EXIT_FAILURE;
    }
    al_attach_sample_instance_to_mixer(elem->sample_game_reg, al_get_default_mixer());
    
    elem->sample_highscore = al_load_sample("audio/highscore.wav"); //cargamos el audio para el menu de highscore

    if (!elem->sample_highscore)
    {
        printf("No se cargo el audio de highscore!\n");
        return EXIT_FAILURE;
    }
    
    
    elem->effect_tetris = al_load_sample("audio/tetris.wav"); //cargamos el audio para el efector de tetris
    if(!elem->effect_tetris) 
    {
        printf("No se cargo el audio del efecto: tetris\n");
        return EXIT_FAILURE;
    }
    
    elem->effect_play = al_load_sample("audio/play.wav"); //cargamos el audio para el efecto de play
    if (!elem->effect_play)
    {
        printf("No se cargo el audio del efecto: play\n");
        return EXIT_FAILURE;
    }

    elem->effect_cursor = al_load_sample("audio/cursor.wav"); //cargamos el audio para el cursor
    if (!elem->effect_cursor)
    {
        printf("No se cargo el audio del efecto: cursor\n");
        return EXIT_FAILURE;
    }

    elem->effect_select = al_load_sample("audio/select.wav"); //cargamos el audio para el effect select
    if (!elem->effect_cursor)
    {
        printf("No se cargo el audio del efecto: select\n");
        return EXIT_FAILURE;
    }

    elem->effect_rotate = al_load_sample("audio/rotate.wav"); //cargamos el audio para el effect rotate
    if (!elem->effect_rotate)
    {
        printf("No se cargo el audio del efecto: rotacion\n");
        return EXIT_FAILURE;
    }

    elem->effect_move = al_load_sample("audio/se_game_move.wav"); //cargamos el audio para el effect move
    if (!elem->effect_move)
    {
        printf("No se cargo el audio del efecto: movimiento\n");
        return EXIT_FAILURE;
    }


    elem->effect_landing = al_load_sample("audio/se_game_landing.wav"); //cargamos el audio para el effect landing
    if (!elem->effect_landing)
    {
        printf("No se cargo el audio del efecto: caida\n");
        return EXIT_FAILURE;
    }

    elem->effect_pause = al_load_sample("audio/se_game_pause.wav"); //cargamos el audio para el effect pause
    if (!elem->effect_landing)
    {
        printf("No se cargo el audio del efecto: pausa\n");
        return EXIT_FAILURE;
    }

    elem->effect_game_over = al_load_sample("audio/me_game_gameover.wav"); 
    if (!elem->effect_game_over)
    {
        printf("No se cargo el audio del efecto: game over\n");
        return EXIT_FAILURE;
    }

    elem->sample_game_over = al_load_sample("audio/game_over.wav"); 
    if (!elem->sample_game_over)
    {
        printf("No se cargo el audio del audio de menu de game over\n");
        return EXIT_FAILURE;
    }

    elem->effect_highscore = al_load_sample("audio/se_game_perfect.wav"); 
    if (!elem->effect_highscore)
    {
        printf("No se cargo el audio del audio de la obtencion de un highscore\n");
        return EXIT_FAILURE;
    }


    /*PRIMITIVAS*/
    if(!al_init_primitives_addon())
    {
        fprintf(stderr, "Falla al inicializar primitivas!\n");
        return EXIT_FAILURE;
    }
    
     
    
    /*INICIALIZACIÓN DEL DISPLAY*/
    elem->display = al_create_display(SCREEN_W, SCREEN_H);//creamos un display de 1000 x 700
    
    if (!elem->display)//si el display no se creo... 
    {
        fprintf(stderr, "Falla al crear el display!\n");
        return EXIT_FAILURE;
    }

    elem->bitmap = al_create_bitmap(SCREEN_W/2, SCREEN_H/2);
    if (!elem->bitmap) 
    {
        fprintf(stderr, "Falla al crear el bitmap.\n");
        return EXIT_FAILURE;
    }

    if (!al_init_image_addon()) 
    {
        fprintf(stderr, "Error al inicializar el sistema de imagenes de allegro.\n");
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

    elem->no_empty = al_load_bitmap("pictures/no_empty.bmp");
    if (!elem-> no_empty)
    {
        fprintf(stderr, "Falla al crear el bitmap de no_empty.\n");
        return EXIT_FAILURE;
    }

    elem->mirrored_prs = al_load_bitmap("pictures/mirrored_prs.bmp");
    if (!elem->mirrored)
    {
        fprintf(stderr, "Falla al crear el bitmap de mirrored.\n");
        return EXIT_FAILURE;
    }

    elem->blinking_prs = al_load_bitmap("pictures/blinking_prs.bmp");
    if (!elem->blinking)
    {
        fprintf(stderr, "Falla al crear el bitmap de blinking.\n");
        return EXIT_FAILURE;
    }

    elem->no_empty_prs = al_load_bitmap("pictures/no_empty_prs.bmp");
    if (!elem->no_empty)
    {
        fprintf(stderr, "Falla al crear el bitmap de no_empty.\n");
        return EXIT_FAILURE;
    }


    
    /*INICIALIZACION DE EVENTOS*/
    elem->event_queue = al_create_event_queue(); //creamos la cola de eventos
    
    if (!elem->event_queue) //si la cola de eventos no se creo... 
    {
        fprintf(stderr, "Falla al crear la cola de eventos!\n");
        return EXIT_FAILURE;
    }
    
    al_register_event_source(elem->event_queue, al_get_keyboard_event_source());
    al_register_event_source(elem->event_queue, al_get_display_event_source(elem->display));
    al_register_event_source(elem->event_queue, al_get_timer_event_source(elem->timer_on));
    al_register_event_source(elem->event_queue, al_get_timer_event_source(elem->timer_off));
    al_register_event_source(elem->event_queue, al_get_mouse_event_source());    

    return EXIT_SUCCESS;
}

