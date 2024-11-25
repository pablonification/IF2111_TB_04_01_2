#ifndef MAIN_H
#define MAIN_H

#include "src/ADT/boolean.h"
#include "src/ADT/queue.h"
#include "src/ADT/list.h"
#include "src/ADT/mesinkarakter.h"
#include "src/misc.h"
#include "src/wordl32.h"
#include "src/rng.h"
#include "src/qwordl3.h"
#include "src/bonus2.h"

#define MAX_LEN 50
#define MAX_USERS 100

extern char currentUser[MAX_LEN];

typedef struct{
    char name[MAX_LEN];
    char password[MAX_LEN];
    int money;
} User;

typedef struct{
    char name[MAX_LEN];
    int price;
} Item;

typedef struct {
    Item item[MaxEl];
    int itemLength;
} ListItem;

typedef struct {
    ListItem itemList;
    User users[MAX_LEN];
    int userCount;
    QueueItem requestQueue;
    boolean isStarted;
    boolean isLoaded;
    boolean isLogin;
} GameState;

// typedef struct{
//     char workName[100]; // nama pekerjaan
//     int workPayment;    // gaji
//     int workDuration;   // durasi kerja
// } Work;

void showMainMenu();
boolean Start(GameState *gameState);
void Load(const char *filename, GameState *gameState);
boolean loadGameState(GameState *gameState, const char *filename);
void Login(User *users, int user_count);
int findUser(User *users, int user_count, const char *username, const char *password);
void Register(GameState *gameState);
void Save(const char *filename, GameState *gameState);
void Logout(User *users, int user_count);
int customStringCMP(const char *str1, const char *str2);
void customStringCPY(char *dest, const char *src);
void insertLastItem(ListItem *itemlist, Item item);
void makeListItem(GameState *gameState);

void printLoad(GameState *gameState);

// work
void delay(int seconds);

void collectInput(char *input);

void work(int *balance);

// store
void storeList (ListItem *L);
// I.S List bisa saja kosong
// F.S Jika list kosong, mencetak "TOKO KOSONG"
// Jika list tidak kosong, mencetak seluruh barang yang ada di toko

void storeRemove(ListItem *L);

void storeRequest (ListItem *L, QueueItem *Q);

void storeSupply(ListItem *L, QueueItem *Q);

boolean IsEmptyItem(ListItem *L);

void DeleteAtItem(ListItem *L, IdxType i);

IdxType LastIdxItem(ListItem L);

boolean SearchItem(ListItem L, char *X);

boolean isWordInt(Word w);

#endif