#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXV 50  // Max number of vertices

int graph[MAXV][MAXV]; // adjacency matrix
int visited[MAXV];
int stack[MAXV], stackPos;
int minCycle = INT_MAX, maxCycle = 0;
int V;

// Utility function to check if vertex is in current stack path
int isInStack(int v) {
    for (int i = 0; i < stackPos; i++) {
        if (stack[i] == v) return i;
    }
    return -1;
}

void dfs(int u, int parent, int directed) {
    visited[u] = 1;
    stack[stackPos++] = u;

    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            // Skip the edge to parent in undirected graph
            if (!directed && v == parent) continue;

            int pos = isInStack(v);
            if (pos != -1) {
                // Found a cycle
                int cycleLen = stackPos - pos;
                if (cycleLen >= 2) {
                    if (cycleLen < minCycle) minCycle = cycleLen;
                    if (cycleLen > maxCycle) maxCycle = cycleLen;
                }
            } else if (!visited[v]) {
                dfs(v, u, directed);
            }
        }
    }

    stackPos--;
    visited[u] = 0;
}

void findCycles(int directed) {
    for (int i = 0; i < V; i++) {
        dfs(i, -1, directed);
    }

    if (minCycle == INT_MAX) {
        printf("No cycles found.\n");
    } else {
        printf("Smallest cycle length = %d\n", minCycle);
        printf("Largest cycle length = %d\n", maxCycle);
    }
}

int main() {
    int E, u, v, directed;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Is the graph directed? (1 = Yes, 0 = No): ");
    scanf("%d", &directed);

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        if (!directed) graph[v][u] = 1;
    }

    findCycles(directed);

    return 0;
}
