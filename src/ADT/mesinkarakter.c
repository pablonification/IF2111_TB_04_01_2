#include <stdio.h>
#include <stdlib.h>
#include "mesinkarakter.h"

char currentChar;
boolean EOP;
static FILE *pita = NULL;
static int retval;

void RESETPITA() {
/* Mengembalikan state awal pita (kosong tanpa inputan) supaya pita dapat 
   digunakan kembali tanpa overflow dari pita input sebelumnya.
   I.S. : sembarang
   F.S. : pita kosong (NULL) */
    // KAMUS LOKAL

    // ALGORITMA
    if (pita != NULL) rewind(pita);
}

void STARTFILE(char* file_name, boolean *success) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Pita yang akan diambil adalah pita yang berada di dalam file
   pada path ../data/file_name.
   Pita baca diambil dari fopen(path).
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (FALSE)
          Jika currentChar = MARK maka EOP akan menyala (TRUE) */
    // KAMUS LOKAL
    static char path[150] = "../data/";
    int i=0, len = 8;

    RESETPITA();

    // ALGORITMA
    while (*file_name != '\0') {
        path[i+len] = *file_name;
        file_name++;
        i++;
    } path[i+len] = '\0';

    //printf("k = %s", path);
    pita = fopen(path,"r");
    if (pita != NULL) {
        *success = TRUE;
        ADV();
    } else {
        *success = FALSE;
    }
}

void START() {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   Pita baca diambil dari stdin. Sebelum pembacaan, pita akan 
   dikembalikan ke state awal.
   I.S. : sembarang
   F.S. : currentChar adalah karakter pertama pada pita
          Jika currentChar != MARK maka EOP akan padam (FALSE)
          Jika currentChar = MARK maka EOP akan menyala (TRUE) */
    // KAMUS LOKAL

    // ALGORITMA
    RESETPITA();

    pita = stdin;
    ADV();
}

void ADV() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = currentChar, currentChar != MARK
   F.S. : currentChar adalah karakter berikutnya dari currentChar yang lama,
          currentChar mungkin = MARK
          Jika  currentChar = MARK maka EOP akan menyala (TRUE) */
    // KAMUS LOKAL

    // ALGORITMA
    retval = fscanf(pita, "%c", &currentChar);
    EOP = (currentChar == MARK);
}