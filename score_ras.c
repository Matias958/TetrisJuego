/* TP FINAL PROGRAMACIÓN I - 2023|1C - TETRIS
 *Titulo: score_ras.c
 *Descripcion: manejo funciones para mostrar los scores
 *             en el display de la raspberry
 *Autores: Facundo Torres
 *         Julieta Libertad Rodriguez
 *         Matias Minitti
 *         Ramiro Nieto Abascal
 */

/*HEADERS*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "joydrv.h"
#include "disdrv.h"
#include "raspberry.h"
#include "score_ras.h"

/*MACROS*/
enum highscore_state
{
    NAME,
    SCORE
};

/*PROTOTIPOS*/

/* nameRas()
 * Función encargada de permitirle al usuario guardar su apodo (de 3 letras) para el highscore.
 * Recibe: puntero a arreglo de 3 char donde va a ir el apodo
 * Devuelve: -
 *
 * Nota: Arriba avanza una letra en el abecedario, abajo retrocede una letra en el abecedario.
 * Derecha e izquierda cambia la letra que se esta modificando. Termina cuando se presiona el botón.
 */
void nameRas(char name[CHARACTERS]);

/*CÓDIGO*/

/*scoreRas()
 * Función encargada de manejar las funciones de puntaje en la raspberry una vez finalizada la partida.
 * Recibe: un int con el puntaje y un puntero a highscore_t con el highscore
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 */
bool scoreRas(int score, highscore_t *highscore)
{
    disp_clear(); // apaga el display por completo
    disp_update();

    int position = checkIfHighscore(score, highscore); // analiza si el puntaje pertenece al highscore
    if (position <= NUMBER_OF_PLAYERS)                 // en caso de ser cierto imprime "HI" y el numero de posicion
    {
        printCharacter('H', 0, 0);
        printCharacter('S', 9, 0);

        if (position >= 10)
        {
            if (!printNum((position / 10), 0, 8))
            {
                return false;
            }
            if (!printNum((position % 10), 9, 8))
            {
                return false;
            }
        }
        else
        {
            if (!printNum(position, 0, 8))
            {
                return false;
            }
        }

        disp_update();
        wait(2);
    }

    if (!printScore(score)) // imprime el puntaje
    {
        return false;
    }

    char direction = WAIT; // espero a que toquen el boton para dejar de ver el puntaje
    while (direction != BUTTON)
    {
        joystick(&direction);
    }

    disp_clear(); // apaga el display por completo
    disp_update();

    if (position <= NUMBER_OF_PLAYERS) // si pertenece al highscore lo deja anotarse en el mismo
    {
        char name[3];
        nameRas(name);

        if (!setHighscore(highscore, score, name))
        {
            return false;
        }

        wait(1);
        disp_clear();
        disp_update();
    }

    return true;
}

/* nameRas()
 * Función encargada de permitirle al usuario guardar su apodo (de 3 letras) para el highscore.
 * Recibe: puntero a arreglo de 3 char donde va a ir el apodo
 * Devuelve: -
 *
 * Nota: Arriba avanza una letra en el abecedario, abajo retrocede una letra en el abecedario.
 * Derecha e izquierda cambia la letra que se esta modificando. Termina cuando se presiona el botón.
 */
void nameRas(char name[CHARACTERS])
{
    disp_clear(); // apaga el display por completo
    disp_update();

    name[0] = 'A'; // inicializa arreglo
    name[1] = 'A';
    name[2] = 'A';
    char direction = WAIT;
    int i = 0;

    while (direction != BUTTON) // espera a que se seleccione nombre
    {
        while (!joystick(&direction))
            ;

        if (direction == UP) // cambia la letra
        {
            if (name[i] != 'Z')
            {
                name[i]++;
            }
            else
            {
                name[i] = 'A';
            }
        }
        else if (direction == DOWN)
        {
            if (name[i] != 'A')
            {
                name[i]--;
            }
            else
            {
                name[i] = 'Z';
            }
        }
        else if (direction == RIGHT_RAS && i != 2) // cambia la el espacio que se esta modificando
        {
            i++;
        }
        else if (direction == LEFT_RAS && i != 0)
        {
            i--;
        }

        disp_clear();
        printCharacter(name[0], 0, 0); // muestra como se va actualizando el nombre en el display
        printCharacter(name[1], 5, 0);
        printCharacter(name[2], 10, 0);
        disp_update();
    }

    wait(2); // espera 2 seg
    disp_clear();
    disp_update();
}

