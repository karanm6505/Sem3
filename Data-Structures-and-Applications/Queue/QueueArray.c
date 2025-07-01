#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef struct queue
{
    int f, r;
    int q[SIZE];
}Queue;
int isEmpty(Queue* q)
{
    return (q->f == -1);
}
int isFull(Queue* q)
{
    return (q->r == SIZE - 1);

}
int peek(Queue* q)
{
    if(isEmpty(q))
    {
        return -1;
    }
    return q->q[q->f];
}
Queue* initQueue()
{
    Queue* newQ = malloc(sizeof(Queue));
    newQ->f = -1;
    newQ->r = -1;
    return newQ;
}
Queue* enqueue(Queue* q, int ele)
{
    if(isFull(q))
    {
        printf("OVERFLOW\n");
        return q;
    }
    if(isEmpty(q))
        q->f = 0;
    q->q[++q->r] = ele;
    return q;
}
Queue* dequeue(Queue* q)
{
    if(isEmpty(q))
    {
        printf("UNDERFLOW\n");
        return q;
    }
    printf("Dequeued element: %d\n", q->q[q->f]);
    if(q->f == q->r) //IF ONLY ONE ELEMENT IN THE QUEUE, dequeue and set to empty.
    {
        q->f = q->r = -1;  
    }
    else
    {
        q->f++;
    }
    return q;
}
void displayQueue(Queue* q)
{
    if(isEmpty(q))
    {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for(int i = q->f; i <= q->r; i++)
    {
        printf("%d ", q->q[i]);
    }
    printf("\n");
}
int main()
{
    Queue* q = initQueue();
    int choice, element;
    
    while(1) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Peek\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter element to enqueue: ");
                scanf("%d", &element);
                q = enqueue(q, element);
                break;
                
            case 2:
                q = dequeue(q);
                break;
                
            case 3:
                displayQueue(q);
                break;
                
            case 5:
                free(q);
                return 0;
                
            case 4:
                element = peek(q);
                if(element != -1)
                    printf("Front element: %d\n", element);
                else
                    printf("Queue is empty\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}