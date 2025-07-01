#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
    int data;
    struct node* left;
    struct node* right;
} Node;

typedef struct tree 
{
    Node* root;
} Tree;

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

int main() {
    Node* root = NULL;
    
}