/*printCharacter()
 * Función encargada de imprimir un caracter en la pantalla. (No borra el display)
 * Recibe: un char con la letra, un int con el corrimiento en x y otro en y
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 *
 * Nota: Sólo imprime letras mayúsculas y número del 0-9.
 */
bool printCharacter(char letter, int i, int j)
{
    bool end = true;
    if (letter >= 'A' && letter <= 'Z') // si es una letra
    {
        switch (letter)
        {
        case 'A':
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 5 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 5 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 5 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 7 + j}, D_ON);
            break;
        case 'B':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            break;
        case 'C':
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            break;
        case 'D':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            break;
        case 'E':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            break;
        case 'F':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);

            break;
        case 'G':
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            break;
        case 'H':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 7 + j}, D_ON);
            break;
        case 'I':
            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);
            break;
        case 'J':
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            break;
        case 'K':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 5 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 7 + j}, D_ON);
            break;
        case 'L':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            break;
        case 'M':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 2 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 3 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 2 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 7 + j}, D_ON);
            break;
        case 'N':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 3 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 5 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 7 + j}, D_ON);
            break;
        case 'O':
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            break;
        case 'P':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            break;
        case 'Q':
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 7 + j}, D_ON);
            break;
        case 'R':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 5 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 7 + j}, D_ON);
            break;
        case 'S':
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            break;
        case 'T':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
            break;
        case 'U':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            break;
        case 'V':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            break;
        case 'W':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 6 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            break;
        case 'X':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 5 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 5 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 7 + j}, D_ON);
            break;
        case 'Y':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 3 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 4 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
            break;
        case 'Z':
            disp_write((dcoord_t){0 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 6 + j}, D_ON);
            disp_write((dcoord_t){0 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 5 + j}, D_ON);
            disp_write((dcoord_t){1 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){2 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 4 + j}, D_ON);
            disp_write((dcoord_t){2 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){3 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 3 + j}, D_ON);
            disp_write((dcoord_t){3 + i, 7 + j}, D_ON);

            disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 2 + j}, D_ON);
            disp_write((dcoord_t){4 + i, 7 + j}, D_ON);
            break;
        default:
            end = false;
            break;
        }
    }
    else // si es un número
    {
        end = printNum(letter - '0', i, 1 + j);
    }
    disp_update();
    return end;
}

/*printScore()
 * Función encargada de imprimir un puntaje en la pantalla.
 * Recibe: un int con el puntaje
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 * 
 * Nota: Se considera que el puntaje es un numero entero de cuatro cifras.
 */
bool printScore(int score)
{
    disp_clear(); // apaga el display por completo
    disp_update();

    int first = score / 1000; // recupero los digitos del puntaje
    int second = (score / 100) % 10;
    int third = (score / 10) % 10;
    int fourth = score % 10;

    if (!printNum(first, 0, 0))
    {
        return false;
    }
    if (!printNum(second, 9, 0))
    {
        return false;
    }
    if (!printNum(third, 0, 9))
    {
        return false;
    }
    if (!printNum(fourth, 9, 9))
    {
        return false;
    }

    disp_update();

    return true;
}

