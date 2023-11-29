/*HEADERS*/
#include "joydrv.h"
#include "disdrv.h"
#include "raspberry.h"
#include "rules.h"
#include "pieces.h"


/*INIT()
* Función encargada de inicializar la pantalla con la palabra "tetris" y esperar hasta
* que se presione el botón del joystick para empezar el juego.
* Recibe: -
* Devuelve: -
*/
void init (void)
{
    disp_init();                                //inicializo el display
    joy_init();                                 //inicializo el joystick

    disp_clear();                               //apaga el display por completo (preventivo)
    disp_update();
    
    disp_write((dcoord_t){2,2} , D_ON);            //dibuje una pantalla que escribe tetris
    disp_write((dcoord_t){2,3}, D_ON);
    disp_write((dcoord_t){2,4}, D_ON);
    disp_write((dcoord_t){2,6}, D_ON);
    disp_write((dcoord_t){2,7}, D_ON);
    disp_write((dcoord_t){2,8}, D_ON);
    disp_write((dcoord_t){2,10}, D_ON);
    disp_write((dcoord_t){2,11}, D_ON);
    disp_write((dcoord_t){2,12}, D_ON);
    disp_write((dcoord_t){3,2}, D_ON);
    disp_write((dcoord_t){3,3}, D_ON);
    disp_write((dcoord_t){3,4}, D_ON);
    disp_write((dcoord_t){3,6}, D_ON);
    disp_write((dcoord_t){3,10}, D_ON);
    disp_write((dcoord_t){3,11}, D_ON);
    disp_write((dcoord_t){3,12}, D_ON);
    disp_write((dcoord_t){4,3}, D_ON);
    disp_write((dcoord_t){4,6}, D_ON);
    disp_write((dcoord_t){4,7}, D_ON);
    disp_write((dcoord_t){4,11}, D_ON);
    disp_write((dcoord_t){5,3}, D_ON);
    disp_write((dcoord_t){5,6}, D_ON);
    disp_write((dcoord_t){5,11}, D_ON);
    disp_write((dcoord_t){6,3}, D_ON);
    disp_write((dcoord_t){6,6}, D_ON);
    disp_write((dcoord_t){6,7}, D_ON);
    disp_write((dcoord_t){6,8}, D_ON);
    disp_write((dcoord_t){6,11}, D_ON);
    disp_write((dcoord_t){9,2}, D_ON);
    disp_write((dcoord_t){9,3}, D_ON);
    disp_write((dcoord_t){9,4}, D_ON);
    disp_write((dcoord_t){9,5}, D_ON);
    disp_write((dcoord_t){9,7}, D_ON);
    disp_write((dcoord_t){9,8}, D_ON);
    disp_write((dcoord_t){9,10}, D_ON);
    disp_write((dcoord_t){9,11}, D_ON);
    disp_write((dcoord_t){9,12}, D_ON);
    disp_write((dcoord_t){10,2}, D_ON);
    disp_write((dcoord_t){10,4}, D_ON);
    disp_write((dcoord_t){10,10}, D_ON);
    disp_write((dcoord_t){11,2}, D_ON);
    disp_write((dcoord_t){11,3}, D_ON);
    disp_write((dcoord_t){11,4}, D_ON);
    disp_write((dcoord_t){11,5}, D_ON);
    disp_write((dcoord_t){11,7}, D_ON);
    disp_write((dcoord_t){11,8}, D_ON);
    disp_write((dcoord_t){11,10}, D_ON);
    disp_write((dcoord_t){11,11}, D_ON);
    disp_write((dcoord_t){11,12}, D_ON);
    disp_write((dcoord_t){12,2}, D_ON);
    disp_write((dcoord_t){12,4}, D_ON);
    disp_write((dcoord_t){12,7}, D_ON);
    disp_write((dcoord_t){12,8}, D_ON);
    disp_write((dcoord_t){12,12}, D_ON);
    disp_write((dcoord_t){13,2}, D_ON);
    disp_write((dcoord_t){13,5}, D_ON);
    disp_write((dcoord_t){13,7}, D_ON);
    disp_write((dcoord_t){13,8}, D_ON);
    disp_write((dcoord_t){13,10}, D_ON);
    disp_write((dcoord_t){13,11}, D_ON);
    disp_write((dcoord_t){13,12}, D_ON);

    disp_update();
   
    while ( joystick() != BUTTON);      //espero a que toquen el boton para iniciar 
    {
        
    }

    disp_clear();                               //apaga el display por completo
    disp_update();

   return;
}

/*JOYSTICK()
* Función encargada de analizar el estado del joystick.
* Recibe: -
* Devuelve: Un char con el estado del joystick.
*/
char joystick(void)
{
    char direction = WAIT;
    joyinfo_t coordenates = joy_read();

    while (direction == WAIT)
    {
        if (coordenates.sw == J_PRESS)
        {
            direction = BUTTON;
        }
        else if (( -100 < coordenates.x < 100) && ( 100 < coordenates.y < 127))
        {
            direction = UP;
        }
        else if (( -100 < coordenates.x < 100) && ( -128 < coordenates.y < -100))
        {
            direction = DOWN;
        }
        else if (( -128 < coordenates.x < -100) && ( -100 < coordenates.y < 100))
        {
            direction = LEFT_RAS;
        }
        else if (( 100 < coordenates.x < 127) && ( -100 < coordenates.y < 100))
        {
            direction = RIGHT_RAS;
        }
    }

    return direction;
}

/*SHOW_DISPLAY()
* Función encargada de ir actualizando la pantalla.
* Recibe: Una matriz con el tablero de juego.
* Devuelve: -
*/
void show_display(char matrix[][WIDTH_OF_BOARD])
{
    disp_clear();   //limpio display
    disp_update();

    dcoord_t position;

    for ( uint8_t i = 0; i <= DISP_MAX_Y; i++)
    {
        for ( uint8_t j = 3; j <= (DISP_MAX_X-3); j++)
        {
            position.x = j;
            position.y = i;
            if (j==3 || j==12)
            {
                disp_write(position, D_ON);
            }
            else if (matrix[i+1][j-2] != EMPTY)
            {
                disp_write(position, D_ON); 
            }
        }
        
    }
   
    disp_update();

    return ;
}

/*PAUSE()
* Función encargada de mostrar en la pantalla la "p" de pausa y esperar a
* que se presione el botón del joystick para continuar el juego.
* Recibe: -
* Devuelve: -
*/
void pause (void)
{
    //escribe una p en el display y espera al boton
}

/*PRINT_HIGHSCORE()
* Función encargada de mostrar en la pantalla "HI" indicando que
* se consiguió un nuevo highscore
* Recibe: -
* Devuelve: -
*/
void print_highscore(void)
{
    //escribir "HI" en el display y esperar al boton
}