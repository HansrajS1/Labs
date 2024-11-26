#include <stdio.h>
#define MAX_PROCESSES 100

typedef struct {
    int id;                
    int burstTime;         
    int arrivalTime;        
    int waitingTime;        
    int turnaroundTime;     
} Process;


void sortProcesses(Process processes[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[j].arrivalTime < processes[i].arrivalTime ||
                (processes[j].arrivalTime == processes[i].arrivalTime &&
                 processes[j].burstTime < processes[i].burstTime)) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp; 
            }
        }
    }
}

void calculateTimes(Process processes[], int n) {
    int i;
    int currentTime = 0;
    for (i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        currentTime += processes[i].burstTime;
    }
}

void printProcesses(Process processes[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("Process ID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id, processes[i].burstTime, processes[i].arrivalTime,
               processes[i].waitingTime, processes[i].turnaroundTime);
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    float averageWaitingTime = (float)totalWaitingTime / n;
    float averageTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("\nAverage Waiting Time: %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
}

int main() {
    Process processes[MAX_PROCESSES];
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n > MAX_PROCESSES || n <= 0) {
        printf("Invalid number of processes. Please enter a number between 1 and %d.\n", MAX_PROCESSES);
        return 1; 
    }

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; 
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);

        if (processes[i].burstTime <= 0) {
            printf("Burst time must be a positive integer.\n");
            return 1; 
        }

        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);

        if (processes[i].arrivalTime < 0) {
            printf("Arrival time must be a non-negative integer.\n");
            return 1; 
        }
    }
    sortProcesses(processes, n);
    calculateTimes(processes, n);
    printProcesses(processes, n);
    return 0;
}

