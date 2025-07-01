#include <stdio.h>
#include <stdlib.h>

/*
If it's an opening bracket, push into stack, if it's a closing bracket pop until that bracket is found
suppose it's ({}), push ( and { onto the stack, when } is found pop { from the stack
and when ) is seen pop ( from the stack.

Suppose it is (}) push ( onto stack, since } is seen, show an error

Suppose it is ({) push ( onto stack, push { onto stack and read through string until } is found, if not found, show error
*/

#define MAX_SIZE 100

typedef struct 
{
    char items[MAX_SIZE];
    int top;
} Stack;
void initStack(Stack *s) 
{
    s->top = -1;
}
int isEmpty(Stack *s) 
{
    return (s->top == -1);
}
int isFull(Stack *s) 
{
    return (s->top >= MAX_SIZE - 1);
}
void push(Stack *s, char c) 
{
    if (isFull(s)) return;
    s->items[++(s->top)] = c;
}
char pop(Stack *s) 
{
    if (isEmpty(s)) return '\0';
    return s->items[(s->top)--];
}
int isMatching(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}
int checkParenthesis(char *expr)
{
    Stack s;
    initStack(&s);
    
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[')
        {
            push(&s, expr[i]);
        }
        else if (expr[i] == ')' || expr[i] == '}' || expr[i] == ']') 
        {
            if (isEmpty(&s)) return 0;  // No matching opening bracket
            char popped = pop(&s);
            if (!isMatching(popped, expr[i])) {
                return 0;
            }
        }
    }
    
    return isEmpty(&s);  // Stack should be empty for valid expression
}
int main() 
{
    char expr[MAX_SIZE];
    printf("Enter expression: ");
    scanf("%s", expr);
    
    if (checkParenthesis(expr))
        printf("Balanced\n");
    else
        printf("Not Balanced\n");
        
    return 0;
}