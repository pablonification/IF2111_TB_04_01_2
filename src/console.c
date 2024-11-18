#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "boolean.h"
#include "console.h"

// IMPLEMENTASI FUNGSI DAN PROSEDUR WORDL3

char board[MAX_ATTEMPTS][WORD_LENGTH * 3 + 1];

// void evaluateGuess(const char *target, const char *guess, char *result) {
//     int matched[WORD_LENGTH] = {0}; // Tracks exact matches
//     int used[WORD_LENGTH] = {0};    // Tracks letters used for wrong positions

//     // Check for exact matches
//     for (int i = 0; i < WORD_LENGTH; i++) {
//         if (guess[i] == target[i]) {
//             result[i * 3] = target[i]; 
//             result[i * 3 + 1] = ' ';  
//             result[i * 3 + 2] = ' ';  
//             matched[i] = 1;           
//             used[i] = 1;              
//         } else {
//             result[i * 3] = guess[i]; 
//             result[i * 3 + 1] = '%';  
//             result[i * 3 + 2] = ' ';  
//         }
//     }

//     // Check for wrong-position matches
//     for (int i = 0; i < WORD_LENGTH; i++) {
//         if (result[i * 3 + 1] == '%') { 
//             for (int j = 0; j < WORD_LENGTH; j++) {
//                 if (!matched[j] && !used[j] && guess[i] == target[j]) {
//                     result[i * 3 + 1] = '*'; 
//                     used[j] = 1;            
//                     break;
//                 }
//             }
//         }
//     }

//     result[WORD_LENGTH * 3] = '\0';
// }

int compareWords(const char *word1, const char *word2) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (word1[i] != word2[i]) {
            return 0; 
        }
    }
    return 1; 
}

char *copy(char *dest, const char *src) {
    char *destPtr = dest; 
    while (*src) {        
        *dest = *src;     
        dest++;           
        src++;            
    }
    *dest = '\0';         
    return destPtr;       
}

void playWordl3() {
    // Load words from file
    char **wordsList = calloc(100, sizeof(char*)); 
    int wordCount = 0;
    char buffer[6];
    FILE *wordsFile = fopen("words.txt", "r");
    if (!wordsFile) {
        printf("Error: Unable to open words file.\n");
        free(wordsList);
        exit(1);
    }

    // Read words from file
    while (fscanf(wordsFile, "%5s", buffer) != EOF) { 
        wordsList[wordCount] = malloc(6 * sizeof(char)); 
        /*if (wordsList[wordCount] == NULL) {
            printf("Error: Memory allocation failed.\n");
            fclose(wordsFile);
            for (int i = 0; i < wordCount; i++) {
                free(wordsList[i]);
            }
            free(wordsList);
            exit(1);
        }*/
        copy(wordsList[wordCount], buffer); 
        wordCount++;
    }
    fclose(wordsFile);

    // Pick a random word
    srand(time(NULL));
    char *answer = wordsList[rand() % wordCount];

    // Initialize game board
    for (int i = 0; i < MAX_ATTEMPTS; i++) {
        for (int j = 0; j < WORD_LENGTH * 3; j += 3) {
            board[i][j] = '_';
            board[i][j + 1] = ' ';
            board[i][j + 2] = ' ';
        }
        board[i][WORD_LENGTH * 3] = '\0'; // Null-terminate each row
    }

    // Game loop
    int attempts = 0;
    boolean win = FALSE;
    char guess[6];

    printf("WELCOME TO W0RDL3, YOU HAVE %d CHANCES TO ANSWER BEFORE YOU LOSE!\n", MAX_ATTEMPTS);

    while (attempts < MAX_ATTEMPTS && !win) {
        // Display the board
        for (int i = 0; i < MAX_ATTEMPTS; i++) {
            printf("%s\n", board[i]);
        }

        // Get user input
        printf("Masukkan kata tebakan Anda: ");
        scanf("%5s", guess); // Only up to 5 chars are read

        evaluateGuess(answer, guess, board[attempts]);

        // Check for win
        if (compareWords(answer, guess)) {
            win = TRUE;
        }
        attempts++;
    }

    // Display final results
    for (int i = 0; i < MAX_ATTEMPTS; i++) {
        printf("%s\n", board[i]);
    }

    if (win) {
        printf("Selamat, Anda menang! +1500 rupiah telah ditambahkan ke akun Anda.\n");
    } else {
        printf("Boo! Anda kalah.\n");
        printf("Jawaban yang benar adalah: %s\n", answer);
    }

    
    free(wordsList); 
}

