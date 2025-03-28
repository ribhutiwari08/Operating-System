#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10
#define TIME_QUANTUM_1 4
#define TIME_QUANTUM_2 8

typedef struct {
    int id, arrival_time, burst_time, remaining_time, waiting_time, turnaround_time, queue_level;
} Process;


void roundRobin(Process processes[], int n, int time_quantum, int queue_level) {
    int time = 0, completed = 0;
    
    while (completed < n) {
        int all_done = 1;
        for (int i = 0; i < n; i++) {
            if (processes[i].queue_level == queue_level && processes[i].remaining_time > 0) {
                all_done = 0;
                if (processes[i].remaining_time > time_quantum) {
                    time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                    printf("P%d -> ", processes[i].id);
                    
                   
                    processes[i].queue_level++;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].waiting_time = time - processes[i].arrival_time - processes[i].burst_time;
                    processes[i].turnaround_time = time - processes[i].arrival_time;
                    processes[i].remaining_time = 0;
                    printf("P%d (Done) -> ", processes[i].id);
                    completed++;
                }
            }
        }
        if (all_done) break;
    }
}


void fcfs(Process processes[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].queue_level == 3 && processes[i].remaining_time > 0) {
            time += processes[i].remaining_time;
            processes[i].waiting_time = time - processes[i].arrival_time - processes[i].burst_time;
            processes[i].turnaround_time = time - processes[i].arrival_time;
            processes[i].remaining_time = 0;
            printf("P%d (Done) -> ", processes[i].id);
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[MAX_PROCESSES];

    printf("\nEnter process details (Arrival Time & Burst Time):\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d Arrival & Burst Time: ", i);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].id = i;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].queue_level = 1; 
    }

    printf("\nExecution Order: ");
    
   
    roundRobin(processes, n, TIME_QUANTUM_1, 1);
    
   
    roundRobin(processes, n, TIME_QUANTUM_2, 2);
    
  
    fcfs(processes, n);

    printf("\n\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time / n);

    return 0;
}
