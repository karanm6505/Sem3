#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//Structure definitions
typedef struct node
{
    int info;
    struct node *left, *right;
    bool rthread;
} NODE;
typedef struct tree
{
    NODE* root;
} TREE;
//Node and tree related functions
NODE* createNode(int info)
{
    NODE* temp = (NODE*)(malloc(sizeof(NODE)));
    temp->info = info;
    temp->left = NULL;
    temp->right = NULL;
    temp->rthread = true;
    return temp;
}
TREE* createTree(NODE* root)
{
    TREE* pt = (TREE*)(malloc(sizeof(TREE)));
    pt->root = root;
    return pt;
}
NODE* setLeft(NODE* root, int ele)
{
    NODE* temp = createNode(ele);
    root->left = temp;
    temp->right = root;
    temp->rthread = true;
    return temp;
}
NODE* setRight(NODE* root, int ele)
{
    NODE* temp = createNode(ele);
    temp->right = root->right;
    root->right = temp;
    root->rthread = false;
    return temp;
}
NODE* insertNodeHelper(NODE* root, int ele)
{
    if(root == NULL)
        return createNode(ele);
    
    if(ele < root->info)
    {
        if(root->left == NULL)
            root->left = setLeft(root, ele);
        else
            root->left = insertNodeHelper(root->left, ele);
    }
    else if(ele > root->info)
    {
        if(root->right == NULL || root->rthread)
            root->right = setRight(root, ele);
        else
            root->right = insertNodeHelper(root->right, ele);
    }
    else
        return root;
    
    return root;
}
TREE* insertNode(TREE* tree, int ele)
{
    if(tree->root == NULL)
        tree->root = createNode(ele);
    else
        tree->root = insertNodeHelper(tree->root, ele);
    return tree;
}
//Threaded trees are mostly used only for inorder, hence only inorder given
void inorderTraversal(TREE *pt) {
    if (pt == NULL || pt->root == NULL) 
    {
        printf("Tree is empty.\n");
        return;
    }

    NODE *p = pt->root;
    while (p->left != NULL) 
    {
        p = p->left;
    }
    while (p != NULL) 
    {
        printf("%d ", p->info);

        if (p->rthread) 
        {
            p = p->right;
        }
        else 
        {
            p = p->right;
            while (p != NULL && p->left != NULL) 
            {
                p = p->left;
            }
        }
    }
}
int main() 
{
    TREE* tree = createTree(NULL);
    int choice, value;

    do {
        printf("\nMenu:\n");
        printf("1. Insert a node\n");
        printf("2. Inorder traversal\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertNode(tree, value);
                printf("Node %d inserted.\n", value);
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorderTraversal(tree);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}