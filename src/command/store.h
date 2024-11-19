#ifndef storelist_H
#define storelist_H
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../ADT/list.h"
#include "../ADT/queue.h"
#include "../ADT/mesinkata.h"
#include "../ADT/mesinkarakter.h"

// typedef struct {
//     int price;
//     char name[100];
// } List;

void storelist ();
// I.S List bisa saja kosong
// F.S Jika list kosong, mencetak "TOKO KOSONG"
// Jika list tidak kosong, mencetak seluruh barang yang ada di toko

void remove(List L);

void request (List *L, Queue *Q);


#endif