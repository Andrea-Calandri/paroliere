#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "paroliere.h"

#define DELAY 60

// function prototype
void addDelay(int delay);

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


// Adds a countdown delay, user can press Enter to skip
void addDelay(int delay) {
    for (int sec = delay; sec >= 0; sec--) {
        printf("\rWaiting: %2d seconds... Press Enter to exit ", sec);
        fflush(stdout);

        // Wait 1 second in 100ms steps
        for (int i = 0; i < 10; i++) {
            Sleep(100);

            if (_kbhit()) {
                int ch = _getch();
                if (ch == '\r') {
                    printf("\nInterrupted by user.\n\n\n");
                    return;
                }
            }
        }
    }

    printf("\nTime's up.\n");
}

