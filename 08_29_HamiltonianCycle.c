#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int n;                      // number of vertices
int graph[MAX][MAX];        // adjacency matrix
int path[MAX];              // store the Hamiltonian path

// Function to check if vertex v can be added at position pos in path[]
bool isSafe(int v, int pos) {
    // Check if this vertex is adjacent to the previous vertex in path
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Check if vertex already included
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// Recursive utility function to solve Hamiltonian cycle problem
bool hamCycleUtil(int pos) {
    // Base case: If all vertices are included in the cycle
    if (pos == n) {
        // And if there is an edge from the last to the first vertex
        return graph[path[pos - 1]][path[0]] == 1;
    }

    // Try different vertices as next candidate in the Hamiltonian Cycle
    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            if (hamCycleUtil(pos + 1))
                return true;

            // Backtrack
            path[pos] = -1;
        }
    }

    return false;
}

// Function to check if there is a Hamiltonian Cycle
bool hamCycle() {
    for (int i = 0; i < n; i++)
        path[i] = -1;

    // Start from vertex 0
    path[0] = 0;

    if (!hamCycleUtil(1)) {
        printf("No Hamiltonian cycle exists.\n");
        return false;
    }

    printf("Hamiltonian Cycle exists:\n");
    for (int i = 0; i < n; i++)
        printf("%d -> ", path[i]);
    printf("%d\n", path[0]);  // complete the cycle

    return true;
}

int main() {
    int e, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter %d edges (u v):\n", e);
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; // Undirected graph
    }

    hamCycle();

    return 0;
}
