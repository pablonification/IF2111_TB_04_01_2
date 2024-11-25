// load.h
#ifndef LOAD_H
#define LOAD_H

#include "../ADT/boolean.h"
#include "../ADT/list.h"
#include "../ADT/mesinkata.h"
#include "../ADT/queue.h"
#include "main.h"

#define MAX_USERS 50
#define MAX_LEN 50
#define SAVE_FOLDER "data/"

typedef struct {
    char name[MAX_LEN];
    char password[MAX_LEN];
    int money;
} User;

typedef struct {
    List itemList;               
    User users[MAX_USERS];       
    int userCount;               
    Queue requestQueue;          
    boolean isInitialized;
} GameState;



boolean loadGameState(GameState *gameState, char *filename);
void getFullSavePath(char *filename, char *fullPath);

#endif