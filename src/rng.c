#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    const int MIN = 1;
    const int MAX = 100;
    int guess, guesses, answer;

    srand(time(0));

    answer = (rand() % MAX) + MIN;

    // scanf("%d", &guess);

    while(guess != answer){
        scanf("%d", &guess);
        if(guess > answer){
            printf("Terlalu besar!\n");
        }
        else if (guess < answer){
            printf("Terlalu kecil.\n");
        }
    }
    printf("Tebakan anda benar!\n");

    // printf("%d", answer);

    return 0;
}
