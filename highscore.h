#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdbool.h>

#define NUMBER_OF_PLAYERS 5
#define CHARACTERS 3

typedef struct
{
	int highscores[NUMBER_OF_PLAYERS];
	char nameOfHighscores[NUMBER_OF_PLAYERS][CHARACTERS + 1];

}highscore_t;

bool getHighscore(highscore_t *highscore);
int checkIfHighscore(int score, highscore_t *highscore);
bool setHighscore(highscore_t* highscore, int score, char name[CHARACTERS]);

#endif
