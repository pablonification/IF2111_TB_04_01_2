#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ADT/mesinkata.h"
#include "misc.h"

void tebakAngkaRNG() {
    const int MIN = 1;
    const int MAX = 100;
    int guess, answer, chance = 10, initial_reward = 500, reward;
    Word inputWord;

    srand(time(0));
    answer = (rand() % MAX) + MIN;
    printf("%d<<<<JAWABAN\n", answer); // sementara di liatin buat testing aje

    for (int i = 1; i <= chance; i++) {
        printf("Tebak angka: ");
        // scanf("%d", &guess);
        scanWord(&inputWord);

        // Convert word to int
        if(isKataInt(inputWord)){
            guess = convertWordToInt(inputWord);
        }
        else {
            printf("Input tidak valid. Tolong masukkan angka!\n");
            i--;
            continue;
        }
        
        if (guess == answer) {
            reward = initial_reward - ((i - 1) * (initial_reward / chance));
            if (reward < 50) {
                reward = 50;
            }
            printf("Tebakanmu benar!, +%d rupiah telah ditambahkan ke akun anda.\n", reward);
            return; 
        } else if (guess > answer) {
            printf("Tebakanmu lebih besar!\n");
        } else if (guess < answer) {
            printf("Tebakanmu lebih kecil.\n");
        }
    }
    printf("Kesempatan habis! Angka yang benar adalah %d.\n", answer);
}

int main(){
    tebakAngkaRNG();
    return 0;
}