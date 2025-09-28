#include <stdio.h>
#include <stdbool.h>

#define N 8   // Change this value for different board sizes

// Function to print the board
void printSolution(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%c ", board[i][j] ? 'Q' : '.');
        printf("\n");
    }
    printf("\n");
}

// Check if queen can be placed at board[row][col]
bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    // Check row on left
    for (i = 0; i < col; i++)
        if (board[row][i]) return false;

    // Check upper diagonal on left
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check lower diagonal on left
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j]) return false;

    return true;
}

// Recursive utility to solve N-Queens
bool solveNQUtil(int board[N][N], int col) {
    if (col >= N) {
        printSolution(board);   // Print one solution
        return true;            // Change to return false here if you want *all* solutions
    }

    bool res = false;
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            res = solveNQUtil(board, col + 1) || res;
            board[i][col] = 0; // backtrack
        }
    }
    return res;
}

// Driver function
int main() {
    int board[N][N] = {0};

    if (!solveNQUtil(board, 0))
        printf("Solution does not exist\n");

    return 0;
}
