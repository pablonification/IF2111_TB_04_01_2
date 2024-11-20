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
void storeList (ListBarang L);
// I.S List bisa saja kosong
// F.S Jika list kosong, mencetak "TOKO KOSONG"
// Jika list tidak kosong, mencetak seluruh barang yang ada di toko

void storeRemove(ListBarang L);

void storeRequest (ListBarang *L, Queue *Q);

void storeSupply(ListBarang *L, Queue *Q);

#endif