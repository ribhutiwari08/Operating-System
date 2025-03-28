#include <stdio.h>

typedef struct {
    int id, arrival_time, burst_time, waiting_time, turnaround_time, completed;
    float response_ratio;
} Process;

void sortByArrival(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, time = 0, completed = 0;
    float avg_waiting_time = 0, avg_turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process p[n];

    printf("\nEnter process details (Arrival Time & Burst Time):\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d Arrival & Burst Time: ", i);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].id = i;
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
        p[i].completed = 0;
    }

    sortByArrival(p, n);

    printf("\nExecution Order: ");

    while (completed < n) {
        int highest_response_index = -1;
        float max_response_ratio = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].completed) {
                p[i].waiting_time = time - p[i].arrival_time;
                p[i].response_ratio = (float)(p[i].waiting_time + p[i].burst_time) / p[i].burst_time;

                if (p[i].response_ratio > max_response_ratio) {
                    max_response_ratio = p[i].response_ratio;
                    highest_response_index = i;
                }
            }
        }

        if (highest_response_index == -1) {
            time++;
            continue;
        }

        int idx = highest_response_index;
        printf("P%d -> ", p[idx].id);

        time += p[idx].burst_time;
        p[idx].turnaround_time = time - p[idx].arrival_time;
        p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
        p[idx].completed = 1;

        avg_waiting_time += p[idx].waiting_time;
        avg_turnaround_time += p[idx].turnaround_time;

        completed++;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\n\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
