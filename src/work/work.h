#ifndef __work__
#define ____

#include "../ADT/mesinkata.h"
#include "../ADT/boolean.h"

typedef struct
{
    char workName[100]; //nama pekerjaan
    int workPayment;    //gaji
    int workDuration;   //durasi kerja
} Work;

void delay(int seconds);

void collectInput(char *input);

#endif