#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_VERTICES 1000

int visited[MAX_VERTICES + 1];
int adj[MAX_VERTICES + 1][MAX_VERTICES + 1];
int V, E;

// Function to populate the adjacency matrix
void populate_adjacency_matrix() {
    int u, v;
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
}

// Depth-First Search (DFS) to mark all nodes in a connected component
void dfs(int v) {
    visited[v] = 1;
    for (int i = 1; i <= V; i++) {
        if (adj[v][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

// Function to count connected components
int count_connected_components() {
    int count = 0;
    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            dfs(i);
            count++;
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &V, &E);

    // Initialize adjacency matrix and visited array
    for (int i = 0; i <= V; i++) {
        visited[i] = 0;
        for (int j = 0; j <= V; j++) {
            adj[i][j] = 0;
        }
    }

    // Populate the adjacency matrix using the function
    populate_adjacency_matrix();

    // Count and print the number of connected components
    int components = count_connected_components();
    printf("%d\n", components);

    return 0;
}