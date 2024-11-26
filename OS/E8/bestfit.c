#include<stdio.h>
void bestfit(int blocksize[], int b[], int m, int processsize[], int n)
{
    int allocation[10]; 
    int i, j;
    for (i = 0; i < n; i++)
    {
        allocation[i] = -1;
         b[i] = blocksize[i]; 
    }
    for (i = 0; i < n; i++) 
    {
        int bestIdx = -1;
        for (j = 0; j < m; j++) 
        {
            if (blocksize[j] >= processsize[i]) 
            {
                if (bestIdx == -1 || blocksize[j] < blocksize[bestIdx])
                {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) 
        {
            allocation[i] = bestIdx;
            blocksize[bestIdx] -= processsize[i];
        }
    }
    printf("\nProcess No.\tProcess Size\tBlock Size\tBlock No.\n");
    for (i = 0; i < n; i++) 
    {
        printf(" %d\t\t%d\t\t%d\t\t", i + 1, processsize[i],b[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1); 
        else
            printf("Not Allocated\n");
    }
}
int main()
{
    int m, n,b[10];
    int blocksize[] = {100, 500, 200, 300, 600}; 
    int processsize[] = {212, 417, 112, 426,98}; 
     for (int i = 0; i < n; i++)
    {
         b[i] = blocksize[i]; 
    }   
    m = sizeof(blocksize) / sizeof(blocksize[0]);
    n = sizeof(processsize) / sizeof(processsize[0]);
    bestfit(blocksize,b, m, processsize, n);
    return 0;
}