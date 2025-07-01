#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int info;
    struct node* prev;
    struct node* next;
}NODE;
typedef struct list
{
    NODE* head;
}LIST;


 