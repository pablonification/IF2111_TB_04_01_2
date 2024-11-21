#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ADT/boolean.h"
#include "ADT/mesinkarakter.h"
#include "ADT/mesinkata.h"

#define WORD_LENGTH 5
#define MAX_ATTEMPTSQ 9
#define TOTAL_WORDS 4

char board[MAX_ATTEMPTSQ][WORD_LENGTH * 3 + 1];

void evaluateGuess(const char *target, Word guess, char *result) {
    int matched[WORD_LENGTH] = {0}; 
    int used[WORD_LENGTH] = {0};    

    for (int i = 0; i < WORD_LENGTH; i++) {
        result[i * 3] = guess.TabWord[i];
        result[i * 3 + 1] = '%'; 
        result[i * 3 + 2] = ' ';
    }
    result[WORD_LENGTH * 3] = '\0'; 

    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess.TabWord[i] == target[i]) {
            result[i * 3 + 1] = ' '; 
            matched[i] = 1;         
            used[i] = 1;            
        }
    }

    // Second pass: Mark wrong-position matches
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result[i * 3 + 1] == '%') { 
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!matched[j] && !used[j] && guess.TabWord[i] == target[j]) {
                    result[i * 3 + 1] = '*'; 
                    used[j] = 1;            
                    break;
                }
            }
        }
    }
}


boolean isValidGuess(Word guess) {
    return (guess.Length == WORD_LENGTH);
}

boolean compareWords(const char *word1, const char *word2) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (word1[i] != word2[i]) {
            return FALSE; // Words are not equal
        }
    }
    return TRUE; // Words are equal
}

void playQuantumWordl3() {
    char **wordsList = calloc(100, sizeof(char *));
    int wordCount = 0;
    char buffer[6];
    FILE *wordsFile = fopen("words.txt", "r");

    if (!wordsFile) {
        printf("Error: Unable to open words file.\n");
        free(wordsList);
        exit(1);
    }

    // Load words into wordsList
    while (fscanf(wordsFile, "%5s", buffer) != EOF) {
        wordsList[wordCount] = malloc(6 * sizeof(char));
        for (int i = 0; i < WORD_LENGTH; i++) {
            wordsList[wordCount][i] = buffer[i];
        }
        wordsList[wordCount][WORD_LENGTH] = '\0'; 
        wordCount++;
    }
    fclose(wordsFile);

    // Pick four unique target words
    srand(time(NULL));
    char *answers[TOTAL_WORDS];
    for (int i = 0; i < TOTAL_WORDS; i++) {
        boolean isUnique;
        do {
            isUnique = TRUE;
            answers[i] = wordsList[rand() % wordCount];
            for (int j = 0; j < i; j++) {
                if (compareWords(answers[i], answers[j])) {
                    isUnique = FALSE;
                    break;
                }
            }
        } while (!isUnique);
    }

    // Initialize game board
    char board[TOTAL_WORDS][MAX_ATTEMPTSQ][WORD_LENGTH * 3 + 1];
    for (int w = 0; w < TOTAL_WORDS; w++) {
        for (int i = 0; i < MAX_ATTEMPTSQ; i++) {
            for (int j = 0; j < WORD_LENGTH * 3; j += 3) {
                board[w][i][j] = '_';
                board[w][i][j + 1] = ' ';
                board[w][i][j + 2] = ' ';
            }
            board[w][i][WORD_LENGTH * 3] = '\0'; // Null-terminate each row
        }
    }

    int attempts = 0;
    boolean win = FALSE;
    Word guesses[TOTAL_WORDS];

    printf("WELCOME TO QUANTUM W0RDL3! GUESS 4 WORDS SIMULTANEOUSLY. YOU HAVE %d CHANCES.\n", MAX_ATTEMPTSQ);

    while (attempts < MAX_ATTEMPTSQ && !win) {
        // Display the game board
        for (int w = 0; w < TOTAL_WORDS; w++) {
            printf("Word %d:\n", w + 1);
            for (int i = 0; i < MAX_ATTEMPTSQ; i++) {
                printf("%s\n", board[w][i]);
            }
        }

        // Prompt the user for guesses
        for (int w = 0; w < TOTAL_WORDS; w++) {
            printf("Masukkan kata tebakan Anda untuk Word %d: ", w + 1);
            do {
                STARTLINE();
                guesses[w] = currentWord;

                if (guesses[w].Length != WORD_LENGTH) {
                    printf("Invalid input! Please enter a %d-letter word: ", WORD_LENGTH);
                }
            } while (guesses[w].Length != WORD_LENGTH);
        }

        // Evaluate the guesses and update the boards
        boolean allCorrect = TRUE;
        for (int w = 0; w < TOTAL_WORDS; w++) {
            char result[WORD_LENGTH * 3 + 1] = {0}; // Clear the result buffer
            evaluateGuess(answers[w], guesses[w], result);
            for (int i = 0; i < WORD_LENGTH * 3 + 1; i++) {
                board[w][attempts][i] = result[i];
            }

            // Check if the word is correctly guessed
            if (!compareWords(answers[w], guesses[w].TabWord)) {
                allCorrect = FALSE;
            }
        }

        // Check if all words are guessed correctly
        if (allCorrect) {
            win = TRUE;
        }

        attempts++;
    }

    // Final display of the game board
    for (int w = 0; w < TOTAL_WORDS; w++) {
        printf("Word %d:\n", w + 1);
        for (int i = 0; i < MAX_ATTEMPTSQ; i++) {
            printf("%s\n", board[w][i]);
        }
    }

    // Display the end message
    if (win) {
        printf("Selamat, Anda menang! +10000 rupiah telah ditambahkan ke akun Anda.\n");
    } else {
        printf("Boo! Anda kalah. Jawaban yang benar adalah:\n");
        for (int w = 0; w < TOTAL_WORDS; w++) {
            printf("Word %d: %s\n", w + 1, answers[w]);
        }
    }

    free(wordsList);
}

int main() {
    playQuantumWordl3();
    return 0;
}