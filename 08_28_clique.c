#include <stdio.h>
#include <stdbool.h>

#define MAX 20  // Maximum number of vertices

int graph[MAX][MAX];
int n, e, m;
int clique[MAX];

// Function to check if the current vertex can be added to the clique
bool is_clique(int b)
{
    for (int i = 0; i < b; i++) {
        for (int j = i + 1; j < b; j++) {
            if (graph[clique[i]][clique[j]] == 0)
                return false;
        }
    }
    return true;
}

// Recursive utility to check all combinations
bool find_clique(int start, int depth)
{
    // If current size = m → clique found
    if (depth == m)
        return true;

    for (int i = start; i < n; i++) {
        clique[depth] = i;

        if (is_clique(depth + 1)) {
            if (find_clique(i + 1, depth + 1))
                return true;
        }
    }
    return false;
}

int main()
{
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);

    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    // Initialize adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;  // undirected graph
    }

    printf("Enter clique size (m): ");
    scanf("%d", &m);

    if (find_clique(0, 0))
        printf("Graph contains a clique of size %d\n", m);
    else
        printf("Graph does NOT contain a clique of size %d\n", m);

    return 0;
}
