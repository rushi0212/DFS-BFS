#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int queue[MAX];
int front = -1, rear = -1;

// Function to enqueue a vertex in the queue
void enqueue(int vertex) {
    if (rear == MAX - 1) {
        printf("Queue is full.\n");
    } else {
        if (front == -1) {
            front = 0;
        }
        rear++;
        queue[rear] = vertex;
    }
}

// Function to dequeue a vertex from the queue
int dequeue() {
    int vertex;
    if (front == -1) {
        printf("Queue is empty.\n");
        return -1;
    } else {
        vertex = queue[front];
        front++;
        if (front > rear) {
            front = rear = -1;
        }
        return vertex;
    }
}

// Function to perform BFS traversal
void bfs(int adjacencyMatrix[MAX][MAX], int vertices, int startVertex) {
    int visited[MAX] = { 0 };
    printf("BFS Traversal starting from vertex %d: ", startVertex);
    
    // Mark the start vertex as visited and enqueue it
    visited[startVertex] = 1;
    enqueue(startVertex);
    
    while (front != -1) {
        int currentVertex = dequeue();
        printf("%d ", currentVertex);
        
        for (int i = 0; i < vertices; i++) {
            if (adjacencyMatrix[currentVertex][i] == 1 && visited[i]==0) {
                visited[i] = 1;
                enqueue(i);
            }
        }
    }
}

int main() {
    int vertices, startVertex;
    int adjacencyMatrix[MAX][MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }

    printf("Enter the start vertex: ");
    scanf("%d", &startVertex);

    bfs(adjacencyMatrix, vertices, startVertex);

    return 0;
}
