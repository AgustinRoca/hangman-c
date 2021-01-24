#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define TOTAL_WORDS 11
#define MAX_ATTEMPTS 6
#define MAX_LENGTH 50
#define MAX_LETTERS ('Z' - 'A' + 1)

char * chooseRandomWord();
void printWord(char * word, int * guessedLettersPositions);
int guessChar(char guessingChar, char * word, int * guessedLettersPositions);
void printHangman(int attempts);
char getCharByStdin();
void printLettersTried(char lettersTried[MAX_LETTERS], int totalLettersTried);

int main() {
    char * word = chooseRandomWord();
    int totalGuessedLetters = 0;
    int totalLetters = strlen(word);
    int * guessedLettersPositions = calloc(1, totalLetters);
    int attempts = 0;
    char lettersTried[MAX_LETTERS] = {0};
    int totalLettersTried = 0;
    while (totalGuessedLetters < totalLetters && attempts <= MAX_ATTEMPTS) {
        printf("\e[1;1H\e[2J"); //clear screen
        printf("Attempts remaining: %d\n", MAX_ATTEMPTS - attempts + 1);
        printHangman(attempts);
        printf("\n");
        printWord(word, guessedLettersPositions);
        printf("\n");
        printLettersTried(lettersTried, totalLettersTried);
        
        char guessingChar;
        int alreadyTried;
        do{
            alreadyTried = 0;
            guessingChar = getCharByStdin();
            for(int i = 0; i<MAX_LETTERS && lettersTried[i]; i++){
                if(guessingChar == lettersTried[i]){
                    printf("You have already tried with this letter, try other one\n");
                    alreadyTried = 1;
                }
            }
        } while(alreadyTried);
        lettersTried[totalLettersTried++] = guessingChar;

        int guessed = guessChar(guessingChar, word, guessedLettersPositions);
        if(guessed == 0){
            attempts++;
        } else {
            totalGuessedLetters += guessed;
        }
        
        printf("-------------------------------------\n");
    }
    if(attempts <= MAX_ATTEMPTS){
        printf("Congratulations you win, the word was: %s\n", word);
    } else {
        printf("Game over, the word was: %s\n", word);
    }
    free(guessedLettersPositions);
    return 0;
}

char * chooseRandomWord(){
    char * words[TOTAL_WORDS] = {"dog", "puppy", "turtle", "rabbit", "parrot", "cat", "kitten", "goldfish", "mouse", "fish", "hamster"};
    srand(time(NULL));
    return words[rand() % TOTAL_WORDS];
}

void printWord(char * word, int * guessedLettersPositions){
    for(int i = 0; word[i]; i++){
        if(guessedLettersPositions[i] != 0){
            printf("%c", word[i]);
        } else {
            printf("_");
        }
    }
    printf("\n");
}

int guessChar(char guessingChar, char * word, int * guessedLettersPositions){
    int guessed = 0;
    for(int i=0; word[i]; i++){
        if(word[i] == guessingChar && guessedLettersPositions[i] == 0){
            guessedLettersPositions[i] = 1;
            guessed++;
        }
    }
    return guessed;
}

char getCharByStdin(){
    int done = 0;
    char ans;
    do {
        printf("Enter a letter: ");
        char inputString[MAX_LENGTH];
        if(fgets(inputString, MAX_LENGTH, stdin) != NULL){
            if(strlen(inputString) == 2 && isalpha(inputString[0]) && inputString[1] == '\n'){
                done = 1;
                if(inputString[0] >= 'A' && inputString[0] <= 'Z')
                    ans = inputString[0] - 'A' + 'a';
                else {
                    ans = inputString[0];
                }
            } else {
                printf("You must enter ONE LETTER\n");
            }
        } else {
            printf("Please enter one letter\n");
        }
    } while(!done);
    return ans;
}

void printHangman(int attempts){
    printf("+--+\n");
    
    printf("|  |\n");

    if(attempts > 0){
        printf("|  o\n");
    } else {
        printf("|\n");
    }

    printf("| ");
    if(attempts > 2){
        printf("/");
    } else {
        printf(" ");
    }
    if(attempts > 1){
        printf("|");
    } else {
        printf(" ");
    } 
    if(attempts > 3){
        printf("\\");
    } else {
        printf(" ");
    }
    printf("\n");

    printf("| ");
    if(attempts > 4){
        printf("/ ");
    } else {
        printf("  ");
    }
    if(attempts > 5){
        printf("\\");
    } else {
        printf(" ");
    }
    printf("\n");
    printf("|\n");
    printf("+======\n");
}

void printLettersTried(char lettersTried[MAX_LETTERS], int totalLettersTried){
    printf("Letters you tried:");
        for (int i = 0; i < MAX_LETTERS && lettersTried[i]; i++)
        {
            printf(" %c", lettersTried[i]);
        }
        if(totalLettersTried == 0){
            printf(" None");
        }
        printf("\n");
}