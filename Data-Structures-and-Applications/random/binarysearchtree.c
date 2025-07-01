#include <stdio.h>
#include <stdlib.h>
#define MAX 100
//Structure definitions of a node, a tree, and a stack (used for the iterative traversal)
typedef struct node{
    int info;
    struct node* left;
    struct node* right;
}NODE;
typedef struct tree{
    NODE* root;
}TREE;
typedef struct stack{
    NODE* arr[MAX];
    int size;
}STACK;
//Usage of helper functions so that the tree object can directly be passed to the function rather than using the nodes to access each one
NODE* createNode(int info)
{
    NODE* temp = (NODE*)(malloc(sizeof(NODE)));
    temp->info = info;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
TREE* createTree(NODE* root)
{
    TREE* pt = (TREE*)(malloc(sizeof(TREE)));
    pt->root = root;
    return pt;
}
NODE* insertNodeHelper(NODE* root, int info)
{
    if (root == NULL)
        return createNode(info);   
    if (info < root->info)
        root->left = insertNodeHelper(root->left, info);
    else if (info > root->info)
        root->right = insertNodeHelper(root->right, info);
        
    return root;
}
TREE* insertNode(TREE* pt, int info)
{
    pt->root = insertNodeHelper(pt->root, info);
    return pt;
}
void inorderTraversalHelper(NODE* root)
{
    if(root != NULL)
    {
        inorderTraversalHelper(root->left);
        printf("%d ", root->info);
        inorderTraversalHelper(root->right);
    }
}
void inorderTraversal(TREE* pt)
{
    inorderTraversalHelper(pt->root);
}
void preorderTraversalHelper(NODE* root)
{
    if(root!=NULL)
    {
        printf("%d ", root->info);
        preorderTraversalHelper(root->left);
        preorderTraversalHelper(root->right);
    }
}
void preorderTraversal(TREE* pt)
{
    preorderTraversalHelper(pt->root);
}
void postorderTraversalHelper(NODE* root)
{
    if(root!=NULL)
    {
        postorderTraversalHelper(root->left);
        postorderTraversalHelper(root->right);
        printf("%d ", root->info);
    }
}
void postorderTraversal(TREE* pt)
{
    postorderTraversalHelper(pt->root);
}
NODE* inorderSuccessor(NODE* root, int value)
{
    NODE* current = root;
    NODE* successor = NULL;
    
    while (current != NULL) 
    {
        if (value < current->info) 
        {
            successor = current;
            current = current->left;
        }
        else if (value > current->info)
        {
            current = current->right;
        }
        else 
        {
            if (current->right != NULL) 
            {
                current = current->right;
                while (current->left != NULL)
                    current = current->left;
                successor = current;
            }
            break;
        }
    }
    return successor;
}
NODE* inorderPredecessor(NODE* root, int value)
{
    NODE* current = root;
    NODE* predecessor = NULL;
    
    while (current != NULL) {
        if (value > current->info) {
            predecessor = current;
            current = current->right;
        }
        else if (value < current->info) {
            current = current->left;
        }
        else {
            
            if (current->left != NULL) 
            {
                current = current->left;
                while (current->right != NULL)
                    current = current->right;
                predecessor = current;
            }
            break;
        }
    }
    return predecessor;
}
NODE* delNodeHelper(NODE* root, int val)
{
    NODE* temp;
    if(root == NULL)
        return NULL;
        
    if(val < root->info)
        root->left = delNodeHelper(root->left, val);
    else if(val > root->info)
        root->right = delNodeHelper(root->right, val);
    else
    {
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        if(root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }
        if(root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }
        NODE* inSuc = inorderSuccessor(root,val);
        root->info = inSuc->info;
        root->right = delNodeHelper(root->right, inSuc->info);
    }
    return root;
}
TREE* delNode(TREE* pt, int ele)
{
    pt->root = delNodeHelper(pt->root, ele);
    return pt;
}
int searchNodeHelper(NODE* root, int val)
{
    if (root == NULL)
        return -1;
        
    if (root->info == val)
        return 1;    
        
    if (val < root->info)
        return searchNodeHelper(root->left, val);
    else
        return searchNodeHelper(root->right, val);
}
int searchNode(TREE* pt, int val)
{
    if (pt == NULL)
        return -1;
    return searchNodeHelper(pt->root, val);
}

//Stack related functions to help in iterative traversals
STACK* initStack()
{
    STACK* s = (STACK*)malloc(sizeof(STACK));
    if (s == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    s->size = 0;
    return s;
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
    if (!isFull(s)) 
    {
        s->arr[s->size++] = node;
    } 
    else {
        printf("Stack overflow\n");
    }
}
NODE* pop(STACK* s)
{
    if (!isEmpty(s))
    {
        return s->arr[--s->size];
    }
    else 
    {
        printf("Stack underflow\n");
        return NULL;
    }
}
//Iterative traversal methods
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
        printf("%d ", curr->info);
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
        printf("%d ", curr->info);
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
        printf("%d ",curr->info);
    }
}
int heightNode(NODE* root)
{
    if (root == NULL)
        return 0; 
    int lheight = heightNode(root->left);
    int rheight = heightNode(root->right);
    return (lheight > rheight ? lheight : rheight) + 1; 
}

