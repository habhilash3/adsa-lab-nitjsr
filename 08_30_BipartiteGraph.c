#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int adj[MAX][MAX];  // adjacency matrix
int color[MAX];     // stores color of each vertex (0 or 1)

bool isBipartite(int n) {
    for (int start = 0; start < n; start++) {
        if (color[start] == -1) {  // uncolored vertex
            int queue[MAX], front = 0, rear = 0;
            queue[rear++] = start;
            color[start] = 0;  // assign first color

            while (front < rear) {
                int u = queue[front++];

                for (int v = 0; v < n; v++) {
                    if (adj[u][v]) { // if edge exists
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            queue[rear++] = v;
                        } else if (color[v] == color[u]) {
                            return false; // same color on both ends
                        }
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    int n, e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // initialize adjacency matrix and color array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;
        color[i] = -1;
    }

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    if (isBipartite(n))
        printf("The graph is Bipartite.\n");
    else
        printf("The graph is NOT Bipartite.\n");

    return 0;
}
