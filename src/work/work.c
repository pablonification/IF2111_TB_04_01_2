#include <stdio.h>
#include <time.h>
#include "../ADT/mesinkata.h"
#include "work.h"

//IMPLEMENTASI FUNGSI DAN PROSEDUR WORK

//Implementasi fungsi delay
void delay(int seconds) {
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < seconds);
}

//Implementasi fungsi pengumpulan input
void collectInput(char *input){ //input per kata jadiin kalimat
    input[0] = '\0'; //inisialisasi
    Word currentWord;

    while(!EndWord){
        int len = my_strlen(input);

        if(len + currentWord.Length + 1 > 100){ //cek apakah kata yang akan dimasukkan melebihi panjang maksimum
            break;
        }

        for (int i = 0; i < currentWord.Length; i++){
            input[len + i] = currentWord.TabWord[i];
        }
        input[len + currentWord.Length] = ' '; //tambahin spasi tiap akhir kata
        input[len + currentWord.Length + 1] = '\0'; //terminate string
        ADVWORD();
    }
    
    int len = my_strlen(input);
    if(len > 0 && input[len - 1] == ' '){
        input[len - 1] = '\0'; //hapus spasi terakhir
    }
}


void work(int balance){
    Work workList[] = {
        {"Asisten Praktikum Alstrukdat", 1000, 10},
        {"Penghangat Kursi Labdas", 500, 6},
        {"Teknisi Wifi Eduroam", 700, 8}
    };

    int workCount = sizeof(workList) / sizeof(workList[0]); //jumlah pekerjaan tersedia

    printf(">> WORK\nDaftar pekerjaan:\n"); //print daftar pekerjaan yang tersedia
    for(int i = 0; i < workCount; i++){
        printf("%d. %s (pendapatan: %d, durasi: %ds)\n", i+1, workList[i].workName, workList[i].workPayment, workList[i].workDuration);
    }

    boolean validWork = FALSE; //inisialisasi
    char selectedWork[100];
    int selectedWorkIndex;

    while(!validWork){
        printf("\nPilih nama pekerjaan: ");
        STARTWORD(); //baca input
        collectInput(selectedWork);

        for (int i = 0; i < workCount; i++){ //cek apakah pekerjaan yang dipilih valid
            if (my_strcmp(selectedWork, workList[i].workName) == 0){ //jika valid
                validWork = TRUE;
                selectedWorkIndex = i;
                break;
            }
        }
        if (!validWork){ //jika tidak valid, kembali ke loop, input lagi
            printf("Pekerjaan tidak valid, silakan coba lagi. "); 
        }
    }

    printf("Anda sedang bekerja sebagai %s. Harap tunggu...\n", selectedWork);
    delay(workList[selectedWorkIndex].workDuration);
    printf("Pekerjaan telah selesai. Anda mendapatkan gaji $%d\n", workList[selectedWorkIndex].workPayment);

    balance += workList[selectedWorkIndex].workPayment;
}