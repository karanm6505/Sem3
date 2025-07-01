#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node;
typedef struct stack
{
    Node* arr[MAX]; 
    int size;
} Stack;
void push(Stack *s, Node* node) 
{
    if (s->size < MAX) 
    {
        s->arr[s->size] = node; 
        s->size++;
    } else 
    {
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
void initStack(Stack *s)
{
    s->size = 0;
}
Node* createNode(int data) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (newnode == NULL) {
        printf("Failed memory allocation\n");
        return NULL;
    }
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
Node* insertNode(Node **root, int data) {
    if (*root == NULL)
        return createNode(data);
    if (data < (*root)->data)
        (*root)->left = insertNode(&((*root)->left), data);
    else if (data > (*root)->data)
        (*root)->right = insertNode(&((*root)->right), data);
    return *root;
}
void inorderTraversal(Node *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}
Node* minimumValue(Node *root) {
    Node* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}
Node* deleteNode(Node **root, int key) {
    if (*root == NULL)
        return *root;

    if (key < (*root)->data) {
        (*root)->left = deleteNode(&((*root)->left), key);
    } else if (key > (*root)->data) {
        (*root)->right = deleteNode(&((*root)->right), key);
    } else {
        
        if ((*root)->left == NULL) {
            Node* temp = (*root)->right;
            free(*root); 
            return temp;
        } else if ((*root)->right == NULL) {
            Node* temp = (*root)->left;
            free(*root); 
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = minimumValue((*root)->right);
        (*root)->data = temp->data; // Copy the inorder successor's content to this node
        (*root)->right = deleteNode(&((*root)->right), temp->data); // Delete the inorder successor
    }
    return *root;
}
void iterativeInorder(Node* root)
{
    Stack s;
    initStack(&s);
    Node* current = root;
    do
    {
        while(current != NULL)
        {
            push(&s, current); 
            current = current->left;
        }
        Node* poppedNode = pop(&s);
        printf("%d ", poppedNode->data); 
        current = poppedNode->right; 
    } while (!isEmpty(&s) || current != NULL); 
}
void iterativePreorder(Node* root)
{
    Node* current = root;
    if(current==NULL)
        return;
    Stack s;
    initStack(&s);
    push(&s,current);
    while(!isEmpty(&s))
    {
        current = pop(&s);
        printf("%d ",current->data);
        if(current->right!=NULL)
            push(&s,current->right);
        if(current->left!=NULL)
            push(&s,current->left);
    }
}
void iterativePostorder(Node* root)
{
    Stack s1,s2;
    initStack(&s1);
    initStack(&s2);
    push(&s1,root);
    while(!isEmpty(&s1))
    {
        Node* current = pop(&s1);
        push(&s2,current);
        if(current->left != NULL)
        {
            push(&s1,current->left);
        }
        if(current->right!=NULL)
        {
            push(&s1,current->right);
        }
    }
    while(!isEmpty(&s2))
    {
        Node* current = pop(&s2);
        printf("%d ",current->data);
    }
}


int main()
{
    Node* root = NULL;
    
    // Insert nodes in the correct order as per the tree in the image
    root = insertNode(&root, 5); // Root node
    insertNode(&root, 3); // Left child of 5
    insertNode(&root, 6); // Right child of 5
    insertNode(&root, 2); // Left child of 3
    insertNode(&root, 4); // Right child of 3

    // Now we can perform different traversals to check the tree structure


    // Iterative Inorder Traversal
    printf("Iterative Inorder Traversal: ");
    iterativeInorder(root);
    printf("\n");

    printf("Iterative Preorder Traversal: ");
    iterativePreorder(root);
    printf("\n");

    printf("Iterative Postorder Traversal: ");
    iterativePostorder(root);
    printf("\n");

    return 0;
}
