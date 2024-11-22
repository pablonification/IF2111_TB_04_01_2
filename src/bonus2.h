#ifndef BONUS2_H
#define BONUS2_H

#include <stdio.h>
#include "misc.h"

// Fungsi untuk mengonversi DNA ke RNA
void DNAtoRNA(Word DNA, Word *RNA);

// Fungsi untuk menerjemahkan codon RNA menjadi asam amino
char translateCodon(char *codon);

#endif // BONUS2_H
