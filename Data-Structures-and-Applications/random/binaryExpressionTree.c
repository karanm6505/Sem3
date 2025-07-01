#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100
//Structure definitions
typedef struct node
{
    char info;
    struct node *left, *right;
}NODE;
typedef struct tree
{
    NODE* root;
}TREE;
typedef struct stack
{
    NODE* arr[MAX];
    int size;
}STACK;
//Stack related functions
STACK* initStack()
{
    STACK* tempStack = malloc(sizeof(STACK));
    tempStack->size = 0;
    return tempStack;
}
int isEmpty(STACK* s)
{
    return s->size == 0;
}
int isFull(STACK* s)
{
    return s->size == MAX;
}
void push(STACK* s, NODE* node)
{
    if(!isFull(s))
    {
        s->arr[s->size++] = node;
    }
    else
        printf("Stack Overflow\n");
}
NODE* pop(STACK* s)
{
    if(!isEmpty(s))
        return s->arr[--s->size];
    else
    {
        printf("Stack underflow \n");
        return NULL;
    }
}
//Tree related functions
NODE* createNode(char info)
{
    NODE* Node = malloc(sizeof(NODE));
    if(Node == NULL)
    {
        printf("Malloc failed\n");
        return NULL;
    }
    Node->info = info;
    Node->left = NULL;
    Node->right = NULL;
    return Node;
}
TREE* createTree(NODE* root)
{
    TREE* Tree = malloc(sizeof(TREE));
    if(Tree == NULL)
    {
        printf("Malloc failed\n");
        return NULL;
    }
    Tree->root = root;
    return Tree;
}
TREE* expressionTree(char *str, TREE* pt)
{
    STACK* s = initStack();
    int i = 0;
    while(str[i]!='\0')
    {
        if(isdigit(str[i]))
        {
            push(s,createNode(str[i]));
            i++;
        }
        else
        {
            NODE* operatorNode = createNode(str[i]);
            operatorNode->right = pop(s);
            operatorNode->left = pop(s);
            push(s,operatorNode);
            i++;
        }
    }
    NODE* root = pop(s);
    free(s);
    pt->root = root;
    return pt;
}
//Iterative traversal functions
void iterativeInorder(TREE* pt)
{
    STACK* s = initStack();
    if (s == NULL) 
        return;
    
    NODE* curr = pt->root;
    while (curr != NULL || !isEmpty(s))
    {
        while(curr != NULL)
        {
            push(s, curr);
            curr = curr->left;
        }
        curr = pop(s);
        printf("%c ", curr->info);
        curr = curr->right;
    }
    
    free(s);
}
void iterativePreorder(TREE* pt)
{
    NODE* curr = pt->root;
    if(curr == NULL)
        return;
    STACK *s = initStack();
    push(s,curr);
    while(!isEmpty(s))
    {
        curr = pop(s);
        printf("%c ", curr->info);
        if(curr->right != NULL)
            push(s,curr->right);
        if(curr->left != NULL)
            push(s,curr->left);
    }
}
void iterativePostorder(TREE* pt)
{
    STACK *s1 = initStack();
    STACK *s2 = initStack();
    NODE* curr = pt->root;
    push(s1,curr);
    while(!isEmpty(s1))
    {
        curr = pop(s1);
        push(s2,curr);
        if(curr->left!=NULL)
            push(s1,curr->left);
        if(curr->right!=NULL)
            push(s1,curr->right);
    }
    while(!isEmpty(s2))
    {
        curr = pop(s2);
        printf("%c ",curr->info);
    }
}
float eval(NODE* root)
{
    if (root->info == '+' || root->info == '-' || 
        root->info == '*' || root->info == '/') 
    {
        switch(root->info)
        {
            case '+': 
                return (eval(root->left) + eval(root->right));
            case '-': 
                return (eval(root->left) - eval(root->right));
            case '*': 
                return (eval(root->left) * eval(root->right));
            case '/': 
                return (eval(root->left) / eval(root->right));
        }
    }
    else if (isdigit(root->info))
    {
        return root->info - '0';
    }
    return 0;  // Should never reach here
}
float eval_result(TREE* pt)
{
    return eval(pt->root);
}
int main() 
{
    TREE* pt = createTree(NULL);
    int choice;
    char expression[MAX];
    
    while (1) 
    {
        printf("\nMenu:\n");
        printf("1. Create Expression Tree\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Evaluate Expression Tree\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the postfix expression: ");
                scanf("%s", expression);
                pt = expressionTree(expression, pt);
                printf("Expression Tree Created\n");
                break;

            case 2:
               
                printf("Inorder Traversal: ");
                iterativeInorder(pt);
                printf("\n");
                break;

            case 3:
                printf("Preorder Traversal: ");
                iterativePreorder(pt);
                printf("\n");
                break;

            case 4:
                // Postordertraversal
                printf("Postorder Traversal: ");
                iterativePostorder(pt);
                printf("\n");
                break;

            case 5:
                printf("Result: %f\n",eval_result(pt));
                break;

            case 6:
                printf("Exiting...\n");
                free(pt);
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}