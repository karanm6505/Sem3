#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
int tree[SIZE];
void initialiseTree()
{
    for(int i=0;i<SIZE;i++)
        tree[i]=-1;
}
void insert(int value)
{
    int index = 0; // starting of the tree (root node index=0)
    while (index < SIZE)
    {
        if (tree[index] == -1)
        {
            tree[index] = value;
            return;
        }
        if (value < tree[index])
        {
            index = 2 * index + 1;
        }
        else if (value > tree[index])
        {
            index = 2 * index + 2;
        }
        else
        {
            return;
        }
    }
    printf("Tree full, cannot insert %d\n", value);
}
int search(int value)
{
    int index = 0;
    while(index<SIZE && tree[index]!=-1)
    {
        if(tree[index]==value)
            return index;
        else if(value<tree[index])
            index = 2*index + 1;
        else 
            index = 2*index + 2;
    }
    return -1;
}
void inorderTraversal(int index)
{
    if(index>SIZE || tree[index]==-1)
    return;
    inorderTraversal(2*index+1);
    printf("%d \n",tree[index]);
    inorderTraversal(2*index+2);
}
void delete(int value)
{
    int index = search(value);
    if (index == -1) {
        printf("Value not found\n");
        return;
    }

    if (tree[2*index+1] == -1 && tree[2*index+2] == -1) {
        tree[index] = -1;
    }
    else if (tree[2*index+1] == -1 || tree[2*index+2] == -1) {
        int childIndex = (tree[2*index+1] != -1) ? 2*index+1 : 2*index+2;
        tree[index] = tree[childIndex];
        tree[childIndex] = -1;
    }
    else {
        int successorIndex = 2*index + 2;
        while (tree[2*successorIndex+1] != -1) {
            successorIndex = 2*successorIndex + 1;
        }
        tree[index] = tree[successorIndex];
        tree[successorIndex] = -1;
    }
}
int main()
{
    initialiseTree();
    while(1)
    {
        int choice, val;
        printf("1. Insert element\n");
        printf("2. Delete element\n");
        printf("3. Search element\n");
        printf("4. Display the tree in inorder\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter the value to be inserted: ");
                scanf("%d", &val);
                insert(val);
                break;
            case 2:
                printf("Enter the value to be deleted: ");
                scanf("%d", &val);
                delete(val);
                break;
            case 3:
                printf("Enter the value to be searched: ");
                scanf("%d", &val);
                int result = search(val);
                if (result != -1)
                    printf("Value %d found at index %d\n", val, result);
                else
                    printf("Value %d not found in the tree\n", val);
                break;
            case 4:
                printf("Inorder traversal of the tree:\n");
                inorderTraversal(0);
                break;
            default:
                exit(0);
        }
        printf("\n");
    }
}