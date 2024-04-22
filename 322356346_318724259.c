#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

// User & Computer Scores
int USER_SCORE = 0;
int COMPUTER_SCORE = 0;

// User & Computer Choices
char USER_CHOICE[20];
char COMPUTER_CHOICE[20];

// Function Declaretions

char getUserChoice();
char convertFromDigitToChar(int var);
char getComputerChoice();
int determineWinner(char userChoice, char computerChoice);
void printResult(int result);
void convertChoicesCharToString(char userChoice, char computerChoice);
void updateScore(int result);
int checkForRemainingCharacters();


// Function to get the choice from the user
char getUserChoice() {
    char choice;
    // Print the choices
    printf("Enter one of the following choices:\n");
    printf("1/R/r - Rock\n");
    printf("2/P/p - Paper\n");
    printf("3/S/s - Scissors\n");
    // Get the user's choice
    scanf_s("%c", &choice, sizeof(choice));
    if (isdigit(choice)) //function isdigit() to check whether the input is digit, returns 1 if true. 
    {
        return convertFromDigitToChar((int)choice);
    }
    else {
        return toupper(choice);
    }
}

char convertFromDigitToChar(int var) {
    if (var == 49)
        return 'R';
    else if (var == 50)
        return 'P';
    else if (var == 51)
        return 'S';
    return;
}

// Function to get the computer's choice
char getComputerChoice() {
    // Generate a random number between 1 and 3, which stands for the computer's answer
    int randomNumber = rand() % 3 + 1;
    switch (randomNumber) {
    case 1:
        return 'R'; // Rock
    case 2:
        return 'P'; // Paper
    case 3:
        return 'S'; // Scissors
    default:
        return 'R'; // Scissors
    }
}

// Function to determine the winner
int determineWinner(char userChoice, char computerChoice) {
    if (userChoice == computerChoice)
        return 3; // Tie

    if ((userChoice == 'R' && computerChoice == 'S') ||
        (userChoice == 'P' && computerChoice == 'R') ||
        (userChoice == 'S' && computerChoice == 'P'))
        return 1; // User wins

    return 2; // Computer wins
}

// Function to print the result
void printResult(int result) {
    printf("You chose %s and the computer chose %s.\n", USER_CHOICE, COMPUTER_CHOICE);
    switch (result) {
    case 1:
        printf("You win!\n");
        break;
    case 2:
        printf("Computer wins!\n");
        break;
    case 3:
        printf("It's a tie!\n");
        break;
    }
    printf("Current Scores:\n");
    printf("User Score: %d\n", USER_SCORE);
    printf("Computer Score: %d\n", COMPUTER_SCORE);
}

void convertChoicesCharToString(char userChoice, char computerChoice) {
    if (userChoice == 'R')
        strcpy_s(USER_CHOICE, sizeof(USER_CHOICE), "Rock");
    if (userChoice == 'P')
        strcpy_s(USER_CHOICE, sizeof(USER_CHOICE), "Paper");
    if (userChoice == 'S')
        strcpy_s(USER_CHOICE, sizeof(USER_CHOICE), "Scissors");
    if (computerChoice == 'R')
        strcpy_s(COMPUTER_CHOICE, sizeof(COMPUTER_CHOICE), "Rock");
    if (computerChoice == 'P')
        strcpy_s(COMPUTER_CHOICE, sizeof(COMPUTER_CHOICE), "Paper");
    if (computerChoice == 'S')
        strcpy_s(COMPUTER_CHOICE, sizeof(COMPUTER_CHOICE), "Scissors");
}

void updateScore(int result) {
    // Update the current scores according to the result
    switch (result) {
    case 1:
        USER_SCORE++;
        break;
    case 2:
        COMPUTER_SCORE++;
        break;
    }
}

int checkForRemainingCharacters() {
    // Check if there are any characters remaining in the input buffer
    char extra;
    if (scanf_s("%c", &extra, sizeof(extra)) != EOF && extra != '\n') {
        printf("Error: More than one character entered.\n");
        // clear input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 1;
    }
    return 0;
}

int main() {
    char userChoice, computerChoice;
    int result;

    srand((unsigned int)time(NULL)); // Seed the random number generator
    printf("Welcome to Rock, Paper, Scissors Game!\n");

    do {
        // Get the user's choice
        do {
            userChoice = getUserChoice();
        } while (checkForRemainingCharacters() == 1);
        // Validate user's choice
        if (userChoice != 'R' && userChoice != 'P' && userChoice != 'S') {
            printf("Invalid choice. Please enter Rock, Paper, or Scissors.\n");
            continue;
        }
        // Get the computer's choice
        computerChoice = getComputerChoice();
        // Determine who is the winner
        result = determineWinner(userChoice, computerChoice);
        // Update Scores
        updateScore(result);
        // Modify choices from int to String
        convertChoicesCharToString(userChoice, computerChoice);
        // Print the end result
        printResult(result);
        // Ask if the user wants to play again
        char playAgain;
        do {
            do {
                printf("Would you like to play again (Y/N)?\n");
                scanf_s(" %c", &playAgain, sizeof(playAgain));
                playAgain = toupper(playAgain);
            } while (checkForRemainingCharacters() == 1);
            // Check if the user wants to play again or not
            if (playAgain == 'Y')
                break;
            if (playAgain == 'N') {
                printf("Thanks for playing!\n");
                printf("Scores:\n");
                printf("User Score: %d\n", USER_SCORE);
                printf("Computer Score: %d\n", COMPUTER_SCORE);
                return 0;
            }
            continue;
        } while (playAgain);
    } while (1);
}