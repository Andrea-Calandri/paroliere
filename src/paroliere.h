#ifndef PAROLIERE_H
#define PAROLIERE_H

// Maximum word length
#define MAX_WORD_LENGTH 16

// Maximum number of words in the dictionary
#define MAX_WORDS 100000

// Size of the grid (4x4)
#define GRID_SIDE 4

// Total number of letters on the board (4x4 grid)
#define ADJ_SIDE 16

// Initialize the game by loading the dictionary and setting up the board
void ParoliereInitialize();

// Add a delay of DELAY seconds
void addDelay(int delay);

// Generates all valid words from the board letters
void generateWords();

// Displays the total score accumulated during the game
void totalScore();

#endif
