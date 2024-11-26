#include<stdio.h>

struct priority {
    int pid, bt, pt, waiting_time, turnaround_time;
}s[10];

int main() {
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Enter the process id: ");
        scanf("%d", &s[i].pid);
        
        printf("Enter the burst time: ");
        scanf("%d", &s[i].bt);
        
        printf("Enter the priority: ");
        scanf("%d", &s[i].pt);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (s[i].pt > s[j].pt) {
                struct priority temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
    	
        
    s[0].waiting_time = 0;
    s[0].turnaround_time = s[0].bt;
    
    
    for (int i = 1; i < n; i++) {
        s[i].waiting_time = s[i-1].waiting_time + s[i-1].bt;
        s[i].turnaround_time = s[i].waiting_time + s[i].bt;
    }
    
    printf("Process ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", s[i].pid, s[i].bt, s[i].pt, s[i].waiting_time, s[i].turnaround_time);
    }
    
    return 0;
}

