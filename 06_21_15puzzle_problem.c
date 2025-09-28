#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4   // 4x4 board for 15-puzzle
#define INF 999999

// Structure for state (node)
typedef struct Node {
    int mat[N][N];    // Board configuration
    int x, y;         // Blank tile coordinates
    int cost;         // Heuristic cost (Manhattan distance)
    int level;        // Depth of node (number of moves)
    struct Node* parent; // Parent node (to print path)
} Node;

// Final (goal) state
int final[N][N] = {
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9, 10, 11, 12},
    {13,14, 15,  0}
};

// Directions: up, down, left, right
int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

// Utility to allocate a new node
Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->parent = parent;
    node->level = level;

    // Copy data
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            node->mat[i][j] = mat[i][j];

    // Swap blank tile with new position
    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->x = newX;
    node->y = newY;

    return node;
}

// Heuristic: Manhattan distance
int calculateCost(int mat[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] && mat[i][j] != final[i][j]) {
                int val = mat[i][j];
                int targetX = (val - 1) / N;
                int targetY = (val - 1) % N;
                cost += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return cost;
}

// Check if (x,y) is within board
int isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Print matrix
void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Print path from root to goal
void printPath(Node* root) {
    if (root == NULL) return;
    printPath(root->parent);
    printMatrix(root->mat);
}

// Simple priority queue for demo (linear search for min f = cost+level)
Node* minNode(Node* arr[], int size, int* index) {
    int minF = INF, idx = -1;
    for (int i = 0; i < size; i++) {
        int f = arr[i]->cost + arr[i]->level;
        if (f < minF) {
            minF = f;
            idx = i;
        }
    }
    *index = idx;
    return arr[idx];
}

// Solve puzzle
void solve(int initial[N][N], int x, int y) {
    Node* start = newNode(initial, x, y, x, y, 0, NULL);
    start->cost = calculateCost(start->mat);

    Node* pq[10000]; // Priority queue (simple array)
    int size = 0;
    pq[size++] = start;

    while (size > 0) {
        int idx;
        Node* min = minNode(pq, size, &idx);

        // Remove min from PQ
        pq[idx] = pq[--size];

        if (min->cost == 0) {
            printf("Solution found!\n\n");
            printPath(min);
            return;
        }

        // Generate children
        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];

            if (isSafe(newX, newY)) {
                Node* child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateCost(child->mat);
                pq[size++] = child;
            }
        }
    }
}

int main() {
    // Example initial state (0 is blank)
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13,14,11,15}
    };

    int x = 1, y = 2; // blank tile position

    solve(initial, x, y);

    return 0;
}
