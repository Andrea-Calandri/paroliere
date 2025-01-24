#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paroliere.h"

// Function prototypes
void readWordsFromFile(const char *filename); 
void insertLetters();                         
void dfs(int current, int *visited, char *word, int word_len);
int binarySearch(const char *prefix, int isPrefix);  
void showGrid();  

// Adjacency matrix for 4x4 grid connections
int adj[ADJ_SIDE][ADJ_SIDE] = {
    {0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0}
};

// Word length scores
int score[] = {0, 0, 0, 0, 1, 2, 3, 5, 8, 10, 12, 14, 16, 18, 20, 22, 24};

// Board letters and grid
char letters[ADJ_SIDE];
char grid[GRID_SIDE][GRID_SIDE];  // 4x4 grid
int num_words = 0, total_score = 0;

// Dictionary words
char words[MAX_WORDS][MAX_WORD_LENGTH + 1];

// Initializes the game
void ParoliereInitialize() {
    readWordsFromFile("assets/dictionary.txt");
    insertLetters();
    showGrid();
}

// Reads words from the dictionary file
void readWordsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File opening failed.\n");
        return;
    }

    char temp[MAX_WORD_LENGTH * 2];
    while (fscanf(file, "%s", temp) == 1) {
        if (strlen(temp) <= MAX_WORD_LENGTH) {  // Only valid-length words
            strcpy(words[num_words], temp);
            num_words++;
        }
    }

    fclose(file);
}

// Prompts user to input letters for the grid
void insertLetters() {
    printf("\nEnter %d characters:\n", ADJ_SIDE);

    int row = 0, col = 0;
    char c;
    for (int i = 0; i < ADJ_SIDE; i++) {
        printf("Character %d: ", i + 1);
        c = getchar();
        grid[row][col] = c;  // Store character in grid
        letters[i] = c;      // Store character in letters array

        getchar();  // Consume the newline

        col++;
        if (col == GRID_SIDE) {
            col = 0;
            row++;
        }
    }
}

// Displays the 4x4 grid of letters
void showGrid() {
    printf("\nCurrent Grid:\n");
    for (int i = 0; i < GRID_SIDE; i++) {
        for (int j = 0; j < GRID_SIDE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Generates all possible valid words from the grid
void generateWords() {
    int visited[ADJ_SIDE] = {0};  // Tracks visited positions
    char word[MAX_WORD_LENGTH + 1];

    for (int start = 0; start < ADJ_SIDE; start++) {
        dfs(start, visited, word, 0);  // DFS from each position
    }
}

// Depth-first search (DFS) to explore word possibilities
void dfs(int current, int *visited, char *word, int word_len) {
    word[word_len] = letters[current];  // Add current letter to word
    word[word_len + 1] = '\0';          // Null-terminate the word

    if (binarySearch(word, 1) == 0)  // Stop if no valid prefix exists
        return;

    if (word_len > 3 && binarySearch(word, 0)) {  // Valid word found
        total_score += score[strlen(word)];
        printf("%s\n", word);  // Print valid word
    }

    visited[current] = 1;  // Mark current as visited

    for (int i = 0; i < ADJ_SIDE; i++) {
        if (adj[current][i] == 1 && !visited[i]) {  // Visit adjacent unvisited nodes
            dfs(i, visited, word, word_len + 1);
        }
    }

    visited[current] = 0;  // Backtrack
}

// Binary search for word or prefix in the dictionary
int binarySearch(const char *word, int isPrefix) {
    int left = 0, right = num_words - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = isPrefix ? strncmp(words[mid], word, strlen(word)) : strcmp(words[mid], word);
        if (cmp == 0) {  // Found match
            return 1;
        } else if (cmp < 0) {  // Search right half
            left = mid + 1;
        } else {  // Search left half
            right = mid - 1;
        }
    }
    return 0;  // Not found
}

// Prints the total score of the game
void totalScore() {
    printf("\nTotal Score: %d\n", total_score);
}
