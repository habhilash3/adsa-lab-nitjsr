#include <stdio.h>
#include <stdbool.h>

#define V 4   // Number of vertices

// Function to print the solution (color assignment)
void printSolution(int color[]) {
    printf("Solution exists: Assigned colors are\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d ---> Color %d\n", i, color[i]);
}

// Function to check if the current color assignment is safe
bool isSafe(int v, bool graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && c == color[i])  // adjacent vertex has same color
            return false;
    }
    return true;
}

// A recursive utility function to solve the m-coloring problem
bool graphColoringUtil(bool graph[V][V], int m, int color[], int v) {
    // If all vertices are assigned a color then return true
    if (v == V)
        return true;

    // Try different colors for vertex v
    for (int c = 1; c <= m; c++) {
        // Check if assignment is safe
        if (isSafe(v, graph, color, c)) {
            color[v] = c;

            // Recur to assign colors to the rest of the vertices
            if (graphColoringUtil(graph, m, color, v + 1))
                return true;

            // If assigning color c doesn't lead to a solution then remove it
            color[v] = 0;
        }
    }

    // If no color can be assigned, return false
    return false;
}

// This function solves the m Coloring problem using Backtracking
void graphColoring(bool graph[V][V], int m) {
    int color[V];
    for (int i = 0; i < V; i++)
        color[i] = 0;

    if (!graphColoringUtil(graph, m, color, 0))
        printf("Solution does not exist\n");
    else
        printSolution(color);
}

// Driver Code
int main() {
    /* Example graph (Adjacency Matrix)
       (0)---(1)
        |   /
        |  /
       (2)---(3)
    */
    bool graph[V][V] = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0},
    };

    int m = 3; // Number of colors
    graphColoring(graph, m);
    return 0;
}
