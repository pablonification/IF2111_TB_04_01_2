#include <stdio.h>
#include "store.h"
#include "../ADT/mesinkata.h"
#include "../ADT/mesinkarakter.h"

void storeList (ListBarang L, Queue Q) {
   
    printf(" _____ _____ ___________ _____ _     _____ _____ _____ \n");
    printf("/  ___|_   _|  _  | ___ \\  ___| |   |_   _/  ___|_   _|\n");
    printf("\\ `--.  | | | | | | |_/ / |__ | |     | | '\\ `--.  | | \n");
    printf(" `--. \\ | | | | | |    /|  __|| |     | |  `--. \\ | |  \n");
    printf("/\\_/ / | | \\ \\_/ / |\\ \\| |___| |_____| |_/\\__/ / | |  \n");
    printf("\\____/  \\_/  \\___/\\_| \\_\\____/\\_____/\\___/\\____/  \\_/\n");


    printf("List barang yang ada di toko: \n");
    
    if (IsEmpty(L)) {
        printf("TOKO KOSONG");
    }
    else { 
        for (int i  = 0; i < Length(L); i ++) {
            printf("- ");
            printf("%s", L.item[i]);
        }
    // }   
    printf("\n");
    // }
    }
}
  // int itemCount = sizeof(itemList) / sizeof(itemList[0]);
  
void storeRequest (ListBarang *L, Queue *Q) {
    char req;
    char val;
    boolean found = 0;

    printf("Nama barang yang diminta: ");
    scanWord(&req);
    printf("\n");

    for (int i = 0; i < Length(*L); i++) {
        if (isEmpty(*Q) && Search(*L,req)) {
            printf("Barang dengan nama yang sama sudah ada di toko\n");
        }
        else if (isEmpty(*Q) && !Search(*L,req)) {
            enqueue(Q, req);
        }
        else if (!isEmpty(*Q) && !Search(*L,req)) {
            for (int i = 0; i < length(*Q); i++) { // gmn kalo pake for sepanjang length queue biar ga ngubah urutan antrian
                dequeue(Q, &val);           // jadi semuanya kedequeue enqueue
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

void storeRemove(ListBarang L) {
    char item_name[100];
    printf("Nama barang yang akan dihapus: ");
    scanWord(&item_name);

    
    boolean found = 0;
    int i = 0;

    while (!IsEmpty(L) || found) {
        if (item_name == L.item[i]) {
            found = 1;
        }
        else {
            found = 0;
        }
        i++;
    }

    if (found) {
        printf("%s telah berhasil dihapus.\n", item_name);
    }
    else {
        pritnf("Toko tidak menjual %s.", item_name);
    }
}

void storeSupply(List *L, Queue *Q) { //asumsi L adalah list ber-Eltype Barang. tapi jadi beda sih sama implementasinya veli nanti tolong bahas lagi:'(
    char item_name[50];
    dequeue(&Q, &item_name);
    printf("Apakah kamu ingin menambahkan barang %s ke toko? (Terima/Tunda/Tolak: ", item_name);

    char response[10];
    scanWord(&response);

    if (mystrcmp(response, "Terima") == 0) {
        int price;
        printf("Harga barang: ");
        scanWord(&price); // ini harusnya scanInt tapi belum ada hehe
        Barang new_item = {item_name, price};

        InsertLast(L, new_item);
        printf("%s dengan harga %d telah ditambahkan ke toko.\n", item_name, price);
    }
    else if (mystrcmp(response, "Tunda") == 0) {
        enqueue(Q, item_name);
        printf("%s dikembalikan ke antrian.\n", item_name);
    }
    else if (mystrcmp(response, "Tolak") == 0) {
        printf("%s dihapus dari antrian.\n", item_name);
    }
    else{
        printf("Input tidak valid.\n"); // kembali ke menu
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