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

// Score table based on word length
int score[] = {0, 0, 0, 0, 1, 2, 3, 5, 8, 10, 12, 14, 16, 18, 20, 22, 24};

// Grid and game state
char letters[ADJ_SIDE];
char grid[GRID_SIDE][GRID_SIDE];
int num_words = 0, total_score = 0;

// Word dictionary
char words[MAX_WORDS][MAX_WORD_LENGTH + 1];

// Initializes the game
void ParoliereInitialize() {
    readWordsFromFile("assets/dictionary.txt");
    insertLetters();
    showGrid();
}

// Loads words from dictionary file
void readWordsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File opening failed.\n");
        return;
    }

    char temp[MAX_WORD_LENGTH * 2];
    while (fscanf(file, "%s", temp) == 1) {
        if (strlen(temp) <= MAX_WORD_LENGTH) {
            strcpy(words[num_words], temp);
            num_words++;
        }
    }

    fclose(file);
}

// Prompts user to input 16 letters
void insertLetters() {
    printf("\nEnter %d characters:\n", ADJ_SIDE);

    int row = 0, col = 0;
    char c;
    for (int i = 0; i < ADJ_SIDE; i++) {
        printf("Character %d: ", i + 1);
        c = getchar();
        grid[row][col] = c;
        letters[i] = c;
        getchar();  // Consume newline

        col++;
        if (col == GRID_SIDE) {
            col = 0;
            row++;
        }
    }
}

// Displays the 4x4 letter grid
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

// Generates all valid words from the grid
void generateWords() {
    int visited[ADJ_SIDE] = {0};
    char word[MAX_WORD_LENGTH + 1];

    for (int start = 0; start < ADJ_SIDE; start++) {
        dfs(start, visited, word, 0);
    }
}

// Depth-first search for words starting at position `current`
void dfs(int current, int *visited, char *word, int word_len) {
    word[word_len] = letters[current];
    word[word_len + 1] = '\0';

    if (binarySearch(word, 1) == 0)
        return;

    if (word_len > 3 && binarySearch(word, 0)) {
        total_score += score[strlen(word)];
        printf("%s\n", word);
    }

    visited[current] = 1;

    for (int i = 0; i < ADJ_SIDE; i++) {
        if (adj[current][i] && !visited[i]) {
            dfs(i, visited, word, word_len + 1);
        }
    }

    visited[current] = 0;
}

// Binary search in the dictionary
// isPrefix = 1 → search by prefix
// isPrefix = 0 → search full word
int binarySearch(const char *word, int isPrefix) {
    int left = 0, right = num_words - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = isPrefix ? strncmp(words[mid], word, strlen(word)) : strcmp(words[mid], word);

        if (cmp == 0)
            return 1;
        else if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return 0;
}

// Displays the final score
void totalScore() {
    printf("\nTotal Score: %d\n", total_score);
}
