#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node* next;
}Node;
typedef struct cll
{
    Node* tail;
}CircularSLL;
void init(CircularSLL* List)
{
    List->tail = NULL;
}
Node* createNode(int data)
{
    Node* newnode = (Node*)(malloc(sizeof(Node)));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}
void insertEnd(CircularSLL* List,int data)
{
    Node* newnode = createNode(data);
    if(List->tail == NULL)
    {
        List->tail = newnode;
        newnode->next = newnode;
    }
    else
    {
        newnode->next = List->tail->next;
        List->tail->next = newnode;
        List->tail = newnode;
    }
}
void insertFront(CircularSLL* List, int data)
{
    Node* newnode = createNode(data);
    if(List->tail == NULL)
    {
        List->tail = newnode;
        newnode->next = newnode;
    }
    else
    {
        newnode->next=List->tail->next;
        List->tail->next = newnode;
    }
}
void insertPos(CircularSLL* List,int data,int pos)
{
    Node* newnode = createNode(data);
    if(pos==1)
    {
        insertFront(List,data);
        return;
    }
    if(pos<1)
    {
        printf("Invalid case\n");
        return;
    }
    if(List->tail=NULL)
    {
        newnode->next = newnode;
        List->tail = newnode;
        return;
    }
    int count = 1;
    Node* current = List->tail->next;
    while(current->next != List->tail->next && count<pos-1)
    {
        current = current->next;
        count++;
    }
    newnode->next = current->next;
    current->next = newnode;
    if(newnode->next == List->tail->next)
    {
        List->tail = newnode;
    }
}
void deleteEnd(CircularSLL* List)
{
    if(List->tail==NULL)
    {
        printf("Empty list\n");
        return;
    }
    if(List->tail->next==List->tail)
    {
        free(List->tail);
        List->tail = NULL;
        return;
    }
    Node* current = List->tail->next; //equivalently the head
    while(current->next != List->tail)
    {
        current = current->next;
    }
    List->tail = current; 
    current->next = List->tail->next;   
}
void deleteFront(CircularSLL* List)
{
    if(List->tail==NULL)
    {
        printf("Empty list\n");
        return;
    }
    if(List->tail->next == List->tail)
    {
        free(List->tail);
    }
    Node* current = List->tail->next;
    List->tail->next = current->next;
    free(current);
}