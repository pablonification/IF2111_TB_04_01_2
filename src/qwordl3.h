#ifndef QUANTUMWORDL3_H
#define QUANTUMWORDL3_H

#include "ADT/boolean.h"
#include "ADT/mesinkarakter.h"
#include "ADT/mesinkata.h"

#define WORD_LENGTH 5
#define MAX_ATTEMPTSQ 9
#define TOTAL_WORDS 4

extern char board[MAX_ATTEMPTSQ][WORD_LENGTH * 3 + 1];


void evaluateGuess(const char *target, Word guess, char *result);

boolean isValidGuess(Word guess);


boolean compareWords(const char *word1, const char *word2);

void playQuantumWordl3();

#endif 
