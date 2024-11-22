/*
isEmpty harus buat lagi

terus fungsi aymar juga ada yg harus dibuat lagi insertLast
*/

#include <stdio.h>
#include "store.h"
#include "../misc.h"
#include "../ADT/mesinkata.h"
#include "../ADT/mesinkarakter.h"

void storeList (ListItem *L) {
    // List L;
    printf(" _____ _____ ___________ _____ _     _____ _____ _____ \n");
    printf("/  ___|_   _|  _  | ___ \\  ___| |   |_   _/  ___|_   _|\n");
    printf("\\ `--.  | | | | | | |_/ / |__ | |     | | '\\ `--.  | | \n");
    printf(" `--. \\ | | | | | |    /|  __|| |     | |  `--. \\ | |  \n");
    printf("/\\_/ / | | \\ \\_/ / |\\ \\| |___| |_____| |_/\\__/ / | |  \n");
    printf("\\____/  \\_/  \\___/\\_| \\_\\____/\\_____/\\___/\\____/  \\_/\n");


    printf("List barang yang ada di toko: \n");
    
    if (IsEmptyItem(L)) {
        printf("TOKO KOSONG");
    }
    else { 
        for (int i  = 0; i < L->itemLength; i ++) {
            printf("- ");
            printf("%s", L->item[i]);
        }
    // }   
    printf("\n");
    // }
    }
}
  // int itemCount = sizeof(itemList) / sizeof(itemList[0]);
  
void storeRequest (ListItem *L, QueueItem *Q) {
    Word req;
    char val;
    boolean found = 0;
    char reqstr;

    printf("Nama barang yang diminta: ");
    scanWord(&req);
    wordToString(req, &reqstr);
    printf("\n");

    for (int i = 0; i < L->itemLength; i++) {
        if (isEmptyItem(*Q) && SearchItem(*L,reqstr)) {
            printf("Barang dengan nama yang sama sudah ada di toko\n");
        }
        else if (isEmptyItem(*Q) && !SearchItem(*L,reqstr)) {
            enqueueItem(Q, &reqstr);
        }
        else if (!isEmptyItem(*Q) && !SearchItem(*L,reqstr)) {
            for (int i = 0; i < lengthQueueItem(*Q); i++) { // gmn kalo pake for sepanjang length queue biar ga ngubah urutan antrian
                dequeueItem(Q, &reqstr);           // jadi semuanya kedequeue enqueue
                if (val == reqstr) {
                    enqueueItem(Q, &reqstr);
                    found = 1;
                }
                else {
                    enqueueItem(Q, &reqstr);
                }   
            }

            if (found) {
                printf("Barang dengan nama yang sama sudah ada di antrian\n");
            }
            else {
                enqueueItem(Q, &reqstr);
            }
        }
    }
}

void storeRemove(ListItem *L) {
    Word item_name;
    printf("Nama barang yang akan dihapus: ");
    scanWord(&item_name);
    char item_namestr;
    wordToString(item_name, &item_namestr);

    
    boolean found = 0;
    int i = 0;

    while (!IsEmptyItem(L) && !found) {
        if (customStringCMP(&item_namestr, (*L).item[i].name) == 0) {
            found = 1;
        }
        i++;
    }

    if (found) {
        DeleteAtItem(L, i-1);
        printf("%s telah berhasil dihapus.\n", item_name);
    }
    else {
        printf("Toko tidak menjual %s.", item_name);
    }
}

void storeSupply(ListItem *L, QueueItem *Q) { 
    char item_name[50];
    dequeueItem(Q, item_name);
    printf("Apakah kamu ingin menambahkan barang %s ke toko? (Terima/Tunda/Tolak: ", item_name);

    Word response;
    scanWord(&response);
    char responsestr;
    wordToString(response, &responsestr);
    boolean inputValid = FALSE;

    while (!inputValid) {
        if (customStringCMP(&responsestr, "Terima") == 0 || customStringCMP(&responsestr, "Tunda") == 0 || customStringCMP(&responsestr, "Tolak") == 0) {
            inputValid = TRUE;
        }
        else {
            printf("Input tidak valid. Silakan coba lagi: ");
            scanWord(&response);
        }
    }

    if (customStringCMP(&responsestr, "Terima") == 0) {
        Word price;
        printf("Harga barang: ");
        scanWord(&price);
        convertWordToInt(price);
        Item new_item;
        customStringCPY(new_item.name, item_name);
        new_item.price = convertWordToInt(price);

        insertLastItem(L, new_item);
        printf("%s dengan harga %d telah ditambahkan ke toko.\n", item_name, convertWordToInt(price));
    }
    else if (customStringCMP(&responsestr, "Tunda") == 0) {
        enqueueItem(Q, item_name);
        printf("%s dikembalikan ke antrian.\n", item_name);
    }
    else if (customStringCMP(&responsestr, "Tolak") == 0) {
        printf("%s dihapus dari antrian.\n", item_name);
    }
}

boolean IsEmptyItem(ListItem *L) {
    return L->itemLength == 0;
}

void DeleteAtItem(ListItem *L, IdxType i) {
	int j = LastIdxItem(*L);
	while (i <= j) {
		(*L).item[i] = (*L).item[i+1];
        i++;
	}
}

IdxType LastIdxItem(ListItem L) {
	int i = 0;
	while ((i < MaxEl) && (L.item[i+1].name != '\0')) {
		i += 1;
	}
	return i;
}

boolean SearchItem(ListItem L, char X) {
	int i = 0;
	int j = LastIdxItem(L);
	boolean found = FALSE;
	while ((i <= j) && !found) {
		if (customStringCMP(L.item[i].name, &X) == 0) {
			found = TRUE;
		}
		i += 1;
	}
    return found;
}

int main() {
    ListItem itemList[] = {
    {"AK47", 20},
    {"Lalabu", 20},
    {"Ayam Goreng Crisbar", 10}
    };

    QueueItem requestQueue;
    CreateQueueItem(&requestQueue);

    storeList(itemList);
    storeRequest(itemList, &requestQueue);
    storeRemove(itemList);
    storeSupply(itemList, &requestQueue);
    return 0;
}
