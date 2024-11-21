#include "src/ADT/boolean.h"
#include "src/ADT/queue.h"
#include "src/ADT/list.h"
#include "src/ADT/mesinkarakter.h"
#include "src/misc.h"

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
} Barang;

typedef struct {
    Barang item[MaxEl];
    int jumlahItem;
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
boolean Start(const char *filename);
void Load(const char *filename, GameState *gameState);
boolean loadGameState(GameState *gameState, const char *filename);
void Login(User *users, int user_count);
int findUser(User *users, int user_count, const char *username, const char *password);
void Register(GameState *gameState);
void Save(const char *filename, GameState *gameState);
int customStringCMP(const char *str1, const char *str2);
void customStringCPY(char *dest, const char *src);
void insertLastItem(ListItem *itemlist, Barang item);
void makeListItem(GameState *gameState);
// void testGameState(GameState *gameState);
