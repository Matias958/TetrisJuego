#include <stdlib.h>
#include <stdio.h>

#include "highscore.h"

bool getHighscore(highscore_t *highscore)
{

	FILE *highscoreFile;
	highscoreFile = fopen("highscore.txt", "r"); //abro un puntero al archivo

	if (highscoreFile == NULL)
	{
		printf("No pudo abrir el archivo: highscore\n");
		return false;
	}

	char buffer[100];
	fgets(buffer, 100, highscoreFile); // guardo el archivo en un buffer

	int c = 0;
	int i;
	for (i = 0; i < NUMBER_OF_PLAYERS; i++, c++)
	{
		// NOMBRE DEL JUGADOR
		int j = 0;
		for (j = 0; j < CHARACTERS; j++)
		{
			highscore->nameOfHighscores[i][j] = buffer[c++]; //guardo el nombre en la estructura 
		}
		highscore->nameOfHighscores[i][3] = '\0';

		// PUNTAJE DEL JUGADOR
		char number[20];
		for (j = 0; buffer[c] != ','; j++)
		{
			number[j] = buffer[c++];   
		}
		number[j] = '\0';

		highscore->highscores[i] = atoi(number); //guardo el puntaje como int en la estructura
	}

	fclose(highscoreFile); //cierro el archivo
	return true;
}

int checkIfHighscore(int score, highscore_t *highscore)
{
	int i;
	for (i = 0; i <= NUMBER_OF_PLAYERS && highscore->highscores[i] >= score; i++);

	return i + 1;
}

bool setHighscore(highscore_t *highscore, int score, char name[CHARACTERS])
{
	// buscamos la posici�n que le corresponde
	int pos;
	for (pos = 0; highscore->highscores[pos] > score; pos++)
		;

	int tempHighScore = highscore->highscores[pos];
	char tempHighScoreName[CHARACTERS];

	// guardamos los datos de la que se encontraba alli
	int i;
	for (i = 0; i < CHARACTERS; i++)
	{
		tempHighScoreName[i] = highscore->nameOfHighscores[pos][i];
	}

	// guardamos el nuevo highscore en su posici�n
	highscore->highscores[pos] = score;
	for (i = 0; i < CHARACTERS; i++)
	{
		highscore->nameOfHighscores[pos][i] = name[i];
	}

	// movemos el resto
	for (i = pos + 1; i < NUMBER_OF_PLAYERS; i++)
	{
		int j;
		highscore->highscores[i] = tempHighScore;
		for (j = 0; j < CHARACTERS; j++)
		{
			highscore->nameOfHighscores[i][j] = tempHighScoreName[j];
		}

		// si quedan elementos por mover, guardamos el siguiente
		if ((i + 1) < NUMBER_OF_PLAYERS)
		{

			for (j = 0; j < CHARACTERS; j++)
			{
				tempHighScore = highscore->highscores[i + 1];
				tempHighScoreName[j] = highscore->nameOfHighscores[i + 1][j];
			}
		}
	}

	FILE *highscoreFile;
	highscoreFile = fopen("highscore.txt", "w"); //abro el archivo como escritura

	if (highscoreFile == NULL)
	{
		printf("No pudo abrir el archivo: highscore\n");
		return false;
	}

	char buffer[100];
	int c = 0;
	for (i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		int j;
		for (j = 0; j < CHARACTERS; j++)
		{
			buffer[c++] = highscore->nameOfHighscores[i][j]; //cargo los nombres en un buffer
		}

		char number[20];
		snprintf(number, sizeof(number), "%d", highscore->highscores[i]); //comvierto el puntaje en string

		for (j = 0; number[j] != '\0'; j++)
		{
			buffer[c++] = number[j];
		}

		buffer[c++] = ',';
	}

	buffer[c] = '\0';

	fprintf(highscoreFile, "%s", buffer); //guardo los nombres y puntaje en el archivo

	fclose(highscoreFile);
	return true;
}