#include "src/ADT/boolean.h"
#include "src/ADT/queue.h"
#include "src/ADT/list.h"
#include "src/ADT/mesinkarakter.h"
#include "src/misc.h"
#include "src/wordl32.h"
#include "src/rng.h"
#include "src/bonus2.h"
#include "src/qwordl3.h"

#define MAX_LEN 50
#define MAX_USERS 100

extern boolean isConfigLoaded;
extern boolean isGameStarted;

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
    Queue requestQueue;          
    boolean isInitialized;
    boolean isStateLoaded;
} GameState;

void showMainMenu();
boolean Start(GameState *gameState);
void Load(const char *filename, GameState *gameState);
void Login(User *users, int user_count);
int findUser(User *users, int user_count, const char *username, const char *password);
void Register(GameState *gameState);
void Save(const char *filename, GameState *gameState);
void Logout(User *users, int user_count);
int customStringCMP(const char *str1, const char *str2);
void customStringCPY(char *dest, const char *src);
void insertLastItem(ListItem *itemlist, Item item);
void makeListItem(GameState *gameState);
void testGameState(GameState *gameState);
