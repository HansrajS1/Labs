#include<stdio.h>
#include<stdlib.h>
int mutex=1,full=0,empty=3,x=0;
int main()
{
    int n;
    void producer();
    void consumer();
    int Wait(int);
    int Signal(int);
    printf("1.Producer\n2.Consumer\n3.Exit\n");
    while(1)
    {
        printf("\nEnter the choice:\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:if((mutex==1)&&(empty!=0))
                producer();
            else
                printf("Buffer is full");
                break;
            case 2:if((mutex==1)&&(full!=0))
                consumer();
            else
                printf("Buffer is empty"); 
                break;
            case 3:exit(0);
                break; 
        }
    }
    return 0;
}
int Wait(int s)
{
    return(--s);
}
int Signal(int s)
{
    return(++s);
}
void producer(){
    mutex=Wait(mutex);
    full=Signal(full);
    empty=Wait(empty);
    x++;
    printf("Producer produces the item %d",x);
    mutex=Signal(mutex);
}
void consumer(){
    mutex=Wait(mutex);
    full=Wait(full);
    empty=Signal(empty);
    printf("Consumer Consumes the item %d",x);
    x--;
    mutex=Signal(mutex);
}
