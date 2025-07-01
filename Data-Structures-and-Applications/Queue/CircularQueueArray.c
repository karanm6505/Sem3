#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
typedef struct queue
{
    int f, r;
    int q[SIZE];
}CircularQueue;
int isEmpty(CircularQueue* cq)
{
    return (cq->f == -1);
}
int isFull(CircularQueue* cq)
{
    return ((cq->r + 1) % SIZE == cq->f);  // Fixed syntax error with parentheses
}
int peek(CircularQueue* cq)
{
    if(isEmpty(cq))
    {
        return -1;
    }
    return cq->q[cq->f];
}
CircularQueue* initQueue()
{
    CircularQueue* newQ = malloc(sizeof(CircularQueue));
    newQ->f = -1;
    newQ->r = -1;
    return newQ;
}
CircularQueue* enqueue(CircularQueue* cq, int ele)
{
    if(isFull(cq))
    {
        printf("OVERFLOW\n");
        return cq;
    }
    if(isEmpty(cq))
        cq->f = 0;
    cq->r = (cq->r + 1) % SIZE;  // Add this line to update rear
    cq->q[cq->r] = ele;
    return cq;
}
CircularQueue* dequeue(CircularQueue* cq)
{
    if(isEmpty(cq))
    {
        printf("UNDERFLOW\n");
        return cq;
    }
    printf("Dequeued element: %d\n", cq->q[cq->f]);
    if(cq->f == cq->r) //IF ONLY ONE ELEMENT IN THE QUEUE, dequeue and set to empty.
    {
        cq->f = cq->r = -1;  
    }
    else
    {
        cq->f = (cq->f + 1)%SIZE;
    }
    return cq;
}
void displayQueue(CircularQueue* cq)
{
    if(isEmpty(cq))
    {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    int i = cq->f;
    do {
        printf("%d ", cq->q[i]);
        i = (i + 1) % SIZE;
    } while(i != (cq->r + 1) % SIZE);
    printf("\n");
}
int main()
{
    CircularQueue* cq = initQueue();
    int choice, element;
    
    while(1)
    {
        printf("\n=== Circular Queue Operations ===\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Peek\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1:
                printf("Enter element to enqueue: ");
                scanf("%d", &element);
                cq = enqueue(cq, element);
                break;
                
            case 2:
                cq = dequeue(cq);
                break;
                
            case 3:
                displayQueue(cq);
                break;
                
            case 4:
                element = peek(cq);
                if(element != -1)
                    printf("Front element: %d\n", element);
                else
                    printf("Queue is empty\n");
                break;
                
            case 5:
                free(cq);
                printf("Exiting program......\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}