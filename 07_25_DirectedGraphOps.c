#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

// ---------------- Strongly Connected Components (Kosaraju) ----------------
void DFS1(int v, bool visited[], int graph[MAX][MAX], int n, int stack[], int *top) {
    visited[v] = true;
    for (int i = 0; i < n; i++)
        if (graph[v][i] && !visited[i])
            DFS1(i, visited, graph, n, stack, top);
    stack[++(*top)] = v;
}

void DFS2(int v, bool visited[], int transpose[MAX][MAX], int n) {
    printf("%d ", v);
    visited[v] = true;
    for (int i = 0; i < n; i++)
        if (transpose[v][i] && !visited[i])
            DFS2(i, visited, transpose, n);
}

void stronglyConnectedComponents(int graph[MAX][MAX], int n) {
    int stack[MAX], top = -1;
    bool visited[MAX] = {false};

    // Step 1: Order by finish time
    for (int i = 0; i < n; i++)
        if (!visited[i])
            DFS1(i, visited, graph, n, stack, &top);

    // Step 2: Transpose graph
    int transpose[MAX][MAX];
    memset(transpose, 0, sizeof(transpose));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (graph[i][j])
                transpose[j][i] = 1;

    // Step 3: Process in stack order
    memset(visited, false, sizeof(visited));
    printf("\nStrongly Connected Components:\n");
    while (top >= 0) {
        int v = stack[top--];
        if (!visited[v]) {
            DFS2(v, visited, transpose, n);
            printf("\n");
        }
    }
}

// ---------------- Articulation Points and Bridges ----------------
int timeDFS;

void APBUtil(int u, bool visited[], int disc[], int low[], int parent[], bool ap[], 
             int graph[MAX][MAX], int n) {
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++timeDFS;

    for (int v = 0; v < n; v++) {
        if (!graph[u][v]) continue;

        if (!visited[v]) {
            children++;
            parent[v] = u;
            APBUtil(v, visited, disc, low, parent, ap, graph, n);

            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            // Articulation point conditions
            if (parent[u] == -1 && children > 1)
                ap[u] = true;
            if (parent[u] != -1 && low[v] >= disc[u])
                ap[u] = true;

            // Bridge condition
            if (low[v] > disc[u])
                printf("Bridge: %d -- %d\n", u, v);

        } else if (v != parent[u]) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

void articulationPointsAndBridges(int graph[MAX][MAX], int n) {
    bool visited[MAX] = {false};
    int disc[MAX], low[MAX], parent[MAX];
    bool ap[MAX] = {false};

    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        visited[i] = false;
    }

    timeDFS = 0;
    for (int i = 0; i < n; i++)
        if (!visited[i])
            APBUtil(i, visited, disc, low, parent, ap, graph, n);

    printf("\nArticulation Points:\n");
    for (int i = 0; i < n; i++)
        if (ap[i]) printf("%d ", i);
    printf("\n");
}

// ---------------- Driver ----------------
int main() {
    int n = 5;
    int graph[MAX][MAX] = {
        {0,1,1,0,0},
        {0,0,0,1,0},
        {0,1,0,0,0},
        {0,0,0,0,1},
        {0,0,0,0,0}
    };

    stronglyConnectedComponents(graph, n);

    // For articulation points and bridges we treat it as undirected
    int undirected[MAX][MAX] = {
        {0,1,1,0,0},
        {1,0,1,1,0},
        {1,1,0,0,0},
        {0,1,0,0,1},
        {0,0,0,1,0}
    };
    articulationPointsAndBridges(undirected, 5);

    return 0;
}
