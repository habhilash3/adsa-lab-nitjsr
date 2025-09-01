/*
Q1. Write a C program that creates a 2D array initialized with zeros
    and allows user to input the row, column and values to insert into the array. */

#include <stdio.h>
#include <stdlib.h>

void printArray(int **arr, int rows, int cols) {
    printf("\nCurrent array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int rows, cols;
    int **arr;
    int row, col, value;
    char choice;
    
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    
    if (rows <= 0 || cols <= 0) {
        printf("Error: Rows and columns must be positive integers.\n");
        return 1;
    }
    
    arr = (int **)malloc(rows * sizeof(int *));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    for (int i = 0; i < rows; i++) {
        arr[i] = (int *)calloc(cols, sizeof(int)); // calloc initializes with zeros
        if (arr[i] == NULL) {
            printf("Memory allocation failed!\n");
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return 1;
        }
    }
    
    printf("\n2D Array (%dx%d) initialized with zeros.\n", rows, cols);
    printArray(arr, rows, cols);
    
    do {
        printf("Enter row index (0-%d): ", rows-1);
        scanf("%d", &row);
        
        printf("Enter column index (0-%d): ", cols-1);
        scanf("%d", &col);
        
        // Validate indices
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            printf("Error: Invalid indices! Row must be 0-%d, Column must be 0-%d\n", 
                   rows-1, cols-1);
            continue;
        }
        
        printf("Enter value to insert: ");
        scanf("%d", &value);
        
        arr[row][col] = value;
        
        printArray(arr, rows, cols);
        
        printf("Do you want to insert another value? (y/n): ");
        scanf(" %c", &choice);
        
    } while (choice == 'y' || choice == 'Y');
    
    printf("Final array:\n");
    printArray(arr, rows, cols);
    
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
    
    printf("Program terminated successfully.\n");
    return 0;
}