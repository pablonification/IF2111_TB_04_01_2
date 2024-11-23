#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "src/misc.h"



/*
harusnya LOAD dulu baru START
CURRENT CONDITION : START DULU BARU LOAD

*/

boolean isLoggedIn = FALSE;
char currentUser[MAX_LEN];
boolean isConfigLoaded = FALSE;
boolean isGameStarted = FALSE;
boolean isStarted = FALSE;

// Fungsi
int main(){
    showMainMenu();
    return 0;
}
void showMainMenu(){
    
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
		Word command;
        scanWord(&command);

		if (compareWords("START", command, 5)){
            Start("savefile.txt");
        } 
        else if (compareWords("LOAD", command, 4)){
            Word filename;
            scanWord(&filename);
            char file[50];
            wordToString(filename, file);
            Load(file, &gameState);
        } 
        else if (compareWords("HELP", command, 4)){
            if (!isStarted){
                printf("START -> Untuk masuk sesi baru\n");
                printf("LOAD -> Untuk memulai sesi berdasarkan file konfigurasi\n");
                printf("QUIT -> Untuk keluar dari program\n");
            } else {
                if (!isLoggedIn){
                printf("=====[ Login Menu Help PURRMART]=====\n");
                printf("REGISTER -> Untuk melakukan pendaftaran akun baru\n");
                printf("LOGIN -> Untuk masuk ke dalam akun dan memulai sesi\n");
                printf("QUIT -> Untuk keluar dari program\n");   
                } else {
                    printf("=====[ Menu Help PURRMART]=====\n");
                    printf("WORK -> Untuk bekerja\n");
                    printf("WORK CHALLENGE -> Untuk mengerjakan challenge\n");
                    printf("STORE LIST -> Untuk melihat barang-barang di toko\n");
                    printf("STORE REQUEST -> Untuk meminta penambahan barang\n");
                    printf("STORE SUPPLY -> Untuk menambahkan barang dari permintaan\n");
                    printf("STORE REMOVE -> Untuk menghapus barang\n");
                    printf("LOGOUT -> Untuk keluar dari sesi\n");
                    printf("SAVE -> Untuk menyimpan state ke dalam file");
                    printf("QUIT -> Untuk keluar dari program\n");
                }
            }
        }
		else if (compareWords("LOGIN", command, 5)){
            Login(gameState.users, gameState.userCount);
        }
        else if (compareWords("LOGOUT", command, 6)){
            
        }
		else if (compareWords("REGISTER", command, 7)){
            Register(&gameState);
        }
		else if (compareWords("WORK", command, 4)){
            //Work(gameState.users.money); 
        }
 		else if (compareWords("WORK CHALLANGE", command, 14)){
            printf("Daftar challenge yang tersedia:\n");
            printf("1. Tebak Angka (biaya main=200)\n");
            printf("2. W0RDL399 (biaya main=500)\n");
            printf("3. QUANTUM W0RDL399 (biaya main=1000)\n");

            printf("Masukan challenge yang hendak dimainkan: ");
            STARTLINE();
            Word choice = currentWord;

            if (compareWords("1", choice, 1)){
                tebakAngkaRNG();
            }
            else if (compareWords("2", choice, 1)){
                playWordl3();
            }
            else if (compareWords("3", choice, 1)){
                playQuantumWordl3();
            }
        }
		else if (compareWords("STORE LIST", command, 10)){

        }
		else if (compareWords("STORE REQUEST", command, 13)){

        }
		else if (compareWords("STORE SUPPLY", command, 12)){

        }
		else if (compareWords("STORE REMOVE", command, 12)){

        }
		else if (compareWords("SAVE", command, 4)){
            //Save(filename,&gameState);
        }
        else if (compareWords("QUIT", command, 4)){

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
        isStarted = TRUE;
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
        printf("File kosong\n");
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
        gameState->itemList.itemLength++;
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

    fprintf(file, "%d\n", gameState->itemList.itemLength);

    for (int i = 0; i < gameState->itemList.itemLength; i++) {
        fprintf(file, "%d %s\n", 
            gameState->itemList.item[i].price,
            gameState->itemList.item[i].name);
    }

    fprintf(file, "%d\n", gameState->userCount);

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

void insertLastItem(ListItem *itemlist, Item item){
    if (itemlist->itemLength < MaxEl) {
        itemlist->item[itemlist->itemLength] = item;
        itemlist->itemLength++;
    } else {
        printf("Item sudah penuh. Tidak bisa menambahkan item %s\n", item.name);
    }
}

void makeListItem(GameState *gameState) {
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

/* buat ngetes hasil load-an tadi*/
// void testGameState(GameState *gameState) {
//     printf("\n=== Testing Game State ===\n");
    
//     if (gameState->itemList.jumlahItem == 0) {
//         printf("Tidak ada item.\n");
//     } else {
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