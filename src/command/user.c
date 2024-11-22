#include <stdio.h>
#include "user.h"

int findUser(User *users, int user_count, const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (customStringCMP(users[i].name, username) == 0 && 
            customStringCMP(users[i].password, password) == 0) { 
            return i;
        }
    }
    return -1;
}

void Login(User *users, int user_count) {
    if(isLoggedIn) {
        printf("Anda masih tercatat sebagai %s. Silahkan LOGOUT terlebih dahulu.\n", currentUser);
        return;
    }

    char username[MAX_LEN];
    char password[MAX_LEN];
    
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    int userIndex = findUser(users, user_count, username, password);
    
    if(userIndex != -1) {
        customStringCPY(currentUser, users[userIndex].name);
        isLoggedIn = TRUE;
        printf("Anda telah berhasil login sebagai %s.\n", currentUser);
    }
    else {
        printf("Username atau password salah. Silakan coba lagi.\n");
    }
}

void Register(GameState *gameState) {
    char username[MAX_LEN], password[MAX_LEN];
    
    printf("Username: ");
    scanf("%s", username);
    
    for (int i = 0; i < gameState->userCount; i++) {
        if (customStringCMP(gameState->users[i].name, username) == 0) {
            printf("Username %s sudah terdaftar. Silakan gunakan username lain.\n", username);
            return;
        }
    }
    
    printf("Password: ");
    scanf("%s", password);

    if (gameState->userCount >= MAX_USERS) {
        printf("Maksimum jumlah pengguna telah tercapai.\n");
        return;
    }

    customStringCPY(gameState->users[gameState->userCount].name, username);
    customStringCPY(gameState->users[gameState->userCount].password, password);
    gameState->users[gameState->userCount].money = 0;
    gameState->userCount++;

    printf("Akun dengan username %s telah berhasil dibuat.\n", username);
    printf("Silakan LOGIN untuk melanjutkan.\n");
}