#include <stdio.h>
#define MAX_NODES 10
#define NO_EDGE 0

void initializeGraph(int graph[MAX_NODES][MAX_NODES], int nodes) {
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            graph[i][j] = NO_EDGE;
        }
    }
}

void addEdge(int graph[MAX_NODES][MAX_NODES], int u, int v, int weight) {
    if (u >= 0 && u < MAX_NODES && v >= 0 && v < MAX_NODES) {
        graph[u][v] = weight;
        printf("Edge added from %d to %d with weight %d.\n", u, v, weight);
    } else {
        printf("Invalid nodes!\n");
    }
}

void deleteEdge(int graph[MAX_NODES][MAX_NODES], int u, int v) {
    if (graph[u][v] != NO_EDGE) {
        graph[u][v] = NO_EDGE;
        printf("Edge deleted from %d to %d.\n", u, v);
    } else {
        printf("Edge does not exist.\n");
    }
}

void searchEdge(int graph[MAX_NODES][MAX_NODES], int u, int v) {
    if (graph[u][v] != NO_EDGE) {
        printf("Edge from %d to %d with weight %d exists.\n", u, v, graph[u][v]);
    } else {
        printf("No edge from %d to %d.\n", u, v);
    }
}

void traverseGraph(int graph[MAX_NODES][MAX_NODES], int nodes) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int nodes;
    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);

    if (nodes > MAX_NODES) {
        printf("Maximum nodes exceeded.\n");
        return 1;
    }

    int graph[MAX_NODES][MAX_NODES];
    initializeGraph(graph, nodes);
    printf("\nChoose an operation for directional graph:\n");
    printf("1. Add edge\n2. Delete edge\n3. Search edge\n4. Traverse graph\n5. Exit\n");

    int choice, u, v, weight;
    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the start node, end node, and weight (u v weight) for the edge: ");
                scanf("%d %d %d", &u, &v, &weight);
                addEdge(graph, u, v, weight);
                break;
            case 2:
                printf("Enter the start and end nodes (u v) of the edge to delete: ");
                scanf("%d %d", &u, &v);
                deleteEdge(graph, u, v);
                break;
            case 3:
                printf("Enter the start and end nodes (u v) to search: ");
                scanf("%d %d", &u, &v);
                searchEdge(graph, u, v);
                break;
            case 4:
                traverseGraph(graph, nodes);
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
