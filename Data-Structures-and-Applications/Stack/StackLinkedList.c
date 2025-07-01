#include <stdio.h>
#include <stdlib.h>

typedef struct stacknode
{
    int info;
    struct stacknode *next;
}StackNode;
typedef struct stack
{
    StackNode* top;
}Stack;
StackNode* createNode(int ele)
{
    StackNode* sn = malloc(sizeof(StackNode));
    sn->info = ele;
    sn->next = NULL;
    return sn;
}
Stack* initStack()
{
    Stack* s = malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}
int isEmpty(Stack* s)
{
    return (s->top == NULL);
}
Stack* push(Stack* s, int ele)
{
    StackNode* sn = createNode(ele);
    sn->next = s->top;
    s->top = sn;
    return s;
}
StackNode* pop(Stack* s)
{
    if(isEmpty(s))
        return NULL;
        
    StackNode* temp = s->top;
    s->top = s->top->next;
    temp->next = NULL;
    return temp;
}
StackNode* peek(Stack* s)
{
    if(isEmpty(s))
        return NULL;

    StackNode* temp = s->top;
    return temp;
}
int main()
{
    Stack* s = initStack();
    int choice, element;
    StackNode* temp;
    
    while(1)
    {
        printf("\nStack Operations:");
        printf("\n1. Push");
        printf("\n2. Pop");
        printf("\n3. Peek");
        printf("\n4. Check if Empty");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1:
                printf("Enter element to push: ");
                scanf("%d", &element);
                s = push(s, element);
                printf("Pushed %d onto stack\n", element);
                break;
                
            case 2:
                temp = pop(s);
                if(temp == NULL)
                    printf("Stack is empty\n");
                else
                {
                    printf("Popped element: %d\n", temp->info);
                    free(temp);  // Don't forget to free the popped node
                }
                break;
                
            case 3:
                temp = peek(s);
                if(temp == NULL)
                    printf("Stack is empty\n");
                else
                    printf("Top element: %d\n", temp->info);
                break;
                
            case 4:
                if(isEmpty(s))
                    printf("Stack is empty\n");
                else
                    printf("Stack is not empty\n");
                break;
                
            case 5:
                // Clean up before exit
                while(!isEmpty(s))
                {
                    temp = pop(s);
                    free(temp);
                }
                free(s);
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}