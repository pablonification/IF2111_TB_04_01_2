#include <stdio.h>
#include "mesinkata.h"
#include "mesinkarakter.h"
#include "boolean.h"

boolean EndWord;
Word currentWord;

void ResetCurrentWord() {
/* Mengembalikan currentWord ke state awal (kosong / length=0).
   I.S. : currentWord sembarang
   F.S. : currentWord kosong (memiliki length 0) */
    // KAMUS LOKAL

    // ALGORITMA
    currentWord.Length = 0;
}

void IgnoreBlanks() {
/* Mengabaikan satu atau beberapa BLANK.
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */
    // KAMUS LOKAL

    // ALGORITMA
    while (currentChar == BLANK) ADV();
}

void STARTWORD() {
/* Kata dibaca dengan prosedur START yang akan membaca dari input user.
   I.S. : currentChar sembarang
   F.S. : EndWord = TRUE, dan currentChar = MARK;
          atau EndWord = FALSE, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
    // KAMUS LOKAL

    // ALGORITMA
    ResetCurrentWord();
    START();
    IgnoreBlanks();
    if (currentChar == MARK) EndWord = TRUE;
    else {
        EndWord = FALSE;
        CopyWord();
    }
}

void ADVWORD() {
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, EndWord = TRUE.
   Proses : Akuisisi kata menggunakan procedure SalinWord */
    // KAMUS LOKAL

    // ALGORITMA
    ResetCurrentWord();
    IgnoreBlanks();
    if (currentChar == MARK) EndWord = TRUE;
    else {
        EndWord = FALSE;
        CopyWord();
        IgnoreBlanks();
    }
}

void CopyWord() {
/* Mengakuisisi kata, menyimpan dalam currentWord.
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
    // KAMUS LOKAL

    // ALGORITMA
    currentWord.Length = 0;
    while (currentChar != BLANK && currentChar != MARK) {
        if (currentWord.Length < NMax) { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = currentChar;
            ADV();
        } else
            break;
            }
}

void STARTWORDFILE(char* path) {
/* Kata dibaca dengan prosedur STARTFILE() yang akan membaca dari file pada path, 
   akuisisi kata menggunakan CopyWordWithBlanks.
   I.S. : currentChar sembarang
   F.S. : EndWord = TRUE, dan currentChar = MARK;
          atau EndWord = FALSE, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
    // KAMUS LOKAL
    boolean success;

    // ALGORITMA
    ResetCurrentWord();
    STARTFILE(path, &success);

    if (success) {
        if (currentChar == MARK) EndWord = TRUE;
        else {
            EndWord = FALSE;
            CopyWordWithBlanks();
        }
    }
}

void ADVWORDFILE() {
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, EndWord = TRUE.
   Proses : Akuisisi kata menggunakan procedure CopyWordWithBlanks */
    // KAMUS LOKAL

    // ALGORITMA
    ResetCurrentWord();
    EndWord = FALSE;
    if (currentChar == MARK) EndWord = TRUE;
    else {
        EndWord = FALSE;
        CopyWordWithBlanks();
    }
}

void CopyWordWithBlanks() {
/* Mengakuisisi kata dengan membolehkan blanks, menyimpan dalam currentWord.
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
    // KAMUS LOKAL

    // ALGORITMA
    currentWord.Length = 0;
    while (currentChar != MARK) {
        if (currentWord.Length < NMax) { // jika lebih akan terpotong
            currentWord.TabWord[currentWord.Length++] = currentChar;
            ADV();
        } else
            break;
            }
}

void STARTLINE() {
/* Membaca satu line dari user, dengan membolehkan spasi.
   I.S. : currentChar sembarang
   F.S. : EndWord = TRUE, dan currentChar = MARK;
          atau EndWord = FALSE, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
    // KAMUS LOKAL

    // ALGORITMA
    ResetCurrentWord();
    START();
    if (currentChar == MARK) EndWord = TRUE;
    else {
        EndWord = FALSE;
        CopyWordWithBlanks();
    }
}

boolean isKataEqual(Word W1, Word W2) {
/* Mengembalikan TRUE bila Word W1 sama dengan Word W2. */
    // KAMUS LOKAL
    int i;
    
    // ALGORITMA
    if (W1.Length != W2.Length) return FALSE;
    else {
        for (i=0; i<W1.Length; i++) {
            if (W1.TabWord[i] != W2.TabWord[i]) return FALSE;
        } return TRUE;
    }
}

boolean isKataInt(Word W) {
/* Mengembalikan TRUE apabila seluruh isi Word berupa numerik */
    // KAMUS LOKAL
    int i;

    // ALGORITMA
    for (i=0; i<W.Length; i++) {
        if (!(W.TabWord[i] >= '0' && W.TabWord[i] <= '9')) return FALSE;
    } return TRUE;
}

void displayWord(Word W, boolean newLine) {
/* Menampilkan isi Word ke layar.
   I.S. : sembarang
   F.S. : Seluruh isi dalam Word telah ditampilkan pada layar */
    // KAMUS LOKAL
    int i=0;

    // ALGORITMA
    for (i=0; i<W.Length; i++) {
        printf("%c", W.TabWord[i]);
    } 

    if (newLine) printf("\n");
}

int WordToInt(Word W) 
{
/* Mengembalikan nilai integer dari Word W */
    // KAMUS LOKAL
    int i, res=0;

    // ALGORITMA
    for (i=0; i<W.Length; i++) {
        res = res*10 + (W.TabWord[i] - '0');
    } return res;
}
