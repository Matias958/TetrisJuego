/*HEADERS*/
#include <stdio.h>
#include <stdlib.h>
#include "inicializacion_al.h"

/*TIEMPO DE PARPADEO*/
#define FPS    5  

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
    elem->timer = al_create_timer(1.00/FPS);//crea el timer pero NO empieza a correr
    
    if (!elem->timer) //verificamos que se haya creado el timer
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
    
    elem->title = al_load_ttf_font("Retronoid.ttf", 180,0);

    if(!elem->title)
    {
        fprintf(stderr, "Falla al crear la fuente del título");
        al_destroy_font(elem->title);
        return EXIT_FAILURE; 
    }
    
    elem->buttons = al_load_ttf_font("game_over.ttf", 100,0);
    
    if(!elem->buttons)
    {
        fprintf(stderr, "Falla al crear la fuente de los botones");
        al_destroy_font(elem->buttons);
        return EXIT_FAILURE; 
    }
    
    elem->game_modes = al_load_ttf_font("Ice Mirror in Winter Kei.ttf", 20,0);

    if(!elem->title)
    {
        fprintf(stderr, "Falla al crear la fuente de la selección de modo de juego");
        al_destroy_font(elem->title);
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

    elem->sample_menu = al_load_sample("Dance-of-the-Sugar-Plum-Fairy.wav"); //cargamos el audio para el modo parpadeo

    if(!elem->sample_menu) 
    {
        printf("No se cargo el audio del menu!\n");
        return EXIT_FAILURE;
    }
    
    /*sample2 = al_load_sample("mixkit-arcade-video-game-pop-2887.wav"); //cargamos el audio para el click

    if(!sample2) 
    {
        printf("No se cargo el audio 2!\n");
        return EXIT_FAILURE;
    }
    
    sample3 = al_load_sample("mixkit-funny-fail-low-tone-2876.wav"); //cargamos el audio para el salir
    if(!sample3) 
    {
        printf("No se cargo el audio 2!\n");
        return EXIT_FAILURE;
    }
    */
    
    
    
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
        al_destroy_event_queue(elem->event_queue);
        al_destroy_timer(elem->timer);
        return EXIT_FAILURE;
    }
    
    
    
    /*INICIALIZACION DE EVENTOS*/
    elem->event_queue = al_create_event_queue(); //creamos la cola de eventos
    
    if (!elem->event_queue) //si la cola de eventos no se creo... 
    {
        fprintf(stderr, "Falla al crear la cola de eventos!\n");
        al_destroy_timer(elem->timer);
        return EXIT_FAILURE;
    }
    
    al_register_event_source(elem->event_queue, al_get_keyboard_event_source());
    al_register_event_source(elem->event_queue, al_get_display_event_source(elem->display));
    al_register_event_source(elem->event_queue, al_get_timer_event_source(elem->timer));
    al_register_event_source(elem->event_queue, al_get_mouse_event_source());    

    al_start_timer(elem->timer); //comienza el timer

    return EXIT_SUCCESS;
}