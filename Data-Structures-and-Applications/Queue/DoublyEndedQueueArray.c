#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct
{
    int arr[MAX];
    int front, rear;
} DEqueue;
void initialize(DEqueue *dq) 
{
    dq->front = dq->rear = -1;
}
int isFull(DEqueue *dq)
{
    return ((dq->front == 0 && dq->rear == MAX-1) || (dq->front == dq->rear + 1));
}
int isEmpty(DEqueue *dq) 
{
    return (dq->front == -1);
}
DEqueue* insertFront(DEqueue *dq, int value)
{
    if (isFull(dq))
    {
        printf("Queue is full!\n");
        return dq;
    }
    if (dq->front == -1) 
    {
        dq->front = dq->rear = 0;
    }
    else if (dq->front == 0) 
    {
        dq->front = MAX - 1;
    }
    else 
    {
        dq->front--;
    }
    dq->arr[dq->front] = value;
    return dq;
}
DEqueue* insertRear(DEqueue *dq, int value)
{
    if (isFull(dq)) 
    {
        printf("Queue is full!\n");
        return dq;
    }
    if (dq->front == -1) 
    {
        dq->front = dq->rear = 0;
    }
    else if (dq->rear == MAX-1) 
    {
        dq->rear = 0;
    }
    else 
    {
        dq->rear++;
    }
    dq->arr[dq->rear] = value;
    return dq;
}
DEqueue* deleteFront(DEqueue *dq) 
{
    if (isEmpty(dq)) 
    {
        printf("Queue is empty!\n");
        return dq;
    }
    printf("Deleted element from front: %d\n", dq->arr[dq->front]);
    if (dq->front == dq->rear) 
    {
        dq->front = dq->rear = -1;
    }
    else if (dq->front == MAX-1) 
    {
        dq->front = 0;
    }
    else 
    {
        dq->front++;
    }
    return dq;
}
DEqueue* deleteRear(DEqueue *dq) 
{
    if (isEmpty(dq))
    {
        printf("Queue is empty!\n");
        return dq;
    }
    printf("Deleted element from rear: %d\n", dq->arr[dq->rear]);
    if (dq->front == dq->rear) 
    {
        dq->front = dq->rear = -1;
    }
    else if (dq->rear == 0) 
    {
        dq->rear = MAX-1;
    }
    else 
    {
        dq->rear--;
    }
    return dq;
}
void display(DEqueue *dq)
{
    if (isEmpty(dq))
    {
        printf("Queue is empty!\n");
        return;
    }
    int i = dq->front;
    printf("Deque elements: ");
    if (dq->front <= dq->rear) 
    {
        while (i <= dq->rear)
            printf("%d ", dq->arr[i++]);
    }
    else 
    {
        while (i < MAX)
            printf("%d ", dq->arr[i++]);
        i = 0;
        while (i <= dq->rear)
            printf("%d ", dq->arr[i++]);
    }
    printf("\n");
}
int main() 
{
    DEqueue dq;
    initialize(&dq);
    int choice, element;
    
    while(1) {
        printf("\nDouble Ended Queue Operations:");
        printf("\n1. Insert at Front");
        printf("\n2. Insert at Rear");
        printf("\n3. Delete from Front");
        printf("\n4. Delete from Rear");
        printf("\n5. Display");
        printf("\n6. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter element to insert at front: ");
                scanf("%d", &element);
                dq = *insertFront(&dq, element);
                break;
                
            case 2:
                printf("Enter element to insert at rear: ");
                scanf("%d", &element);
                dq = *insertRear(&dq, element);
                break;
                
            case 3:
                dq = *deleteFront(&dq);
                break;
                
            case 4:
                dq = *deleteRear(&dq);
                break;
                
            case 5:
                display(&dq);
                break;
                
            case 6:
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}