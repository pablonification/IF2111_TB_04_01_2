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


int isLoggedIn = 0;
char currentUser[MAX_LEN];
boolean isConfigLoaded = FALSE;
boolean isGameStarted = FALSE;

int findUser(User *users, int user_count, const char *username, const char *password);

void Login(User *users, int user_count);

void Register(GameState *gameState);