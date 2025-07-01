#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct 
{
    int info[MAX];
    int priority[MAX];
    int front, rear;
} PriorityQueue;
void initialize(PriorityQueue *pq) 
{
    pq->front = pq->rear = -1;
}
int isEmpty(PriorityQueue *pq) 
{
    return pq->front == -1;
}
int isFull(PriorityQueue *pq) 
{
    return pq->rear == MAX - 1;
}
PriorityQueue* enqueue(PriorityQueue *pq, int item, int priority)
{
    // Check if queue is full
    if(isFull(pq)) 
    {
        printf("Queue is full!\n");
        return pq;
    }

    // If queue is empty, insert at first position
    if(isEmpty(pq))
    {
        pq->front = pq->rear = 0;
        pq->info[0] = item;
        pq->priority[0] = priority;
        return pq;
    }

    // Find correct position based on priority
    int i;
    for(i = pq->rear; i >= pq->front; i--) 
    {
        if(priority > pq->priority[i]) 
        {
            // Shift elements right to make space
            pq->info[i+1] = pq->info[i];
            pq->priority[i+1] = pq->priority[i];
        } 
        else 
        {
            // Found position where priority is greater or equal
            break;
        }
    }
    
    // Insert at the correct position (i+1)
    pq->info[i+1] = item;
    pq->priority[i+1] = priority;
    pq->rear++;  // Increment rear
    return pq;
}
PriorityQueue* dequeue(PriorityQueue *pq)
{
    if(isEmpty(pq))
    {
        printf("Queue is empty!\n");
        return pq;
    }
    
    int item = pq->info[pq->front];
    printf("Dequeued element: %d\n", item);
    
    if(pq->front == pq->rear)
        pq->front = pq->rear = -1;
    else 
        pq->front++;
    
    return pq;
}
void display(PriorityQueue *pq)
{
    if(isEmpty(pq))
    {
        printf("Queue is empty!\n");
        return;
    }
    
    printf("\nQueue contents:\n");
    printf("Item\tPriority\n");
    for(int i = pq->front; i <= pq->rear; i++) {
        printf("%d\t%d\n", pq->info[i], pq->priority[i]);
    }
}
int main()
{
    PriorityQueue pq;
    initialize(&pq);
    int choice, item, priority;
    
    while(1) {
        printf("\nPriority Queue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter item to insert: ");
                scanf("%d", &item);
                printf("Enter priority: ");
                scanf("%d", &priority);
                pq = *enqueue(&pq, item, priority);
                break;
                
            case 2:
                pq = *dequeue(&pq);
                break;
                
            case 3:
                display(&pq);
                break;
                
            case 4:
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
```
/*
Priority Queue Struct 
- int info[MAX], int priority[MAX].
Insertion based on priority, maximum priority at first location followed by next.
Deletion, only the first location can be dequeued.
Display both info and priority
*/