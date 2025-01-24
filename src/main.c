#include <stdio.h>
#include <stdlib.h>
#include "paroliere.h"

int main() {
    // Initialize the game by loading the dictionary and setting up the board
    ParoliereInitialize();

    // Generate all valid words from the board letters
    generateWords();

    // Display the total score accumulated during the game
    totalScore();

    return 0;
}
