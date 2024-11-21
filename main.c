#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// Variabel Global
int isLoggedIn = 0;
char currentUser[MAX_LEN];
boolean isConfigLoaded = FALSE;
boolean isGameStarted = FALSE;

// Fungsi
int main(){
    showMainMenu();
    return 0;
}
void showMainMenu(){
    char command[MAX_LEN];
    static GameState gameState = {0};
    gameState.isInitialized = FALSE; 

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

    printf("Selamat datang di PURRMART!\nTolong masukkan command yang valid (START, LOAD <filename>, REGISTER, LOGIN, HELP, atau QUIT.)\n");

     while (1) {
        printf(">> ");
        scanf("%s", command);

        if (customStringCMP(command, "START") == 0) {
            if (isGameStarted) {
                printf("Game sudah dijalankan sebelumnya.\n");
                continue;
            }
            if (Start("savefile.txt")) {
                isGameStarted = TRUE;
                gameState.isInitialized = TRUE;
                printf("PURRMART berhasil dijalankan.\n");
            }
        }
        else if (customStringCMP(command, "LOAD") == 0) {
            if (!isGameStarted) {
                printf("Anda harus START terlebih dahulu.\n");
                continue;
            }
            
            char filename[MAX_LEN];
            scanf("%s", filename);
            Load(filename, &gameState); // Passing pointer
            if (gameState.isInitialized) {
                isConfigLoaded = TRUE;
            }
        }
        else if (customStringCMP(command, "LOGIN") == 0) {
            if (!isConfigLoaded) {
                printf("Anda harus LOAD file konfigurasi terlebih dahulu.\n");
                continue;
            }
            Login(gameState.users, gameState.userCount);
        }else if (customStringCMP(command, "REGISTER") == 0) {
            if (!isConfigLoaded) {
                printf("Anda harus LOAD file konfigurasi terlebih dahulu.\n");
                continue;
            }
            Register(&gameState);
        }else if (customStringCMP(command, "SAVE") == 0) {
            char filename[MAX_LEN];
            printf("Masukkan nama file untuk menyimpan: ");
            scanf("%s", filename);
            Save(filename, &gameState);
        }else if (customStringCMP(command, "HELP") == 0) {
            printf("Commands: START, LOAD <filename>, SAVE <filename> LOGIN, REGISTER, HELP, QUIT\n");
        }else if (customStringCMP(command, "QUIT") == 0) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Unknown command. Type HELP for a list of commands.\n");
        }
    }
}

boolean Start(const char *filename) {
    char filepath[100];
    customStringCPY(filepath, "data/");
    stringConcat(filepath, filename);
    
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        printf("Save file ditemukan dan dibaca.\n");
        fclose(file);
        return TRUE;
    } else {
        printf("Save file tidak ditemukan. PURRMART gagal dijalankan.\n");
        return FALSE;
    }
}


void Load(const char *filename, GameState *gameState) {
    if (filename == NULL || *filename == '\0') {
        printf("Nama file tidak valid.\n");
        return;
    }

    char filepath[100];
    customStringCPY(filepath, "data/");
    stringConcat(filepath, filename);
    
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Save file tidak ditemukan. PURRMART gagal dijalankan.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    
    if (size == 0) {
        printf("Error: File kosong\n");
        fclose(file);
        return;
    }

    if (!loadGameState(gameState, filename)) {
        printf("Kesalahan dalam memuat file konfigurasi. PURRMART gagal dijalankan.\n");
        fclose(file);
        return;
    }
    
    fclose(file);
    // testGameState(gameState);
    printf("File konfigurasi berhasil diload. PURRMART siap digunakan.\n");
}


boolean loadGameState(GameState *gameState, const char *filename) {
    char filepath[100];
    customStringCPY(filepath, "data/");
    stringConcat(filepath, filename);
    
    FILE *file = fopen(filepath, "r");
    if (file == NULL) return FALSE;

    makeListItem(gameState);

    int itemCount;
    if (fscanf(file, "%d", &itemCount) != 1) {
        fclose(file);
        return FALSE;
    }

    for (int i = 0; i < itemCount; i++) {
        int price;
        char name[MAX_LEN];
        
        if (fscanf(file, "%d %[^\n]", &price, name) != 2) {
            fclose(file);
            return FALSE;
        }
        
        gameState->itemList.item[i].price = price;
        customStringCPY(gameState->itemList.item[i].name, name);
        gameState->itemList.jumlahItem++;
    }

    int userCount;
    if (fscanf(file, "%d", &userCount) != 1) {
        fclose(file);
        return FALSE;
    }

    for (int i = 0; i < userCount; i++) {
        int money;
        char username[MAX_LEN], password[MAX_LEN];
        
        if (fscanf(file, "%d %s %s", &money, username, password) != 3) {
            fclose(file);
            return FALSE;
        }
        
        gameState->users[i].money = money;
        customStringCPY(gameState->users[i].name, username);
        customStringCPY(gameState->users[i].password, password);
        gameState->userCount++;
    }

    gameState->isInitialized = TRUE;
    fclose(file);
    return TRUE;
}

