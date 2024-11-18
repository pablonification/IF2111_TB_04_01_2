#include <stdio.h>
#include "ADT/mesinkata.h"
#include "misc.h"
#include "ADT/boolean.h"

void scanWord(Word *inputWord) {
/* Membaca input dari pengguna menggunakan mesin kata.
   I.S. : sembarang
   F.S. : inputWord berisi kata yang dibaca dari pengguna */
    STARTWORD();           // Memulai pembacaan kata
    *inputWord = currentWord; // Salin kata yang dibaca ke parameter output
}

int convertWordToInt(Word inputWord) {
/* Mengonversi Word ke integer.
   I.S. : inputWord berupa angka dalam bentuk Word
   F.S. : Nilai integer dikembalikan */
    return WordToInt(inputWord);
}

boolean isWordEqual(Word W1, Word W2) {
/* Membandingkan dua Word, apakah sama.
   I.S. : W1 dan W2 sembarang
   F.S. : Mengembalikan TRUE jika W1 sama dengan W2 */
    return isKataEqual(W1, W2);
}

void displayWordWithNewline(Word W) {
/* Menampilkan Word ke layar diikuti newline.
   I.S. : Word sembarang
   F.S. : Isi Word ditampilkan ke layar dengan newline */
    displayWord(W, TRUE);
}
