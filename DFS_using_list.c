#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure for the adjacency list
struct AdjList {
    struct Node* head;
};

// Structure for the graph
struct Graph {
    int vertices;
    struct AdjList* array;
};

// Function to create a new node
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;

    // Create an array of adjacency lists
    graph->array = (struct AdjList*)malloc(vertices * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by setting head to NULL
    for (int i = 0; i < vertices; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Recursive function for depth-first search
void DFSUtil(struct Graph* graph, int vertex, int* visited) {
    // Mark the current node as visited
    visited[vertex] = 1;
    printf("%d ", vertex);

    // Traverse all the adjacent vertices
    struct Node* temp = graph->array[vertex].head;
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            // If the adjacent vertex is not visited, recursively call DFS on it
            DFSUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

// Function to perform depth-first search on the graph
void DFS(struct Graph* graph, int startVertex) {
    // Array to keep track of visited vertices
    int* visited = (int*)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; ++i) {
        visited[i] = 0;
    }

    // Call the recursive helper function
    DFSUtil(graph, startVertex, visited);

    free(visited);
}

int main() {
    int vertices = 6; // 6 vertices for a sample graph
    struct Graph* graph = createGraph(vertices);

    // Add edges to the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);

    // Perform depth-first search starting from vertex 0
    printf("DFS starting from vertex 0: ");
    DFS(graph, 0);

    // Release allocated memory
    free(graph->array);
    free(graph);

    return 0;
}
