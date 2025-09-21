#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int timeCounter;

// Graph adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

struct Node* adj[MAX]; // adjacency list
int visited[MAX], disc[MAX], finish[MAX];
int parent[MAX];

// Add edge to adjacency list (directed graph)
void addEdge(int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

// DFS utility
void DFS_Visit(int u, int V) {
    visited[u] = 1;
    disc[u] = ++timeCounter; // discovery time

    struct Node* temp = adj[u];
    while (temp) {
        int v = temp->vertex;

        if (!visited[v]) {
            printf("Tree Edge: %d -> %d\n", u, v);
            parent[v] = u;
            DFS_Visit(v, V);
        } else {
            if (finish[v] == 0) {
                // v discovered but not finished
                printf("Back Edge: %d -> %d\n", u, v);
            } else {
                if (disc[u] < disc[v])
                    printf("Forward Edge: %d -> %d\n", u, v);
                else
                    printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
        temp = temp->next;
    }

    finish[u] = ++timeCounter; // finishing time
}

// DFS for all vertices
void DFS(int V) {
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        parent[i] = -1;
        disc[i] = finish[i] = 0;
    }
    timeCounter = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            DFS_Visit(i, V);
        }
    }
}

// Example usage
int main() {
    int V = 6;

    // Initialize adjacency list
    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
    }

    // Example directed graph
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 3);
    addEdge(3, 4);
    addEdge(4, 5);
    addEdge(5, 3); // back edge
    addEdge(2, 5); // cross/forward depending on traversal

    printf("DFS Edge Classification:\n");
    DFS(V);

    return 0;
}
