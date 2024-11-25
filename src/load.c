#include <stdio.h>
#include <stdlib.h>
#include "load.h"

// Helper functions untuk manipulasi string
int stringLength(char *str) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

void stringCopy(char *dest, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void stringConcat(char *dest, char *src) {
    int destLen = stringLength(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[destLen + i] = src[i];
        i++;
    }
    dest[destLen + i] = '\0';
}

boolean stringEqual(char *str1, char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return FALSE;
        i++;
    }
    return str1[i] == str2[i];
}

// Helper function untuk mengkonversi Word ke integer
int wordToInt(Word word) {
    int result = 0;
    for (int i = 0; i < word.Length; i++) {
        if (word.TabWord[i] >= '0' && word.TabWord[i] <= '9') {
            result = result * 10 + (word.TabWord[i] - '0');
        }
    }
    return result;
}

// Helper function untuk mengekstrak nama dari Word
void wordToString(Word word, char *str) {
    int i;
    for (i = 0; i < word.TabWord; i++) {
        str[i] = word.TabWord[i];
    }
    str[i] = '\0';
}

boolean loadGameState(GameState *gameState, char *filename) {
    // Buat full path
    char fullPath[MAX_LEN];
    int i = 0;
    while (SAVE_FOLDER[i] != '\0') {
        fullPath[i] = SAVE_FOLDER[i];
        i++;
    }
    int j = 0;
    while (filename[j] != '\0') {
        fullPath[i + j] = filename[j];
        j++;
    }
    fullPath[i + j] = '\0';
    
    // Inisialisasi state awal
    CreateList(&gameState->itemList);
    CreateQueue(&gameState->requestQueue);
    gameState->userCount = 0;
    gameState->isInitialized = FALSE;

    // Mulai membaca file menggunakan Mesin Kata
    STARTWORD(fullPath);
    if (currentChar == MARK) {
        printf("Error: File kosong\n");
        return FALSE;
    }

    // Baca jumlah item
    int itemCount = wordToInt(currentWord);
    if (itemCount < 0 || itemCount > CAPACITY) {
        printf("Error: Jumlah item tidak valid\n");
        return FALSE;
    }

    // Baca setiap item
    for (int i = 0; i < itemCount; i++) {
        Barang item;
        
        // Baca harga
        ADVWORD();
        if (currentWord.TabWord == 0) {
            printf("Error: Format harga item tidak valid\n");
            return FALSE;
        }
        item.price = wordToInt(currentWord);

        // Baca nama
        ADVWORD();
        if (currentWord.TabWord == 0) {
            printf("Error: Format nama item tidak valid\n");
            return FALSE;
        }
        wordToString(currentWord, item.name);

        // Masukkan ke list
        insertLast(&gameState->itemList, item);
    }

    // Baca jumlah user
    ADVWORD();
    int userCount = wordToInt(currentWord);
    if (userCount < 0 || userCount > MAX_USERS) {
        printf("Error: Jumlah user tidak valid\n");
        return FALSE;
    }

    // Baca setiap user
    for (int i = 0; i < userCount; i++) {
        User user;

        // Baca uang
        ADVWORD();
        if (currentWord.TabWord == 0) {
            printf("Error: Format uang user tidak valid\n");
            return FALSE;
        }
        user.money = wordToInt(currentWord);

        // Baca username
        ADVWORD();
        if (currentWord.TabWord == 0) {
            printf("Error: Format username tidak valid\n");
            return FALSE;
        }
        wordToString(currentWord, user.name);

        // Baca password
        ADVWORD();
        if (currentWord.TabWord == 0) {
            printf("Error: Format password tidak valid\n");
            return FALSE;
        }
        wordToString(currentWord, user.password);

        // Tambahkan user ke array
        gameState->users[gameState->userCount++] = user;
    }

    // Tutup file
    CLOSE();
    
    gameState->isInitialized = TRUE;
    printf("File konfigurasi aplikasi berhasil dibaca. PURRMART berhasil dijalankan.\n");
    return TRUE;
}

void getFullSavePath(char *filename, char *fullPath) {
    int i = 0;
    while (SAVE_FOLDER[i] != '\0') {
        fullPath[i] = SAVE_FOLDER[i];
        i++;
    }
    int j = 0;
    while (filename[j] != '\0') {
        fullPath[i + j] = filename[j];
        j++;
    }
    fullPath[i + j] = '\0';
}