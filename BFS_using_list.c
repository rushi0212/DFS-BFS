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

// Structure for a queue node
struct QueueNode {
    int data;
    struct QueueNode* next;
};

// Structure for the queue
struct Queue {
    struct QueueNode *front, *rear;
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

// Function to create a new queue node
struct QueueNode* createQueueNode(int data) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue a node to the queue
void enqueue(struct Queue* queue, int data) {
    struct QueueNode* newNode = createQueueNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to dequeue a node from the queue
int dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return -1; // Queue is empty
    }
    struct QueueNode* temp = queue->front;
    int data = temp->data;
    queue->front = temp->next;
    free(temp);

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return data;
}

// Function to perform BFS traversal
void BFS(struct Graph* graph, int startVertex) {
    // Create a boolean array to track visited vertices
    int* visited = (int*)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; ++i) {
        visited[i] = 0;
    }

    // Create a queue for BFS
    struct Queue* queue = createQueue();

    // Mark the current node as visited and enqueue it
    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    // Loop to visit all vertices in BFS order
    while (queue->front != NULL) {
        // Dequeue a vertex from the queue and print it
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        // Get all adjacent vertices of the dequeued vertex
        struct Node* temp = graph->array[currentVertex].head;
        while (temp != NULL) {
            int adjVertex = temp->vertex;

            // If the adjacent vertex is not visited, mark it as visited and enqueue it
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }

            temp = temp->next;
        }
    }

    // Free allocated memory
    free(visited);
    free(queue);
}

int main() {
    int vertices = 6; // 6 vertices for a sample graph
    struct Graph* graph = createGraph(vertices);

    // Add edges to represent the graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    printf("Breadth-First Traversal starting from vertex 0: ");
    BFS(graph, 0);

    // Free allocated memory
    free(graph);

    return 0;
}
