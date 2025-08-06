#include <stdio.h>
#include <stdlib.h>
#include "paroliere.h"

#define DELAY 60

int main() {


    // Initialize the game by loading the dictionary and setting up the board
    ParoliereInitialize();

    // Add a delay of DELAY seconds before displaying the results
    addDelay(DELAY);

    // Generate all valid words from the board letters
    generateWords();

    // Display the total score accumulated during the game
    totalScore();

    return 0;
}
