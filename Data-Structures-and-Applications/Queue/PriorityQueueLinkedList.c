#include <stdio.h>
#include <stdlib.h>

typedef struct PQNode
{
    int info;
    int priority;
    struct PQNode* next;
} PQNode;
typedef struct
{
    PQNode *front;
    PQNode *rear;
} PriorityQueue;
PQNode* createNode(int info, int prio)
{
    PQNode* newNode = malloc(sizeof(PQNode));
    newNode->info = info;
    newNode->priority = prio;
    newNode->next = NULL;
    return newNode;
}
PriorityQueue* initPQ() 
{
    PriorityQueue* pq = malloc(sizeof(PriorityQueue));
    pq->front = NULL;
    pq->rear = NULL;
    return pq;
}
int isEmpty(PriorityQueue *pq)
{
    return (pq->front == NULL);
}
PriorityQueue* enqueue(PriorityQueue *pq, int item, int priority) 
{
    PQNode *newNode = createNode(item, priority);
    if (isEmpty(pq))
    {
        pq->front = pq->rear = newNode;
        return pq;
    }
    if (priority > pq->front->priority)
    {
        newNode->next = pq->front;
        pq->front = newNode;
        return pq;
    }
    
    PQNode *temp = pq->front;
    while (temp->next != NULL && temp->next->priority >= priority)
    {
        temp = temp->next;
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
    
    if (temp->next == NULL)
    {
        pq->rear = newNode;
    }
    return pq;
}
PriorityQueue* dequeue(PriorityQueue *pq)
{
    if (isEmpty(pq)) 
    {
        printf("Queue is empty!\n");
        return pq;
    }
    PQNode *temp = pq->front;
    int item = temp->info;
    pq->front = pq->front->next;
    printf("Dequeued element: %d\n", item);
    free(temp);
    return pq;
}
void display(PriorityQueue *pq)
{
    if (isEmpty(pq))
    {
        printf("Queue is empty!\n");
        return;
    }
    PQNode *temp = pq->front;
    printf("\nQueue contents:\n");
    printf("Item\tPriority\n");
    while (temp != NULL)
    {
        printf("%d\t%d\n", temp->info, temp->priority);
        temp = temp->next;
    }
}
int main()
{
    PriorityQueue* pq = initPQ(); 
    int choice, item, priority;

    while(1)
    {
        printf("\nPriority Queue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter item to insert: ");
                scanf("%d", &item);
                printf("Enter priority (higher number = higher priority): ");
                scanf("%d", &priority);
                pq = enqueue(pq, item, priority);
                break;

            case 2:
                pq = dequeue(pq);
                break;

            case 3:
                display(pq);
                break;

            case 4:
                printf("Exiting...\n");
                free(pq);
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
