#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node* next;
}Node;
Node* createNode(int);
void insertBegin(Node **, int);
void insertEnd(Node **, int);
void insertPos(Node **, int, int);
void deleteBegin(Node **);
void deleteEnd(Node **);
void deletePos(Node **, int);
void destroyList(Node **);
void display(Node *);
Node* RecurReverseList(Node *);
Node* reverseList(Node *);
Node* createNode(int data)
{
    Node* newnode = malloc(sizeof(Node));
    if (newnode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}
void insertBegin(Node **head,int data)
{
    Node* newnode = createNode(data);
    newnode->next = *head; //newnode->next now points to the previous start of list
    *head = newnode; //newnode set to the start of the list now
}
void insertEnd(Node **head,int data)
{
    Node* newnode = createNode(data);
    Node* temp = *head;
    if(*head==NULL)
    {
        
        *head=newnode;
        newnode->next = NULL;
        return;
    }
    while(temp->next!=NULL)
    {
        temp = temp->next;
    }
    temp->next = newnode;
    newnode->next = NULL;
}
void insertPos(Node **head,int data,int pos)
{
    Node* newnode = createNode(data);
    int count = 1;
    Node* temp = *head;
    if(pos==1 )
    {
        insertBegin(head,data);
    }
    else
    {
        while(temp!=NULL && count<pos-1)
        {
            temp=temp->next;
            count++;
        }
        if(temp==NULL)
        {
            printf("Invalid \n");
            free(newnode);
            return;
        }
        newnode->next = temp->next;
        temp->next = newnode;
    }
    
}
void deleteBegin(Node **head)
{
    Node* temp = *head;
    if(*head==NULL)
    {
        printf("List Empty\n");
        return;
    }
    else
    {
        *head = temp->next;
        free(temp);
    }   
}
void deleteEnd(Node **head)
{
    Node* temp = *head;
    if(*head == NULL)
    {
        return;
    }
    if(temp->next == NULL)
    {
        free(temp);
        *head = NULL;
        return;
    }
    while(temp->next->next!=NULL)
    {

        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}
void deletePos(Node **head, int pos)
{
    Node* temp = *head;
    Node* prev = NULL;
    int count = 1;

    if (pos < 1) {
        printf("Invalid position\n");
        return;
    }

    if (pos == 1) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && count < pos) {
        prev = temp;
        temp = temp->next;
        count++;
    }

    if (temp == NULL) {
        printf("Invalid position\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
}
void destroyList(Node **head)
{
    Node* current = *head;
    Node* next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}
void display(Node* head)
{
    if(head==NULL)
    {
        printf("List empty \n");
        return;
    }
    while(head!=NULL)
    {
        printf("%d",head->data);
        head = head->next;
        if(head!=NULL)
        {
            printf("->");
        }
    }
    printf("\n");
}
int search(Node** head, int data)
{
    Node* temp = *head;
    int count = 0;

    while (temp != NULL) 
    {
        if (temp->data == data) 
        {
            return count; 
        }
        temp = temp->next;
        count++;
    }
    
    return -1; 
}
Node* RecurReverseList(Node* head)
{
    if(head==NULL||head->next == NULL)
    {
        return head;
    }
    Node* newHead = RecurReverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;    
}
Node* reverseList(Node *head) 
{
    Node *prev = NULL; 
    Node *curr = head;
    Node *next = NULL;

    while (curr != NULL) {
        next = curr->next;  
        curr->next = prev;  
        prev = curr;        
        curr = next;        
    }

    return prev;
}
int countNodes(Node **head)
{
    Node* temp = *head;
    int count=0;
    if(*head==NULL)
    {
        return 0;
    }
    while(temp!=NULL)
    {
        temp = temp->next;
        count++;
    }
    return count;
}
Node* copyList(Node* head)
{
    if(head == NULL)
    {
        return NULL;
    }
    Node* newhead = NULL;
    Node* temp = head;
    while(temp!=NULL)
    {
        insertEnd(&newhead,temp->data);
        temp = temp->next;
    }
    return newhead;
}
void sortList(Node **head)
{
    int n = countNodes(head);
    Node* temp;
    for(int i=0;i<n-1;i++)
    {
        temp = *head;
        for(int j=0;j<n-i-1;j++)
        {
            if(temp->next!=NULL && temp->data > temp->next->data)
            {
                int swapper;
                swapper = temp->data;
                temp->data = temp->next->data;
                temp->next->data = swapper;   
            }
            temp = temp->next;
        }
    }
}
void removeDuplicates(Node **head)
{
    if (*head == NULL)
        return;
    Node* temp = *head;
    while (temp != NULL) {
        Node* temp1 = temp; 
        while (temp1->next != NULL) {
            if (temp1->next->data == temp->data) {
                
                Node* duplicate = temp1->next; 
                temp1->next = temp1->next->next; 
                free(duplicate); 
            } else {
                temp1 = temp1->next;
            }
        }
        temp = temp->next; 
    }
}
Node* mergeLists(Node **head1,Node **head2)
{
    Node* temp1 = *head1;
    if(*head1 == NULL)
    {
        printf("List 1 is empty \n");
        return *head2;
    }
    if(*head2 == NULL)
    {
        printf("List 2 is empty \n");
        return *head1;
    }
    while(temp1->next!=NULL)
    {
        temp1 = temp1->next;
    }
    temp1->next = *head2;
    return *head1;

}
int main() {
    Node* head = NULL;
    Node* head2 = NULL;  // For merging lists
    int choice, data, pos;

    do {
        printf("\nLinked List Operations:\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete from Beginning\n");
        printf("5. Delete from End\n");
        printf("6. Delete from Position\n");
        printf("7. Display List\n");
        printf("8. Reverse List (Iterative)\n");
        printf("9. Reverse List (Recursive)\n");
        printf("10. Search\n");
        printf("11. Count Nodes\n");
        printf("12. Copy List\n");
        printf("13. Sort List\n");
        printf("14. Remove Duplicates\n");
        printf("15. Merge Lists\n");
        printf("16. Destroy List\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertBegin(&head, data);
                break;
            case 2:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertEnd(&head, data);
                break;
            case 3:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &pos);
                insertPos(&head, data, pos);
                break;
            case 4:
                deleteBegin(&head);
                break;
            case 5:
                deleteEnd(&head);
                break;
            case 6:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                deletePos(&head, pos);
                break;
            case 7:
                display(head);
                break;
            case 8:
                head = reverseList(head);
                printf("List reversed iteratively.\n");
                break;
            case 9:
                head = RecurReverseList(head);
                printf("List reversed recursively.\n");
                break;
            case 10:
                printf("Enter data to search: ");
                scanf("%d", &data);
                pos = search(&head, data);
                if (pos != -1)
                    printf("Data found at position %d\n", pos);
                else
                    printf("Data not found\n");
                break;
            case 11:
                printf("Number of nodes: %d\n", countNodes(&head));
                break;
            case 12:
                head2 = copyList(head);
                printf("List copied. New list: ");
                display(head2);
                destroyList(&head2);  // Clean up the copied list
                break;
            case 13:
                sortList(&head);
                printf("List sorted.\n");
                break;
            case 14:
                removeDuplicates(&head);
                printf("Duplicates removed.\n");
                break;
            case 15:
                printf("Creating a second list for merging...\n");
                destroyList(&head2);  
                head2 = NULL;
                int numElements, element;
                
                printf("Enter the number of elements for the second list: ");
                scanf("%d", &numElements);
                
                for (int i = 0; i < numElements; i++) {
                    printf("Enter element %d: ", i + 1);
                    scanf("%d", &element);
                    insertEnd(&head2, element);
    }
    
    printf("Second list: ");
    display(head2);
    
    printf("First list: ");
    display(head);
    
    head = mergeLists(&head, &head2);
    printf("Lists merged.\n");
    printf("Merged list: ");
    display(head);
    break;
            case 16:
                destroyList(&head);
                printf("List destroyed.\n");
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    destroyList(&head);
    destroyList(&head2);

    return 0;
}