#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct stack
{
    int top;
    int stack[SIZE];
}Stack;
Stack* initStack()
{
    Stack* st = malloc(sizeof(Stack));
    st->top = -1;
    return st;
}
int isEmpty(Stack* s)
{
    return (s->top == -1);
}
int isFull(Stack* s)
{
    return (s->top == SIZE-1);
}
int pop(Stack* s)
{
    if(isEmpty(s))
    {
        printf("UNDERFLOW\n");
        return -1;
    }
    else
    {
        return s->stack[s->top--];
    }
}
void push(Stack* s, int ele)
{
    if(isFull(s))
    {
        printf("OVERFLOW\n");
        return;
    }
    else
    {
        s->stack[++s->top] = ele;
        return;
    }
}
int peek(Stack* s)
{
    if(isEmpty(s))
    {
        printf("EMPTY STACK\n");
        return -1;
    }
    else
    {
        return s->stack[s->top]; 
    }
}
void displayStack(Stack* s)
{
    if(isEmpty(s))
    {
        printf("EMPTY STACK\n");
        return;
    }
    else
    {
        for(int i = s->top; i >= 0; i--)
        {
            printf("%d ", s->stack[i]);
        }
        printf("\n");
    }
}
int main()
{
    Stack* s = initStack();
    int choice, element;
    
    while(1)
    {
        printf("\n1. Push\n2. Pop\n3. Peek\n4. Display\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1:
                printf("Enter element to push: ");
                scanf("%d", &element);
                push(s, element);
                break;
            
            case 2:
                element = pop(s);
                if(element != -1)
                    printf("Popped element: %d\n", element);
                break;
            
            case 3:
                element = peek(s);
                if(element != -1)
                    printf("Top element: %d\n", element);
                break;
            
            case 4:
                displayStack(s);
                break;
            
            case 5:
                free(s);
                return 0;
            
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}