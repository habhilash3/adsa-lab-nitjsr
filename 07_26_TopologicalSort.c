#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// DFS utility function
void topologicalSortUtil(int v, bool visited[], int graph[MAX][MAX], int n, int stack[], int *top) {
    visited[v] = true;

    for (int i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i])
            topologicalSortUtil(i, visited, graph, n, stack, top);
    }

    // Push vertex to stack after visiting neighbors
    stack[++(*top)] = v;
}

// Main function for Topological Sort
void topologicalSort(int graph[MAX][MAX], int n) {
    bool visited[MAX] = {false};
    int stack[MAX];
    int top = -1;

    // Do DFS for all unvisited vertices
    for (int i = 0; i < n; i++)
        if (!visited[i])
            topologicalSortUtil(i, visited, graph, n, stack, &top);

    // Print in reverse order of finishing times
    printf("Topological Sort Order:\n");
    while (top >= 0)
        printf("%d ", stack[top--]);
    printf("\n");
}

// ---------------- Driver ----------------
int main() {
    int n = 6; // number of vertices
    int graph[MAX][MAX] = { {0,1,1,0,0,0},
                            {0,0,0,1,1,0},
                            {0,0,0,1,0,0},
                            {0,0,0,0,0,1},
                            {0,0,0,0,0,1},
                            {0,0,0,0,0,0} };

    topologicalSort(graph, n);
    return 0;
}
