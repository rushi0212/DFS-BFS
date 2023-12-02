#include <stdio.h>

#define MAX 100

int stack[MAX];
int top = -1;

// Function to push a vertex onto the stack
void push(int vertex) {
    if (top == MAX - 1) {
        printf("Stack overflow.\n");
    } else {
        top++;
        stack[top] = vertex;
    }
}

// Function to pop a vertex from the stack
int pop() {
    int vertex;
    if (top == -1) {
        printf("Stack underflow.\n");
        return -1;
    } else {
        vertex = stack[top];
        top--;
        return vertex;
    }
}

// Function to perform DFS traversal
void dfs(int adjacencyMatrix[MAX][MAX], int vertices, int startVertex, int visited[MAX]) {
    push(startVertex);

    while (top != -1) {
        int currentVertex = pop();

        if (visited[currentVertex] == 0) {
            printf("%d ", currentVertex);
            visited[currentVertex] = 1;
        }

        for (int i = vertices - 1; i >= 0; i--) {
            if (adjacencyMatrix[currentVertex][i] == 1 && visited[i] == 0) {
                push(i);
            }
        }
    }
}

int main() {
    int vertices, startVertex;
    int adjacencyMatrix[MAX][MAX];
    int visited[MAX] = {0};

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

    printf("DFS Traversal starting from vertex %d: ", startVertex);
    dfs(adjacencyMatrix, vertices, startVertex, visited);

    return 0;
}
