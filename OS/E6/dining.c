#include <stdio.h>


int chopsticks[5] = {1, 1, 1, 1, 1}; 
int mutex = 1;                       
int philosophers = 5;                
int eating[5] = {0, 0, 0, 0, 0};     


void pick_chopsticks(int p) {
    --mutex;  
    if (eating[p] == 1) {
        printf("Philosopher %d is already eating. They cannot pick up chopsticks again.\n", p + 1);
    } else if (chopsticks[p] == 1 && chopsticks[(p + 1) % philosophers] == 1) {
        chopsticks[p] = chopsticks[(p + 1) % philosophers] = 0; 
        eating[p] = 1; 
        printf("Philosopher %d picks up chopsticks %d and %d\n", p + 1, p + 1, (p + 1) % philosophers + 1);
        printf("Philosopher %d is eating now\n", p + 1);
    } else {
        printf("Philosopher %d is waiting for chopsticks\n", p + 1);
    }
    ++mutex;  
}


void put_chopsticks(int p) {
    --mutex;
    if (eating[p] == 1) {
        chopsticks[p] = chopsticks[(p + 1) % philosophers] = 1;
        eating[p] = 0;  
        printf("Philosopher %d puts down chopsticks %d and %d\n", p + 1, p + 1, (p + 1) % philosophers + 1);
    } else {
        printf("Philosopher %d was not eating, so they cannot put down chopsticks\n", p + 1);
    }
    ++mutex;  
}
int main() {
    int n, p;
    printf("\n1. Pick Chopsticks\n2. Put Chopsticks\n3. Exit\n");
    while (1) {
        printf("Enter choice: ");
        scanf("%d", &n);

        if (n == 3) {
            printf("Exiting...\n");
            break;  
        }

        printf("Enter philosopher number from 1-5: ");
        scanf("%d", &p);
        
        if (p < 1 || p > 5) {
            printf("Invalid philosopher number. Please enter a number between 1 and 5.\n");
        } else {
            p -= 1; 
            switch (n) {
                case 1:
                    pick_chopsticks(p);
                    break;
                case 2:
                    put_chopsticks(p);
                    break;
                default:
                    printf("Invalid choice. Please enter 1, 2, or 3.\n");
                    break;
            }
        }
        printf("\n"); 
    }

    return 0;
}