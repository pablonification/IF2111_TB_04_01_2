#include <stdio.h>
#include "list.h"

int main () {
    List l1 = MakeList();

    if (IsEmpty(l1)) {
        printf("List kosong.\n");
    }
    else {
        printf("List tidak kosong.\n");
    }

    InsertFirst(&l1, 100);
    InsertLast(&l1, 300);
    InsertAt(&
    l1, 200, 1);

    printf("%d\n", Length(l1));

    List l2 = MakeList();

    InsertFirst(&l2, 1);
    InsertLast(&l2, 3);
    InsertAt(&l2, 2, 1);

    List l3 = Concat(l1,l2);

    for (int i = 0; i < Length(l3); i++) {
        printf("%d ", l3.A[i]);
    }
    printf("\n");

    DeleteLast(&l3);

    printf("%d\n", Length(l3));

    if (Search(l3, 300)) {
        printf("Angka ditemukan.\n");
    }


    // ListItem itemList = {
    //     .item = {
    //     {"AK47", 20},
    //     {"Lalabu", 20},
    //     {"Ayam Goreng Crisbar", 10},
    //     {"Kunjaw UAS Alstrukdat", 50}
    //     },
    //     .itemLength = 4
    // };

    // if (IsEmptyItem(&itemList)) {
    //     printf("Kosong\n");
    // }
    // else {
    //     printf("Tidak kosong\n");
    // }

    // printf("%d/n", LastIdxItem(itemList));
    // DeleteAtItem(&itemList, 2);
    
    // if (SearchItem(itemList, "Ayam Goreng Crisbar")) {
    //     printf("Ditemukan\n");
    // }
    // else {
    //     printf("Tidak ditemukan\n");
    // }
    // return 0;
}

// gcc -o list list.c