/*printNum()
 * Función encargada de imprimir un numero (del 0-9) en la pantalla. (No borra el display)
 * Recibe: un int con el numero, uno con el corrimiento en x y otro en y
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 */
bool printNum(int num, int i, int j)
{
    switch (num)
    {
    case 0:
        disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 5 + j}, D_ON);

        disp_write((dcoord_t){2 + i, 6 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 0 + j}, D_ON);

        disp_write((dcoord_t){3 + i, 6 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 0 + j}, D_ON);

        disp_write((dcoord_t){4 + i, 6 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 0 + j}, D_ON);

        disp_write((dcoord_t){5 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 5 + j}, D_ON);

        break;
    case 1:
        disp_write((dcoord_t){1 + i, 6 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 2 + j}, D_ON);

        disp_write((dcoord_t){2 + i, 6 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 1 + j}, D_ON);

        disp_write((dcoord_t){3 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 5 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){4 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){5 + i, 6 + j}, D_ON);
        break;
    case 2:
        disp_write((dcoord_t){1 + i, 6 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 1 + j}, D_ON);

        disp_write((dcoord_t){2 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 5 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){3 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){4 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){5 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 6 + j}, D_ON);

        break;
    case 3:
        disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 5 + j}, D_ON);

        disp_write((dcoord_t){2 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){3 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){4 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){5 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 5 + j}, D_ON);

        break;
    case 4:
        disp_write((dcoord_t){1 + i, 4 + j}, D_ON);

        disp_write((dcoord_t){2 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 4 + j}, D_ON);

        disp_write((dcoord_t){3 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 4 + j}, D_ON);

        disp_write((dcoord_t){4 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 4 + j}, D_ON);

        disp_write((dcoord_t){5 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 5 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 6 + j}, D_ON);

        break;
    case 5:
        disp_write((dcoord_t){1 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){2 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){3 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){4 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){5 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 5 + j}, D_ON);

        break;
    case 6:
        disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 5 + j}, D_ON);

        disp_write((dcoord_t){2 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){3 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){4 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){5 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 5 + j}, D_ON);

        break;
    case 7:
        disp_write((dcoord_t){1 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){2 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 5 + j}, D_ON);

        disp_write((dcoord_t){3 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 4 + j}, D_ON);

        disp_write((dcoord_t){4 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 2 + j}, D_ON);

        break;
    case 8:
        disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 5 + j}, D_ON);

        disp_write((dcoord_t){2 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){3 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){4 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){5 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 5 + j}, D_ON);

        break;
    case 9:
        disp_write((dcoord_t){1 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){1 + i, 2 + j}, D_ON);

        disp_write((dcoord_t){2 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){2 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){3 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){3 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){4 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){4 + i, 6 + j}, D_ON);

        disp_write((dcoord_t){5 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 3 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 5 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 6 + j}, D_ON);
        break;
    default:
        return false;
        break;
    }

    disp_update();
    return true;
}

/*showHighScores()
 * Función encargada de mostrar los highscores actuales.
 * Recibe: un puntero a highscore_t con el highscore y uno a window_state_t con el estado de la ventana
 * Devuelve: -
 * 
 * Nota: Muestra el puesto y el nombre de los jugadores, al mover a la derecha muestra el puntaje de dicho
 * jugador y a la izquierda vuelve a los nombres. Moviendo hacia arriba o hacia abajo (estando en los 
 * puntajes o los nombres), muestra los datos de los otros jugadores. Moviendo hacia la izquierda estando
 * en la pantalla de los nombres, vuelve al menú.
 */
void showHighScores(highscore_t *highscore, window_state_t *state)
{

    disp_clear(); //apaga display
    disp_update();

    int i, pos = 0, winState = NAME;
    char direction;
    bool draw = true;
    joystick(&direction);

    while (*state != GAME_SEL)
    {
        if (direction == DOWN) //analizo movimiento joystick
        {
            pos++;
            pos %= NUMBER_OF_PLAYERS;
            draw = true;
        }
        else if (direction == UP)
        {
            pos--;
            if (pos < 0)
            {
                pos = NUMBER_OF_PLAYERS - 1;
            }
            draw = true;
        }

        else if (direction == RIGHT_RAS)
        {
            if (winState == NAME)
            {
                winState = SCORE;
                draw = true;
            }
        }

        else if (direction == LEFT_RAS)
        {
            if (winState == NAME)
            {
                *state = GAME_SEL;
            }
            else
            {
                winState = NAME;
                draw = true;
            }
        }

        if (draw)
        {
            if (winState == NAME)
            {
                disp_clear();
                printNum(pos + 1, 0, 0); //muestro posicion en el highscore
                for (i = 0; i < CHARACTERS; i++)
                {
                    printCharacter(highscore->nameOfHighscores[pos][i], i * 5, 8); //muestro nombres
                }
                disp_update();
            }
            else
            {
                disp_clear();
                printScore(highscore->highscores[pos]); //muestro puntajes
            }

            draw = false;
        }
        while (!joystick(&direction))
            ;
    }

    disp_clear();
    disp_update();
    wait(1);
}
