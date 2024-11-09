#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define INF INT_MAX  // Define infinite distance

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], int sptSet[], int V) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

// Function to print the shortest path from source to each vertex
void printSolution(int dist[], int V) {
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Dijkstra's algorithm to find the shortest path from source to all vertices
void dijkstra(int **graph, int src, int V) {
    int dist[V];  // Array to hold the shortest distance from source to each vertex
    int sptSet[V];  // Array to keep track of vertices in the shortest path tree

    // Initialize distances and sptSet arrays
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
    }

    dist[src] = 0;  // Distance from source to itself is always 0

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);  // Pick the minimum distance vertex not in sptSet
        sptSet[u] = 1;  // Mark the picked vertex as processed

        // Update dist[v] only if it's not in sptSet, there's an edge from u to v,
        // and the total weight of path from src to v through u is smaller than dist[v]
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INF
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
    }

    // Print the constructed distance array
    printSolution(dist, V);
}

// Main function to test the algorithm
int main() {
    int V;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    // Dynamically allocate memory for the adjacency matrix
    int **graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        graph[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;  // Initialize with 0, indicating no edge
        }
    }

    int edges;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge with its weight (format: source destination weight):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        graph[src][dest] = weight;  // Add edge from src to dest with the given weight
    }

    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);

    dijkstra(graph, source, V);

    // Free allocated memory
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