// IMPLEMENTASI FUNGSI DAN PROSEDUR QUANTUM WORDL3

char quantumBoard[NUM_WORDS][MAX_ATTEMPTS_Q][WORD_LENGTH * 3 + 1];

size_t my_strlen(const char *str) {
    size_t length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

void my_strcpy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0'; 
}

int my_strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

// Function to evaluate a single guess against a target word
void evaluateGuess(const char *target, const char *guess, char *result) {
    int matched[WORD_LENGTH] = {0};
    int used[WORD_LENGTH] = {0};

    // Check for exact matches
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == target[i]) {
            result[i * 3] = target[i];
            result[i * 3 + 1] = ' ';
            result[i * 3 + 2] = ' ';
            matched[i] = 1;
            used[i] = 1;
        } else {
            result[i * 3] = guess[i];
            result[i * 3 + 1] = '%';
            result[i * 3 + 2] = ' ';
        }
    }

    // Check for wrong-position matches
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result[i * 3 + 1] == '%') {
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!matched[j] && !used[j] && guess[i] == target[j]) {
                    result[i * 3 + 1] = '*';
                    used[j] = 1;
                    break;
                }
            }
        }
    }

    result[WORD_LENGTH * 3] = '\0'; // Null-terminate the result
}

// Function to check if all target words are guessed correctly
boolean allWordsGuessed(const char targets[NUM_WORDS][WORD_LENGTH + 1], const char guesses[NUM_WORDS][WORD_LENGTH + 1]) {
    for (int i = 0; i < NUM_WORDS; i++) {
        if (my_strcmp(targets[i], guesses[i]) != 0) {
            return FALSE;
        }
    }
    return TRUE;
}

// Function to play Quantum W0RDL3
void playQuantumWordl3() {
    // Load words from file
    char **wordsList = calloc(100, sizeof(char*));
    int wordCount = 0;
    char buffer[6];
    FILE *wordsFile = fopen("words.txt", "r");
    if (!wordsFile) {
        printf("Error: Unable to open words file.\n");
        free(wordsList);
        exit(1);
    }

    while (fscanf(wordsFile, "%5s", buffer) != EOF) {
        wordsList[wordCount] = malloc(6 * sizeof(char));
        my_strcpy(wordsList[wordCount], buffer);
        wordCount++;
    }
    fclose(wordsFile);

    // Randomly select four distinct words
    char targets[NUM_WORDS][WORD_LENGTH + 1];
    int selectedIndices[NUM_WORDS] = {-1, -1, -1, -1};

    for (int i = 0; i < NUM_WORDS; i++) {
        int index;
        do {
            index = rand() % wordCount;
        } while (index == selectedIndices[0] || index == selectedIndices[1] || index == selectedIndices[2] || 
                 index == selectedIndices[3]);

        my_strcpy(targets[i], wordsList[index]);
        selectedIndices[i] = index;
    }

    // Initialize the game board
    for (int w = 0; w < NUM_WORDS; w++) {
        for (int a = 0; a < MAX_ATTEMPTS_Q; a++) {
            for (int j = 0; j < WORD_LENGTH * 3; j += 3) {
                quantumBoard[w][a][j] = '_';
                quantumBoard[w][a][j + 1] = ' ';
                quantumBoard[w][a][j + 2] = ' ';
            }
            quantumBoard[w][a][WORD_LENGTH * 3] = '\0'; // Null-terminate
        }
    }

    // Game loop
    int attempts = 0;
    boolean win = FALSE;
    char guesses[NUM_WORDS][WORD_LENGTH + 1];

    printf("WELCOME TO QUANTUM W0RDL3! YOU HAVE %d CHANCES TO GUESS ALL FOUR WORDS.\n", MAX_ATTEMPTS_Q);

    while (attempts < MAX_ATTEMPTS_Q && !win) {
        // Display the board
        for (int w = 0; w < NUM_WORDS; w++) {
            printf("Word %d:\n", w + 1);
            for (int a = 0; a < MAX_ATTEMPTS_Q; a++) {
                printf("%s\n", quantumBoard[w][a]);
            }
            printf("\n");
        }

        // Get guesses for all four words
        printf("Enter your guesses (space-separated, 4 words): ");
        for (int i = 0; i < NUM_WORDS; i++) {
            scanf("%5s", guesses[i]);
        }

        // Evaluate guesses and update the board
        for (int w = 0; w < NUM_WORDS; w++) {
            evaluateGuess(targets[w], guesses[w], quantumBoard[w][attempts]);
        }

        // Check if all words are guessed correctly
        if (allWordsGuessed(targets, guesses)) {
            win = TRUE;
        }

        attempts++;
    }

    // Display final results
    for (int w = 0; w < NUM_WORDS; w++) {
        printf("Word %d:\n", w + 1);
        for (int a = 0; a < MAX_ATTEMPTS_Q; a++) {
            printf("%s\n", board[w][a]);
        }
        printf("\n");
    }

    if (win) {
        printf("Selamat, Anda menang! +10000 rupiah telah ditambahkan ke akun Anda.\n");
    } else {
        printf("Boo! Anda kalah.\n");
        printf("Jawaban yang benar adalah:\n");
        for (int i = 0; i < NUM_WORDS; i++) {
            printf("Kata %d: %s\n", i + 1, targets[i]);
        }
    }

    free(wordsList);
}

