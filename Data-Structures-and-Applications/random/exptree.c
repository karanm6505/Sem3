//postorder to inorder (somewhat)
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100
typedef struct node 
{
    char data; 
    struct node* left;
    struct node* right;
} Node;
typedef struct stack 
{
    Node* arr[MAX]; 
    int size;
} Stack;
void initStack(Stack *s) 
{
    s->size = 0;
}
void push(Stack *s, Node* node) 
{
    if (s->size < MAX) {
        s->arr[s->size] = node;
        s->size++;
    } else {
        printf("Stack overflow: cannot push node\n");
    }
}
int isEmpty(Stack *s) 
{
    return s->size == 0;
}
Node* pop(Stack *s) 
{
    if (s->size <= 0) 
    {
        printf("Stack underflow\n");
        return NULL;
    }
    return s->arr[--s->size];
}
Node* createNode(char value)
{
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->data = value;
    return newnode;
}
Node* exptree(char *str, Stack *s) 
{
    int i = 0;
    while (str[i] != '\0') {
        if (isalpha(str[i])) 
        {  
            push(s, createNode(str[i]));
            i++;
        } 
        else 
        {  
            Node* op = createNode(str[i]);
            Node* right = pop(s);
            Node* left = pop(s);
            op->right = right;
            op->left = left;
            push(s, op);  
            i++;
        }
    }
    return pop(s);  
}
void iterativeInorder(Node* root) 
{
    Stack s;
    initStack(&s);
    Node* current = root;
    do {
        while (current != NULL) {
            push(&s, current);
            current = current->left;
        }
        Node* poppedNode = pop(&s);
        printf("%c ", poppedNode->data);  // Use %c for char data
        current = poppedNode->right;
    } while (!isEmpty(&s) || current != NULL);
}
int main()
{
    Stack s;  // Declare stack as a normal variable
    initStack(&s);
    
    // Expression: "ab*c/ef/g*+k+xy*-"
    char str[MAX];
    scanf("%s",str);
    
    iterativeInorder(exptree(str, &s));
    
    return 0;
}
