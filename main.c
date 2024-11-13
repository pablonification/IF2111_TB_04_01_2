#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void showMainMenu();
void start();
void load(const char *filename);
void login(User *users, int user_count);
int findUser(User *users, int user_count, const char *username, const char *password);
int customStringCMP(const char *str1, const char *str2);
void customStringCPY(char *dest, const char *src);

// Variabel Global
int isLoggedIn = 0;
char currentUser[MAX_LEN];

// Fungsi
int main(){
    showMainMenu();
    return 0;
}

void showMainMenu(){
    char command[MAX_LEN];
    printf("                                                                                           \n"
        "                                                                                           \n"
        "_________   _...._                               __  __   ___                              \n"
        "\\        |.'      '-.                           |  |/  `.'   `.                            \n"
        " \\        .'```'.    '.         .-,.--. .-,.--. |   .-.  .-.   '          .-,.--.      .|  \n"
        "  \\      |       \\     \\        |  .-. ||  .-. ||  |  |  |  |  |    __    |  .-. |   .' |_ \n"
        "   |     |        |    |_    _  | |  | || |  | ||  |  |  |  |  | .:--.'.  | |  | | .'     |\n"
        "   |      \\      /    .| '  / | | |  | || |  | ||  |  |  |  |  |/ |   \\ | | |  | |'--.  .-'\n"
        "   |     |\\`'-.-'   .'.' | .' | | |  '- | |  '- |  |  |  |  |  |`\" __ | | | |  '-    |  |  \n"
        "   |     | '-....-'`  /  | /  | | |     | |     |__|  |__|  |__| .'.''| | | |        |  |  \n"
        "  .'     '.          |   `'.  | | |     | |                     / /   | |_| |        |  '.'\n"
        "'-----------'        '   .'|  '/|_|     |_|                     \\ \\._,\\ '/|_|        |   / \n"
        "                      `-'  `--'                                  `--'  \"            `'-'   \n");

    printf("Selamat datang di PURRMART!\nTolong masukkan command yang valid (START, LOAD <filename>, HELP, atau Quit.)\n");

    while(1){
        printf(">> ");
        scanf("%s", command);

        if (customStringCMP(command, "START") == 0){
            start();
        }
        else if (customStringCMP(command, "LOAD") == 0){
            char filename[MAX_LEN];
            scanf("%s", filename);
            load(filename);
        }
        else if (customStringCMP(command, "HELP") == 0){
            printf("Commands yang tersedia:\n");
            printf("START - ...\n");
            printf("LOAD - ...\n");
            printf("LOGIN - ...\n");
            printf("QUIT - ...\n");
            printf("Pastikan command diketik dalam huruf kapital!\n");
        }
        else if (customStringCMP(command, "QUIT") == 0){
            printf("Exitting PURRMART. Goodbye!\n");
            break;
        }
        else{
            printf("Command tidak ada. Ketik HELP untuk melihat list commands.\n");
        }
    }
}

void start(){
    printf("File konfigurasi PURRMART berhasil dibaca. PURRMART akan dijalankan sesaat lagi..\n");
}

void load(const char *filename){
    if (customStringCMP(filename, "savefile.txt") == 0){
        printf("Save file valid. PURRMART akan dijalankan sesaat lagi..\n");
    }
    else {
        printf("Save file tidak valid. PURRMART gagal dijalankan.\n");
    }
}

void login(User *users, int user_count){
    if(isLoggedIn){
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
    if(userIndex != 1){
        customStringCPY(currentUser, users[userIndex].name);
        isLoggedIn = 1;
        printf("Anda telah berhasil login sebagai %s.\n", currentUser);
    }
    else{
        printf("Username atau password salah.\n");
    }

}

int findUser(User *users, int user_count, const char *username, const char *password){
    for (int i = 0; i < user_count ; i++){
        if(customStringCMP(users[i].name, username) == 0 && customStringCMP(users[i].password, password)){
            return i;
        }
    }
    return -1;
}

int customStringCMP(const char *str1, const char *str2){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i] != str2[i]){
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

void customStringCPY(char *dest, const char *src){
    int i = 0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