// IMPLEMENTASI PROSEDUR HELP
void Help(int x){
    if ( x == 1){
        // Ketika perintah dipanggil pada welcome menu
        printf("=====[ Welcome Menu Help PURRMART]=====\n");
        printf("1. START -> Untuk masuk sesi baru\n");
        printf("2. LOAD -> Untuk memulai sesi berdasarkan file konfigurasi\n");
        printf("3. QUIT -> Untuk keluar dari program\n");
    } else if ( x == 2){
        // Ketika perintah dipanggil pada login menu
        printf("=====[ Login Menu Help PURRMART ]=====\n");
        printf("1. REGISTER -> Untuk melakukan pendaftaran akun baru\n");
        printf("2. LOGIN -> Untuk masuk ke dalam akun dan memulai sesi\n");
        printf("3. QUIT -> Untuk keluar dari program\n");
    } else if ( x == 3){
        // Ketika perintah dipanggil pada main menu
        printf("=====[ Menu Help PURRMART ]=====\n");
        printf("1. WORK -> Untuk bekerja\n");
        printf("2. WORK CHALLENGE -> Untuk mengerjakan challenge\n");
        printf("3. STORE LIST -> Untuk melihat barang-barang di toko\n");
        printf("4. STORE REQUEST -> Untuk meminta penambahan barangn");
        printf("5. STORE SUPPLY -> Untuk menambahkan barang dari permintaan\n");
        printf("6. STORE REMOVE -> Untuk menghapus barang\n");
        printf("7. LOGOUT -> Untuk keluar dari sesi\n");
        printf("8. SAVE -> Untuk menyimpan state ke dalam file\n");
        printf("9. QUIT -> Untuk keluar dari program\n");
    }
}

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

    printf(">> WORK\nDaftar pekerjaan:\n");
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
        if (!validWork){ //jika tidak valid
            printf("Pekerjaan tidak valid, silakan coba lagi. ");
        }
    }

    printf("Anda sedang bekerja sebagai %s. Harap tunggu...\n", selectedWork);
    delay(workList[selectedWorkIndex].workDuration);
    printf("Pekerjaan telah selesai. Anda mendapatkan gaji $%d\n", workList[selectedWorkIndex].workPayment);

    balance += workList[selectedWorkIndex].workPayment;
}