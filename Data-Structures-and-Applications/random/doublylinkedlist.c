#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    struct node* prev;
    int data;
    struct node* next;
}Node;
Node* createNode(int data)
{
    Node* newNode = (Node*)(malloc(sizeof(Node)));
    newNode->prev = NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
void insertBegin(Node **head,int data)
{
    Node* newnode = createNode(data);
    if(*head!=NULL)
    {
        (*head)->prev = newnode;
    }
    newnode->next = *head;
    newnode->prev = NULL;
    *head = newnode;
}
void insertEnd(Node **head,int data)
{
    Node *temp = *head;
    Node* newnode = createNode(data);
    if(*head == NULL)
    {
        newnode->prev = NULL;
        *head = newnode;
    }
    while(temp->next!=NULL)
    {
        temp = temp->next;
    }
    temp->next = newnode;
    newnode->prev = temp;
    newnode->next = NULL;
}
void insertPos(Node **head,int data,int pos)
{
    Node* temp = *head;
    Node* newnode = createNode(data);
    int count = 1;
    if(*head==NULL)
    {
        if(pos == 1)
        {
            insertBegin(head,data);
            return;
        }
        else
        {
            printf("INVALID INVALID INVALID\n");
            return;
        }
    } 
    while(temp != NULL && count<pos-1)
    {
        temp = temp->next;
        count++;
    }
    if(temp==NULL)
    {
        printf("Invalid \n");
        free(newnode);
        return;
    }
    newnode->prev = temp;
    newnode->next = temp->next;
    if(temp->next == NULL)
    {
        insertEnd(head,data);
        return;
    }

}
void deleteBegin(Node **head)
{
    if(*head == NULL)
    {
        return;
    }
    if((*head)->next == NULL)
    {
        *head = NULL;
    }
    Node *temp = *head;
    *head = (*head)->next;
    (*head)->next->prev = NULL;
    free(temp);
}
void deleteEnd(Node **head)
{
    Node* temp = *head;
    if(*head==NULL)
        return;
    if((*head)->next == NULL)
        *head = NULL;
    else
    {
        while(temp->next->next!=NULL)
        {
            temp = temp->next; 
        }
        free(temp->next);
        temp->next = NULL;
    }
}
void deletePos(Node **head,int pos)
{
    if(*head==NULL)
    {
        printf("Empty list\n");
        return;
    }
    if((*head)->next == NULL || pos == 1)
    {
        deleteBegin(head);
        return;
    }
    Node *temp = *head;
    int count = 1;
    while(temp!=NULL && count<pos)
        {
            temp = temp->next;
            count++;
        }
    if(temp == NULL)
        {
            printf("Invalid Position\n");
            return;
        }
    if(temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    if(temp->next != NULL)
    {
    temp->next->prev = temp->prev;
    }
    free(temp);
    
}
void destroyList(Node **head)
{
    Node* temp = *head;
    if(*head == NULL)
    {
        printf("Empty List\n");
        free(temp);
    }
    while(temp!=NULL)
    {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
}
void display(Node *head)
{
    Node *temp = head;
    if(head == NULL)
    {
        printf("Empty list\n");
        return;
    }
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        if(temp->next!=NULL)
            printf(" -> ");
        temp = temp->next;
    }
}
void displayreverse(Node *head)
{
    Node *temp = head;
    if(head == NULL)
    {
        printf("Empty list\n");
        return;
    }
    while(temp->next!=NULL)
    {
        temp = temp->next;
    }
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        if(temp->prev!=NULL)
            printf(" <- ");
        temp = temp->prev;
    }
}
