#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 100

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
void push(Stack* s, char element)
{
    if(isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->stack[++s->top] = element;
}
char pop(Stack* s)
{
    if(isEmpty(s)) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return s->stack[s->top--];
}
char peek(Stack* s) 
{
    if(isEmpty(s)) 
    {
        printf("Stack is Empty\n");
        return '\0';
    }
    return s->stack[s->top];
}
void displayStack(Stack* s) 
{
    if(isEmpty(s)) 
    {
        printf("Stack is Empty\n");
        return;
    }
    for(int i = s->top; i >= 0; i--) 
    {
        printf("%c ", s->stack[i]);
    }
    printf("\n");
}
int isOperand(char ch) 
{
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}
int isOperator(char ch) 
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}
int precedence(char ch) 
{
    switch (ch) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}
void infixToPostfix(char* infix, char* postfix) 
{
    Stack* s = initStack();
    int i, j = 0;
    
    for (i = 0; infix[i] != '\0'; i++) 
    {
        if (isOperand(infix[i])) 
        {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(') 
        {
            push(s, infix[i]);
        }
        else if (infix[i] == ')') 
        {
            while (!isEmpty(s) && peek(s) != '(') 
            {
                postfix[j++] = pop(s);
            }
            if (!isEmpty(s) && peek(s) != '(')
            {
                printf("Invalid Expression\n");
                return;
            }
            else 
            {
                pop(s); 
            }
        }
        else if (isOperator(infix[i])) 
        {
            while (!isEmpty(s) && precedence(peek(s)) >= precedence(infix[i])) 
            {
                postfix[j++] = pop(s);
            }
            push(s, infix[i]);
        }
    }

    while (!isEmpty(s)) {
        if (peek(s) == '(') {
            printf("Invalid Expression\n");
            return;
        }
        postfix[j++] = pop(s);
    }
    postfix[j] = '\0';
}
int main() 
{
    char infix[100], postfix[100];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    
    return 0;
}

