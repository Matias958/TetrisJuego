#include "reglas.h"

/*JUGARTETRIS()
* Función encargada de ir moviendo las piezas en base a los comandos enviados y llamar a las
* funciones necesarias para que se ejecute correctamente el juego.
* Recibe: Un char al movimiento que se realizo, una estructura bloque_t con la pieza con la 
* que se esta jugando; la matris de juego y un int con el puntaje actual.
* Devuelve: Un bool indicando si pudo hacer el movimiento correctamente o no.
*/
bool jugarTetris (char movimiento, bloque_t *pieza, char matris[][12], int *puntaje)
{
    switch(movimiento)
    {
        case 'd':
            Mover_Pieza ( pieza, DERECHA, matris);
            break;
        case 'a':
            Mover_Pieza ( pieza, IZQUIERDA, matris);
            break;
        case 's':
            bool flag_bajar = Bajar_Pieza(pieza, matris);
            //inicializarTiempo();
            if (flag_bajar == false)
            {
                char flag_estacionar = Estacionar (pieza, matris);
                if (flag_estacionar == BIEN)
                {
                    *pieza = Crear_Pieza();
                }
                else
                {
                    return true;
                }
            }
            break;

        case 'w': 
            Girar_Pieza(pieza, matris);
            break;

        case ' ': //baja hasta chocar
            flag_bajar = Bajar_Pieza(pieza, matris);
            while(flag_bajar)
            {
                flag_bajar = flag_bajar = Bajar_Pieza(pieza, matris);
            }
            char flag_estacionar = Estacionar (pieza, matris);
            if (flag_estacionar == BIEN)
            {
                *pieza = Crear_Pieza();
            }
            else
            {
                return true;
            }
            break;

        default:
            break;
    }
    
    if(tiempo_transcurrido( 1.0 /(1.0 + *puntaje/50000)))
    {
        bool flag = Bajar_Pieza(pieza, matris);
        if (flag == false)
        {
                char flag_estacionar = Estacionar (pieza, matris);     //temporal en realidad habria que darle un tiempo
                if (flag_estacionar == BIEN)
                {
                    *pieza = Crear_Pieza();
                }
                else 
                {
                    return true;
                }
        }
    }
    
    if (choque(matris, pieza) == MAL)
    {
        return true;
    }

    return false;
}


void crearTablero (char matris[][12])
{
    int i, cantidad = 5 + rand() % 4;
    for(i = 0; i < cantidad; i++)
    {
        bloque_t pieza = Crear_Pieza();
        pieza.fila = LARGO_TABLERO-6;
        while ( rand() % 7)
        {
            int movimiento = rand() % 100;

            if(!(movimiento % 7))
            {
                bool flag_bajar = Bajar_Pieza(&pieza, matris);
                if (flag_bajar == false)
                {
                    break;
                }
            }

            if(!(movimiento % 2))
            {
                Girar_Pieza(&pieza, matris);
            }

            if(!(movimiento % 3))
            {
                Mover_Pieza ( &pieza, DERECHA, matris);
            }

            if(!(movimiento % 5))
            {
                Mover_Pieza ( &pieza, IZQUIERDA, matris);
            }
        }
        Estacionar (&pieza, matris);
    }

}
