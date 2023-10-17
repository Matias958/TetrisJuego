#include "reglas.h"

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
            break;

        case 'w': 
            Girar_Pieza(pieza, matris);
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

    *puntaje += borrarFila(matris);

    return false;
}
