#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 100
#define MAX_VERTICES 100

// Edge structure
typedef struct {
    int source, destination, weight;
} Edge;

typedef struct {
    Edge edges[MAX_EDGES];
    int vertices, edges_count;
} Graph;

// Subset structure for Union-Find
typedef struct {
    int parent, rank;
} Subset;

int compareEdges(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->weight - edgeB->weight;
}

// Find the set of an element i (uses path compression)
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Union of two sets x and y (uses union by rank)
void Union(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Function to find MST using Kruskal's algorithm
void kruskalMST(Graph *graph) {
    int vertices = graph->vertices;
    Edge result[MAX_VERTICES];
    int resultCount = 0;

    // Step 1: Sort all the edges in non-decreasing order of weight
    qsort(graph->edges, graph->edges_count, sizeof(Edge), compareEdges);

    // Allocate memory for creating subsets
    Subset *subsets = (Subset *)malloc(vertices * sizeof(Subset));

    // Create subsets with single elements
    for (int v = 0; v < vertices; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is vertices - 1
    int i = 0;
    while (resultCount < vertices - 1 && i < graph->edges_count) {
        Edge nextEdge = graph->edges[i++];

        int x = find(subsets, nextEdge.source);
        int y = find(subsets, nextEdge.destination);

        // If including this edge does not cause a cycle, include it in the result
        if (x != y) {
            result[resultCount++] = nextEdge;
            Union(subsets, x, y);
        }
    }

    // Print the resultant MST
    printf("Edges in the Minimum Spanning Tree:\n");
    int totalWeight = 0;
    for (i = 0; i < resultCount; i++) {
        printf("%d -- %d == %d\n", result[i].source, result[i].destination, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total weight of MST: %d\n", totalWeight);

    // Free memory
    free(subsets);
}

// Function to add an edge to the graph
void addEdge(Graph *graph, int source, int destination, int weight) {
    graph->edges[graph->edges_count].source = source;
    graph->edges[graph->edges_count].destination = destination;
    graph->edges[graph->edges_count].weight = weight;
    graph->edges_count++;
}

int main() {
    Graph graph;
    int vertices, edges;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    graph.vertices = vertices;
    graph.edges_count = 0;

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges in the format: source destination weight\n");
    for (int i = 0; i < edges; i++) {
        int source, destination, weight;
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &source, &destination, &weight);
        addEdge(&graph, source, destination, weight);
    }

    kruskalMST(&graph);

    return 0;
}

