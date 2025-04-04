#include <stdio.h>
#include <stdbool.h>

#define MAX 10  

int rag[MAX][MAX];  
int visited[MAX], recStack[MAX]; 
int nodes;

bool detectCycle(int v) {
    visited[v] = 1;
    recStack[v] = 1;

    for (int i = 0; i < nodes; i++) {
        if (rag[v][i]) { 
            if (!visited[i] && detectCycle(i))
                return true;
            else if (recStack[i])
                return true;
        }
    }

    recStack[v] = 0;
    return false;
}

bool isDeadlocked() {
    for (int i = 0; i < nodes; i++) {
        visited[i] = recStack[i] = 0;
    }

    for (int i = 0; i < nodes; i++) {
        if (!visited[i] && detectCycle(i))
            return true;
    }
    return false;
}

int main() {
    int processes, resources;
    
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);

    nodes = processes + resources;

    printf("\nEnter number of edges (process → resource or resource → process): ");
    int edges;
    scanf("%d", &edges);

    printf("Enter edges (from to) where P0 = 0, R0 = %d:\n", processes);
    for (int i = 0; i < edges; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        rag[from][to] = 1;
    }

    if (isDeadlocked())
        printf("\n Deadlock Detected (Cycle in RAG)\n");
    else
        printf("\n No Deadlock (No Cycle in RAG)\n");

    return 0;
}
