#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int id, arrival_time, burst_time, waiting_time, turnaround_time;
} Process;


void fcfs(Process processes[], int n, int *current_time) {
    for (int i = 0; i < n; i++) {
        if (*current_time < processes[i].arrival_time) {
            *current_time = processes[i].arrival_time;
        }
        processes[i].waiting_time = *current_time - processes[i].arrival_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        *current_time += processes[i].burst_time;
        printf("P%d -> ", processes[i].id);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process queue1[MAX_PROCESSES], queue2[MAX_PROCESSES];
    int n1 = 0, n2 = 0;

    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        int id, arrival, burst;
        printf("Process P%d Arrival Time & Burst Time: ", i);
        scanf("%d %d", &arrival, &burst);
        
       
        if (i == 0 || i == 1 || i == 4) { 
            queue1[n1++] = (Process){i, arrival, burst, 0, 0};
        } else {  
            queue2[n2++] = (Process){i, arrival, burst, 0, 0};
        }
    }

    int current_time = 0;
    printf("\nExecution Order: ");

   
    fcfs(queue1, n1, &current_time);

    fcfs(queue2, n2, &current_time);

    printf("Done\n");

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    float avg_waiting_time = 0, avg_turnaround_time = 0;

    for (int i = 0; i < n1; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", queue1[i].id, queue1[i].arrival_time, queue1[i].burst_time, queue1[i].waiting_time, queue1[i].turnaround_time);
        avg_waiting_time += queue1[i].waiting_time;
        avg_turnaround_time += queue1[i].turnaround_time;
    }

    for (int i = 0; i < n2; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", queue2[i].id, queue2[i].arrival_time, queue2[i].burst_time, queue2[i].waiting_time, queue2[i].turnaround_time);
        avg_waiting_time += queue2[i].waiting_time;
        avg_turnaround_time += queue2[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time / n);

    return 0;
}
