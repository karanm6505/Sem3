#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 100

typedef struct stack
{
    int top;
    int stack[SIZE];  // Changed from char to int
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
int pop(Stack* s)     // Changed return type from char to int
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
void push(Stack* s, int ele)  // Changed parameter from char to int
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
int isOperand(char ch) 
{
    return ((ch >= '0' && ch <= '9'));
}
int isOperator(char ch) 
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}
int precedence(char ch) 
{
    switch (ch) 
    {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}
int resultPostfix(char* postfix)
{
    Stack* s = initStack();
    int i = 0;
    while(postfix[i] != '\0')
    {
        if(isOperand(postfix[i]))
        {
            push(s, postfix[i] - '0');  // Convert char to int
            i++;
        }
        else if(isOperator(postfix[i]))
        {
            // Note the order: first pop is second operand
            int op2 = pop(s);
            int op1 = pop(s);
            int result;
            
            switch(postfix[i])
            {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
                case '^': result = (int)pow(op1, op2); break;
            }
            push(s, result);
            i++;
        }
    }
    
    int final_result = pop(s);
    free(s);
    return final_result;
}
int main()
{
    char postfix[SIZE];
    printf("Enter postfix expression: ");
    scanf("%s", postfix);
    
    int result = resultPostfix(postfix);
    printf("Result of postfix expression: %d\n", result);
    
    return 0;
}
