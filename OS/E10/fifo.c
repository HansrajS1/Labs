#include <stdio.h>
int main() 
{
    int frames[10], pages[10], numPages, numFrames, faults = 0;
    int i, j, k, flag;
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);
    printf("Enter the page sequence: ");
    for (i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);
    for (i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }
    j = 0; 
    printf("\nPage replacement process:\n");
    for (i = 0; i < numPages; i++) {
        flag = 0;
        for (k = 0; k < numFrames; k++) {
            if (frames[k] == pages[i]) {
                flag = 1; 
                break;
            }
        }
        if (flag == 0) {
            frames[j] = pages[i]; 
            j = (j + 1) % numFrames; 
            faults++; 
        }
        for (k = 0; k < numFrames; k++) {
            if (frames[k] == -1) {
                printf(" - ");
            } else {
                printf(" %d ", frames[k]);
            }
        }
        printf("\n");
    }
    printf("\nTotal page faults: %d\n", faults);
    return 0;
}