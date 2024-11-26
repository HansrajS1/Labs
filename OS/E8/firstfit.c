#include<stdio.h>
void firstfit(int blocksize[], int m, int processsize[], int n)
{
    int allocation[10]; 
    int i, j;
    for (i = 0; i < n; i++)
        allocation[i] = -1;
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < m; j++) 
        {
            if (blocksize[j] >= processsize[i]) 
            {
                allocation[i] = j;
                blocksize[j] -= processsize[i];
                break; 
            }
        }
    }
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < n; i++) 
    {
        printf(" %d\t\t%d\t\t", i + 1, processsize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1); 
        else
            printf("Not Allocated\n");
    }
}
int main()
{
    int m, n;
    int blocksize[] = {100, 500, 200, 300, 600}; 
    int processsize[] = {212, 417, 112, 426};    
    m = sizeof(blocksize) / sizeof(blocksize[0]);
    n = sizeof(processsize) / sizeof(processsize[0]);
    firstfit(blocksize, m, processsize, n);
    return 0;
}