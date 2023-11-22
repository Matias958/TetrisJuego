#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "highscore.h"



bool get_highscore(int highscores [NUMBER_OF_PLAYERS], char nameOfHighscores [NUMBER_OF_PLAYERS][CHARACTERS + 1])
{
	FILE *highscoreFile;
	highscoreFile = fopen("highscore.txt", "w");

	if (highscoreFile != NULL)
	{
		printf("No pudo abrir el archivo: highscore\n");
		return false;
	}

	int i;
	for (i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		//recupera el nombre del jugador
		fgets(nameOfHighscores[i], 3, highscoreFile);
		nameOfHighscores[i][4] = '\0';
	}




}