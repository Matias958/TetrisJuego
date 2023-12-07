/*headers*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "joydrv.h"
#include "disdrv.h"
#include "raspberry.h"
#include "score_ras.h"

/*prototipos*/

/*NAME_RAS()
 * Función encargada de permitirle al usuario guardar su apodo (de 3 letras) para el highscore.
 * Arriba avanza una letra en el abecedario, abajo retrocede una letra en el abecedario.
 * Derecha e izquierda cambia la letra que se esta modificando.
 * Tambien va mostrando los cambios que hace en la pantalla.
 * Termina cuando se presiona el botón.
 * Recibe: puntero a arreglo de 3 char donde va a ir el apodo
 * Devuelve: -
 */
void name_ras(char name[CHARACTERS]);

/*PRINT_SCORE()
 * Función encargada de imprimir el puntaje en la pantalla.
 * Se considera que el puntaje es un numero entero de cuatro cifras.
 * Recibe: un int con el puntaje
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 */
bool print_score(int score);

/*codigo*/

/*SCORE_RAS()
 * Función encargada de manejar las funciones de puntaje en la raspberry
 * Recibe: un int con el puntaje y un puntero a highscore_t con el highscore
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 */
bool score_ras(int score, highscore_t *highscore)
{
    disp_clear(); // apaga el display por completo
    disp_update();

    int position = checkIfHighscore(score, highscore); // analiza si el puntaje pertenece al highscore
    if (position <= NUMBER_OF_PLAYERS)                 // en caso de ser cierto imprime "HI" y el numero de posicion
    {
        print_letter('H', 0, 0);
        print_letter('S', 9, 0);
        
        if (position >= 10)
        {
            if (!print_num((position / 10), 0, 8))
            {
                return false;
            }
            if (!print_num((position % 10), 9, 8))
            {
                return false;
            }
        }
        else
        {
            if (!print_num(position, 0, 8))
            {
                return false;
            }
        }

        disp_update();
        wait(2);
    }

    if (!print_score(score)) // imprime el puntaje
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
        name_ras(name);

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

/*NAME_RAS()
 * Función encargada de permitirle al usuario guardar su apodo (de 3 letras) para el highscore.
 * Arriba avanza una letra en el abecedario, abajo retrocede una letra en el abecedario.
 * Derecha e izquierda cambia la letra que se esta modificando.
 * Tambien va mostrando los cambios que hace en la pantalla.
 * Termina cuando se presiona el botón.
 * Recibe: puntero a arreglo de 3 char donde va a ir el apodo
 * Devuelve: -
 */
void name_ras(char name[CHARACTERS])
{
    disp_clear(); // apaga el display por completo
    disp_update();

    name[0] = 'A';
    name[1] = 'A';
    name[2] = 'A';
    char direction = WAIT;
    int i = 0;

    while (direction != BUTTON)
    {
        while (!joystick(&direction));

        if (direction == UP)
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
        else if (direction == RIGHT_RAS && i != 2)
        {
            i++;
        }
        else if (direction == LEFT_RAS && i != 0)
        {
            i--;
        }

        disp_clear();
        print_letter(name[0], 0, 0);
        print_letter(name[1], 5, 0);
        print_letter(name[2], 10, 0);
        disp_update();
    }
    wait(2);
    disp_clear();
    disp_update();
}

/*PRINT_LETTER()
 * Función encargada de imprimir una letra en la pantalla. (No borra el display)
 * Recibe: un char con la letra, un int con el corrimiento en x y otro en y
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 */
bool print_letter(char letter, int i, int j)
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
        return false;
        break;
    }

    disp_update();
    return true;
}

/*PRINT_SCORE()
 * Función encargada de imprimir el puntaje en la pantalla.
 * Se considera que el puntaje es un numero entero de cuatro cifras.
 * Recibe: un int con el puntaje
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 */
bool print_score(int score)
{
    disp_clear(); // apaga el display por completo
    disp_update();

    int first = score / 1000; // recupero los digitos del puntaje
    int second = (score / 100) % 10;
    int third = (score / 10) % 10;
    int fourth = score % 10;

    if (!print_num(first, 0, 0))
    {
        return false;
    }
    if (!print_num(second, 9, 0))
    {
        return false;
    }
    if (!print_num(third, 0, 9))
    {
        return false;
    }
    if (!print_num(fourth, 9, 9))
    {
        return false;
    }

    disp_update();

    return true;
}

/*PRINT_NUM()
 * Función encargada de imprimir un numero en la pantalla. (No borra el display)
 * Recibe: un int con el numero, uno con el corrimiento en x y otro en y
 * Devuelve: un bool que indica que todo funcionó correctamente (true) o no (false)
 */
bool print_num(int num, int i, int j)
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
        disp_write((dcoord_t){2 + i, 4 + j}, D_ON);

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

        disp_write((dcoord_t){5 + i, 0 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 1 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 2 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 4 + j}, D_ON);
        disp_write((dcoord_t){5 + i, 5 + j}, D_ON);
        break;
    default:
        return false;
        break;
    }

    disp_update();
    return true;
}