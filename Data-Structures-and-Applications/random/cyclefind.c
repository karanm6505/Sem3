#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_VERTICES 100000

int parent[MAX_VERTICES + 1];
int rank[MAX_VERTICES + 1];

// Function to find the root of a vertex with path compression
int find(int v) {
    if (parent[v] != v) {
        parent[v] = find(parent[v]);
    }
    return parent[v];
}

// Function to perform union of two subsets with union by rank
int union_sets(int v1, int v2) {
    int root1 = find(v1);
    int root2 = find(v2);

    if (root1 != root2) {
        if (rank[root1] > rank[root2]) {
            parent[root2] = root1;
        } else if (rank[root1] < rank[root2]) {
            parent[root1] = root2;
        } else {
            parent[root2] = root1;
            rank[root1]++;
        }
        return 0; // No cycle
    }
    return 1; // Cycle detected
}

// Function to check if a cycle exists in the graph
int has_cycle(int V, int E) {
    int v1, v2;
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &v1, &v2);
        if (union_sets(v1, v2)) {
            return 1; // Cycle detected
        }
    }
    return 0; // No cycle
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);

    // Initialize each vertex as its own parent (disjoint set)
    for (int i = 1; i <= V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // Check if the graph has a cycle
    if (has_cycle(V, E)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}