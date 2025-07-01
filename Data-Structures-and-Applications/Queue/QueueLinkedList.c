#include <stdio.h>
#include <stdlib.h>


typedef struct QN
{
    int ele;
    struct QN* next;
}QueueNode;
typedef struct queue
{
    QueueNode* front;
    QueueNode* rear;
}Queue;
QueueNode* createNode(int ele)
{
    QueueNode* QueueNode = malloc(sizeof(QueueNode));
    QueueNode->ele = ele;
    QueueNode->next = NULL;
    return QueueNode;
}
Queue* initQueue()
{
    Queue* newQ = malloc(sizeof(Queue));
    newQ->front = NULL;
    newQ->rear = NULL;
    return newQ;
}
Queue* enqueue(Queue* q, int ele)
{
    QueueNode* newNode = createNode(ele);
    if(q->front == NULL)  // Empty queue
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else  // Non-empty queue
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    return q;
}
Queue* dequeue(Queue* q)
{
    if(q->front == NULL)  // Empty queue
        return q;
    
    QueueNode* temp = q->front;
    printf("Dequeued element: %d\n",temp->ele);
    q->front = q->front->next;
    
    // If queue becomes empty after dequeue
    if(q->front == NULL)
        q->rear = NULL;
        
    free(temp);  // Free the dequeued node
    return q;
}
void displayQueue(Queue* q)
{
    if(q->front == NULL) 
    {
        printf("Empty queue\n");
        return;
    }
    
    QueueNode* temp = q->front;
    while(temp != NULL) 
    {
        printf("%d ", temp->ele);
        temp = temp->next;
    }
    printf("\n");
}
int main()
{
    Queue* q = initQueue();
    int choice, element;
    
    while(1) {
        printf("\n1. Enqueue");
        printf("\n2. Dequeue");
        printf("\n3. Display");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
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
                
            case 4:
                exit(0);
                
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}