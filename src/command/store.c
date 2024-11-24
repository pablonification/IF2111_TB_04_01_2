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
    if (IsEmptyItem(L)) {
        printf("TOKO KOSONG\n");
    }
    else { 
        printf("List barang yang ada di toko: \n");
        for (int i  = 0; i < L->itemLength; i ++) {
            printf("");
            printf("%d. %s\n", i + 1, L->item[i].name);
        }
    // }   
    printf("\n");
    // }
    }
}
  // int itemCount = sizeof(itemList) / sizeof(itemList[0]);
  
void storeRequest(ListItem *L, QueueItem *Q) {
    Word req;
    char reqstr[MaxEl]; // Ensure sufficient size
    boolean found = FALSE;

    printf("Nama barang yang diminta: ");
    STARTLINE();
    req = currentWord;
    wordToString(req, reqstr); // Convert Word to string

    boolean isFoundInList = SearchItem(*L, reqstr);
    if (isFoundInList) {
        printf("Barang dengan nama yang sama sudah ada di toko\n");
    } else if (isEmptyItem(*Q)) {
        enqueueItem(Q, reqstr);
    } else {
        boolean foundInQueue = FALSE;
        int queueLength = lengthQueueItem(*Q);

        for (int i = 0; i < queueLength; i++) {
            char temp[MaxEl];
            dequeueItem(Q, temp); // Dequeue an item to temp
            if (customStringCMP(temp, reqstr) == 0) {
                foundInQueue = TRUE;
            }
            enqueueItem(Q, temp); // Re-enqueue the item
        }

        if (foundInQueue) {
            printf("Barang dengan nama yang sama sudah ada di antrian\n");
        } else {
            enqueueItem(Q, reqstr);
        }
    }
}

void storeRemove(ListItem *L) {
    Word item_name;
    printf("Nama barang yang akan dihapus: ");
    STARTLINE();
    item_name = currentWord;
    
    char item_namestr[50];
    wordToString(item_name, item_namestr);

    
    boolean found = 0;
    int i = 0;

    while (i < L->itemLength && !found) {
        if (customStringCMP(item_namestr, (*L).item[i].name) == 0) {
            found = 1;
        }
        i++;
    }

    if (found) {
        DeleteAtItem(L, i-1);
        printf("%s telah berhasil dihapus.\n", item_namestr);
    }
    else {
        printf("Toko tidak menjual %s.\n", item_namestr);
    }
}

void storeSupply(ListItem *L, QueueItem *Q) { 
    char item_name[50];
    dequeueItem(Q, item_name);
    printf("Apakah kamu ingin menambahkan barang %s ke toko? (Terima/Tunda/Tolak): ", item_name);

    Word response;
    STARTLINE();
    char responsestr;
    response = currentWord;
    wordToString(response, &responsestr);
    boolean inputValid = FALSE;

    while (!inputValid) {
        if (customStringCMP(&responsestr, "Terima") == 0 || customStringCMP(&responsestr, "Tunda") == 0 || customStringCMP(&responsestr, "Tolak") == 0) {
            inputValid = TRUE;
        }
        else {
            printf("Input tidak valid. Silakan coba lagi: ");
            scanWord(&response);
            wordToString(response, &responsestr);
        }
    }

    if (customStringCMP(&responsestr, "Terima") == 0) {
        Word price;
        printf("Harga barang: ");
        scanWord(&price);
        int priceint = convertWordToInt(price);
        Item new_item;
        customStringCPY(new_item.name, item_name);
        new_item.price = priceint;

        insertLastItem(L, new_item);
        printf("%s dengan harga %d telah ditambahkan ke toko.\n", item_name, priceint);
    }
    else if (customStringCMP(&responsestr, "Tunda") == 0) {
        printf("%s dikembalikan ke antrian.\n", item_name);
        enqueueItem(Q, item_name);
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
	while (i < j) {
		(*L).item[i] = (*L).item[i+1];
        i++;
	}
    (*L).itemLength -= 1;
}

IdxType LastIdxItem(ListItem L) {
	int i = 0;
	while ((i < MaxEl) && (L.item[i+1].name != '\0')) {
		i += 1;
	}
	return i;
}

boolean SearchItem(ListItem L, char *X) {
	int i = 0;
    
	int j = L.itemLength;
    printf("%d\n", j);
	boolean found = FALSE;
	while ((i < L.itemLength) && !found) {
		if (customStringCMP(L.item[i].name, X) == 0) {
			found = TRUE;
            // i++;
		}
		i += 1;
	}
    return found;
}

// int main() {
//     ListItem itemList = {
//         .item = {
//         {"AK47", 20},
//         {"Lalabu", 20},
//         {"Ayam Goreng Crisbar", 10},
//         {"Kunjaw UAS Alstrukdat", 50}
//         },
//         .itemLength = 4
//     };

//     QueueItem requestQueue;
//     CreateQueueItem(&requestQueue);

//     storeList(&itemList);
//     storeRequest(&itemList, &requestQueue);
//     storeRequest(&itemList, &requestQueue);
//     storeRequest(&itemList, &requestQueue);
//     storeSupply(&itemList, &requestQueue);
//     storeSupply(&itemList, &requestQueue);
//     storeSupply(&itemList, &requestQueue);
//     storeRemove(&itemList);
//     storeList(&itemList);
//     return 0;
// }
