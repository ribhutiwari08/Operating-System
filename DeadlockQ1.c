#include <stdio.h>
#include <stdbool.h>

#define P 2
#define R 3

int available[R];
int maximum[P][R];
int allocation[P][R];
int need[P][R];

bool isSafeState()
{
    bool finish[P] = {false};
    int work[R];
    for (int i = 0; i < R; i++)
        work[i] = available[i];

    int count = 0;
    while (count < P)
    {
        bool found = false;
        for (int i = 0; i < P; i++)
        {
            if (!finish[i])
            {
                bool canAllocate = true;
                for (int j = 0; j < R; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];

                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

bool requestResources(int process, int request[R])
{
    for (int j = 0; j < R; j++)
    {
        if (request[j] > need[process][j] || request[j] > available[j])
            return false;
    }

    for (int j = 0; j < R; j++)
    {
        available[j] -= request[j];
        allocation[process][j] += request[j];
        need[process][j] -= request[j];
    }

    if (isSafeState())
    {
        printf("Request granted for P%d.\n", process);
        return true;
    }
    else
    {

        for (int j = 0; j < R; j++)
        {
            available[j] += request[j];
            allocation[process][j] -= request[j];
            need[process][j] += request[j];
        }
        printf("Request denied for P%d (unsafe state).\n", process);
        return false;
    }
}

int main()
{
    printf("Enter available resources: ");
    for (int i = 0; i < R; i++)
        scanf("%d", &available[i]);

    printf("Enter maximum resource demand for each process:\n");
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
            scanf("%d", &maximum[i][j]);
    }

    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    int process;
    printf("Enter process number (0-%d) making a request: ", P - 1);
    scanf("%d", &process);

    int request[R];
    printf("Enter requested resources: ");
    for (int i = 0; i < R; i++)
        scanf("%d", &request[i]);

    requestResources(process, request);

    return 0;
}
