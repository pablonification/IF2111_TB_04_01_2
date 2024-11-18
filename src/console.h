#ifndef CONSOLE_H
#define CONSOLE_H

#include "boolean.h"
#include <stddef.h> // Include this header for size_t
#include "mesinkata.h" //

// DEKLARASI FUNGSI DAN PROSEDUR WORDL3 
// Constants applied both in wordl3 and quantum wordl3
#define WORD_LENGTH 5   // Length of each word 
#define MAX_ATTEMPTS 5  // Maximum number of attempts
#define NUM_WORDS 4     // Number of words in Quantum Wordle

void evaluateGuess(const char *target, const char *guess, char *result); // applied both in wordl3 and quantum wordl3
int compareWords(const char *word1, const char *word2);
char *copy(char *dest, const char *src);
void playWordl3();

// DEKLARASI FUNGSI DAN PROSEDUR QUANTUM WORDL3 
#define MAX_ATTEMPTS_Q 9

size_t my_strlen(const char *str);
void my_strcpy(char *dest, const char *src);
int my_strcmp(const char *str1, const char *str2);
boolean allWordsGuessed(const char targets[NUM_WORDS][WORD_LENGTH + 1], const char guesses[NUM_WORDS][WORD_LENGTH + 1]);
void playQuantumWordl3();

// DEKLARASI PROSEDUR HELP
void Help(int x);

// DEKLARASI FUNGSI DAN PROSEDUR UNTUK WORK

typedef struct // DEKLARASI STRUCT WORK
{
    char workName[100]; //nama pekerjaan
    int workPayment;    //gaji
    int workDuration;   //durasi kerja
} Work;

#ifdef _WIN32
    #include <windows.h> // buat tes di windows
#else
    #include <unistd.h>  // spek tubes hrs bisa di linux
#endif

void portable_sleep(int milliseconds); // fungsi untuk sleep (delay durasi kerja)
void collectInput(char *input); // fungsi pengumpulan input

#endif // CONSOLE_H