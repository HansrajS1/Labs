#include <stdio.h>

#define MAX_PROCESSES 100


typedef struct {
    int id;         
    int burstTime;  
    int waitingTime; 
    int turnaroundTime; 
} Process;

void calculateTimes(Process processes[], int n) {
    int i;
    processes[0].waitingTime = 0;
    processes[0].turnaroundTime = processes[0].burstTime;

    for (i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i-1].waitingTime + processes[i-1].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}


void printProcesses(Process processes[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
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

    // Input process IDs and burst times
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; // Assuming process IDs start from 1
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    // Calculate waiting time and turnaround time
    calculateTimes(processes, n);

    // Print process details and averages
    printProcesses(processes, n);

    return 0;
}


