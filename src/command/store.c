#include <stdio.h>
#include "store.h"
#include "../ADT/mesinkata.h"
#include "../ADT/mesinkarakter.h"

void storelist () {
   
    printf(" _____ _____ ___________ _____ _     _____ _____ _____ \n");
    printf("/  ___|_   _|  _  | ___ \\  ___| |   |_   _/  ___|_   _|\n");
    printf("\\ `--.  | | | | | | |_/ / |__ | |     | | '\\ `--.  | | \n");
    printf(" `--. \\ | | | | | |    /|  __|| |     | |  `--. \\ | |  \n");
    printf("/\\_/ / | | \\ \\_/ / |\\ \\| |___| |_____| |_/\\__/ / | |  \n");
    printf("\\____/  \\_/  \\___/\\_| \\_\\____/\\_____/\\___/\\____/  \\_/\n");


    printf("List barang yang ada di toko: \n");
    
    STARTWORDFILE("config.txt");
    // if (IsEmpty(itemList)) {
    //     printf("TOKO KOSONG");
    // }
    // else { 
        printf("- ");
        printf("%s", currentWord);
    // }   
    printf("\n");
    // }
}


    // item itemList[] = {
    // {20, "AK47"},
    // {20, "Lalabu"},
    // {10, "Ayam Goreng Crisbar"}
    // };

    // int itemCount = sizeof(itemList) / sizeof(itemList[0]);
    
void request (List *L, Queue *Q) {
    char req;
    char val;
    boolean found = 0;

    printf("Nama barang yang diminta: ");
    scanWord(&req);
    printf("\n");

    for (int i = 0; i < itemCount; i++) {
        if (isEmpty(*Q) && Search(*L,req)) {
            printf("Barang dengan nama yang sama sudah ada di toko\n");
        }
        else if (isEmpty(*Q) && !Search(*L,req)) {
            enqueue(Q, req);
        }
        else if (!isEmpty(*Q) && !Search(*L,req)) {
            while(!isEmpty(*Q) && !found) {
                dequeue(Q, &val);
                if (val == req) {
                    enqueue(Q, val);
                    found = 1;
                }
                else {
                    enqueue(Q, val);
                }
                
            }

            if (found) {
                printf("Barang dengan nama yang sama sudah ada di antrian\n");
            }
            else {
                enqueue(Q, req);
            }
        }
    }
}

void remove(List L) {
    char item_name[100];
    printf("Nama barang yang akan dihapus: ");
    scanWord(&item_name);

    
    boolean found = 0;
    int i = 0;

    while (!IsEmpty(L) || found) {
        if (item_name == L.A[i]) {
            found = 1;
        }
        else {
            found = 0;
        }
    }

    if (found) {
        printf("%s telah berhasil dihapus.\n", item_name);
    }
    else {
        pritnf("Toko tidak menjual %s.", item_name);
    }
}

int main() {
    // List itemList[] = {
    // {20, "AK47"},
    // {20, "Lalabu"},
    // {10, "Ayam Goreng Crisbar"}
    // };

    storelist();
    return 0;
}