int findUser(User *users, int user_count, const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (customStringCMP(users[i].name, username) == 0 && 
            customStringCMP(users[i].password, password) == 0) {  // Tambahkan == 0
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
        printf("Error: Maksimum jumlah pengguna telah tercapai.\n");
        return;
    }

    customStringCPY(gameState->users[gameState->userCount].name, username);
    customStringCPY(gameState->users[gameState->userCount].password, password);
    gameState->users[gameState->userCount].money = 0;
    gameState->userCount++;

    printf("Akun dengan username %s telah berhasil dibuat.\n", username);
    printf("Silakan LOGIN untuk melanjutkan.\n");
}

void Save(const char *filename, GameState *gameState) {
    if (!isGameStarted || !isConfigLoaded) {
        printf("Anda harus memulai game dan load file konfigurasi terlebih dahulu.\n");
        return;
    }

    if (filename == NULL || *filename == '\0') {
        printf("Nama file tidak valid.\n");
        return;
    }

    char filepath[100];
    customStringCPY(filepath, "data/");
    stringConcat(filepath, filename);
    
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Gagal membuat file save.\n");
        return;
    }

    // Format penulisan mengikuti format config.txt:
    // <jumlah_item>
    // <harga> <nama_item>
    // <jumlah_user>
    // <saldo> <username> <password>

    fprintf(file, "%d\n", gameState->itemList.jumlahItem);

    for (int i = 0; i < gameState->itemList.jumlahItem; i++) {
        fprintf(file, "%d %s\n", 
            gameState->itemList.item[i].price,
            gameState->itemList.item[i].name);
    }

    fprintf(file, "%d\n", gameState->userCount);

    // Tulis users
    for (int i = 0; i < gameState->userCount; i++) {
        fprintf(file, "%d %s %s\n",
            gameState->users[i].money,
            gameState->users[i].name,
            gameState->users[i].password);
    }

    fclose(file);
    printf("Game berhasil disimpan dalam %s.\n", filepath);
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


void insertLastItem(ListItem *itemlist, Barang item){
    if (itemlist->jumlahItem < MaxEl) {
        itemlist->item[itemlist->jumlahItem] = item;
        itemlist->jumlahItem++;
    } else {
        printf("Item sudah penuh. Tidak bisa menambahkan item %s\n", item.name);
    }
}

void makeListItem(GameState *gameState) {
    gameState->itemList.jumlahItem = 0;  
    for (int i = 0; i < MaxEl; i++) {
        gameState->itemList.item[i].price = 0;
        gameState->itemList.item[i].name[0] = '\0';
    }
    
    gameState->userCount = 0;
    for (int i = 0; i < MAX_USERS; i++) {
        gameState->users[i].money = 0;
        gameState->users[i].name[0] = '\0';
        gameState->users[i].password[0] = '\0';
    }
}

// void testGameState(GameState *gameState) {
//     printf("\n=== Testing Game State ===\n");
    
//     printf("\nDaftar Item (%d item):\n", gameState->itemList.jumlahItem);
//     if (gameState->itemList.jumlahItem == 0) {
//         printf("Tidak ada item.\n");
//     } else {
//         for (int i = 0; i < gameState->itemList.jumlahItem; i++) {
//             printf("%d. %s (Harga: %d)\n", 
//                    i + 1, 
//                    gameState->itemList.item[i].name, 
//                    gameState->itemList.item[i].price);
//         }
//     }
    
//     printf("\nDaftar User (%d user):\n", gameState->userCount);
//     if (gameState->userCount == 0) {
//         printf("Tidak ada user terdaftar.\n");
//     } else {
//         for (int i = 0; i < gameState->userCount; i++) {
//             printf("%d. Username: %s, Password: %s, Saldo: %d\n", 
//                    i + 1, 
//                    gameState->users[i].name, 
//                    gameState->users[i].password, 
//                    gameState->users[i].money);
//         }
//     }

//     printf("\nStatus Inisialisasi: %s\n", 
//            gameState->isInitialized ? "Sudah Terinisialisasi" : "Belum Terinisialisasi");
// }