int heightTree(TREE *pt)
{
    return heightNode(pt->root);
}

int main() 
{
    TREE* bst = createTree(NULL);
    int choice, value;
    
    do {
        printf("\n\n=== Binary Search Tree Operations ===");
        printf("\n1.  Insert Node");
        printf("\n2.  Delete Node");
        printf("\n3.  Search Node");
        printf("\n4.  Recursive Inorder Traversal");
        printf("\n5.  Recursive Preorder Traversal");
        printf("\n6.  Recursive Postorder Traversal");
        printf("\n7.  Iterative Inorder Traversal");
        printf("\n8.  Iterative Preorder Traversal");
        printf("\n9.  Iterative Postorder Traversal");
        printf("\n10. Find Tree Height");
        printf("\n11. Find Inorder Successor");
        printf("\n12. Find Inorder Predecessor");
        printf("\n13. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\nEnter value to insert: ");
                scanf("%d", &value);
                insertNode(bst, value);
                printf("\nNode inserted successfully!");
                break;

            case 2:
                printf("\nEnter value to delete: ");
                scanf("%d", &value);
                delNode(bst, value);
                printf("\nNode deleted successfully!");
                break;

            case 3:
                printf("\nEnter value to search: ");
                scanf("%d", &value);
                if(searchNode(bst, value) == 1)
                    printf("\n%d found in the tree!", value);
                else
                    printf("\n%d not found in the tree!", value);
                break;

            case 4:
                printf("\nInorder Traversal: ");
                inorderTraversal(bst);
                break;

            case 5:
                printf("\nPreorder Traversal: ");
                preorderTraversal(bst);
                break;

            case 6:
                printf("\nPostorder Traversal: ");
                postorderTraversal(bst);
                break;

            case 7:
                printf("\nIterative Inorder Traversal: ");
                iterativeInorder(bst);
                break;

            case 8:
                printf("\nIterative Preorder Traversal: ");
                iterativePreorder(bst);
                break;

            case 9:
                printf("\nIterative Postorder Traversal: ");
                iterativePostorder(bst);
                break;

            case 10:
                printf("\nHeight of the tree: %d", heightTree(bst));
                break;

            case 11:
                printf("\nEnter node value to find successor: ");
                scanf("%d", &value);
                NODE* succ = inorderSuccessor(bst->root, value);
                if(succ)
                    printf("\nInorder successor of %d is %d", value, succ->info);
                else
                    printf("\nNo inorder successor exists for %d!", value);
                break;

            case 12:
                printf("\nEnter node value to find predecessor: ");
                scanf("%d", &value);
                NODE* pred = inorderPredecessor(bst->root, value);
                if(pred)
                    printf("\nInorder predecessor of %d is %d", value, pred->info);
                else
                    printf("\nNo inorder predecessor exists for %d!", value);
                break;

            case 13:
                printf("\nExiting program...");
                break;

            default:
                printf("\nInvalid choice! Please try again.");
        }
    } while(choice != 13);

    return 0;
}
