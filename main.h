#define MAX_LEN 50
#define MAX_USERS 100

typedef struct{
    char name[MAX_LEN];
    char password[MAX_LEN];
    int money;
} User;

typedef struct{
    char name[MAX_LEN];
    int price;
} Barang;