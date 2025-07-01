#include <stdio.h>
#include <stdlib.h>

typedef struct cqnode
{
    int info;
    struct cqnode* next;
}CQNode;
typedef struct CQ
{
    CQNode* front;
    CQNode* rear;
}CircularQueue;
CQNode* createNode(int ele)
{
    CQNode* newNode = malloc(sizeof(CQNode));
    newNode->info = ele;
    newNode->next = NULL;
    return newNode;
}
CircularQueue* initCircularQueue()
{
    CircularQueue* newCQ = malloc(sizeof(CircularQueue));
    newCQ->front = NULL;
    newCQ->rear = NULL;
    return newCQ;
}
int isEmpty(CircularQueue* cq)
{
    return (cq->front == NULL);
}
CircularQueue* enqueue(CircularQueue* cq, int ele)
{
    CQNode* newNode = createNode(ele);
    if(cq->front == NULL)
    {
        cq->front = newNode;
        cq->rear = newNode;
        return cq;
    }
    newNode->next = cq->front;    
    cq->rear->next = newNode;     
    cq->rear = newNode;           
    return cq;
}
CircularQueue* dequeue(CircularQueue* cq)
{
    if(isEmpty(cq))
    {
        printf("Queue is empty!\n");
        return cq;
    }
    
    CQNode* temp = cq->front;
    int value = temp->info;
    printf("Dequeued element: %d\n", value);
    
    if(cq->front == cq->rear)
    {
        cq->front = NULL;
        cq->rear = NULL;
    }
    else
    {
        cq->front = cq->front->next;
        cq->rear->next = cq->front;
    }
    
    free(temp);
    return cq;
}
void displayQueue(CircularQueue* cq)
{
    if(isEmpty(cq))
    {
        printf("Queue is empty!\n");
        return;
    }
    CQNode* temp = cq->front;
    do 
    {
        printf("%d ", temp->info);
        temp = temp->next;
    } while(temp != cq->front);
    printf("\n");
}
int main()
{
    CircularQueue* cq = initCircularQueue();
    int choice, element;
    
    while(1)
    {
        printf("\n1. Enqueue");
        printf("\n2. Dequeue");
        printf("\n3. Display");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
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
                printf("Exiting...\n");
                exit(0);
                
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}