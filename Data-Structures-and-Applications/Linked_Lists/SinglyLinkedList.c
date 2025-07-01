#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int info;
    struct node* next;
}NODE;
typedef struct list
{
    NODE* head;
}LIST;
NODE* createNode(int ele)
{
    NODE* newNode = (NODE*)(malloc(sizeof(NODE)));
    if (newNode == NULL) 
        return NULL;  
    newNode->info = ele;
    newNode->next = NULL;
    return newNode;
}
LIST* createList(NODE* head)
{
    LIST* newList = (LIST*)(malloc(sizeof(LIST)));
    if (newList == NULL) 
        return NULL; 
    newList->head = head;
    return newList;
}
NODE* insertFrontHelper(NODE* head, int ele)
{
    NODE* newNode = createNode(ele);
    if (newNode == NULL) 
        return head; 
    
    newNode->next = head;
    return newNode;
}
LIST* insertFront(LIST* ll, int ele)
{
    if (ll == NULL) 
        return NULL;
    ll->head = insertFrontHelper(ll->head, ele);
    return ll;
}
NODE* insertEndHelper(NODE* head, int ele)
{
    NODE* newNode = createNode(ele);
    if (newNode == NULL) 
    return head;  
    
    if (head == NULL) 
    {
        return newNode;
    }
    
    NODE* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;  
}
LIST* insertEnd(LIST* ll, int ele)
{
    if (ll == NULL) return NULL;
    
    ll->head = insertEndHelper(ll->head, ele);
    return ll;
}
NODE* insertPosHelper(NODE* head, int ele, int pos)
{
    if (pos < 1) 
    {
        return head;
    } 
    if (pos == 1) 
    {
        return insertFrontHelper(head, ele);  
    }
    
    NODE* newNode = createNode(ele);
    if (newNode == NULL) 
        return head;
    
    NODE* temp = head;
    int count = 1;
    
    while (temp != NULL && count < pos - 1) {
        temp = temp->next;
        count++;
    }
    
    if (temp == NULL) 
    {
        free(newNode);  
        return head;
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}
LIST* insertPos(LIST* ll, int ele, int pos)
{
    if (ll == NULL) return NULL;
    
    ll->head = insertPosHelper(ll->head, ele, pos);
    return ll;
}
NODE* deleteFrontHelper(NODE* head)
{
    if(head == NULL)
        return NULL;
    NODE* temp = head;
    head = temp->next;
    free(temp);
    return head;
}
LIST* deleteFront(LIST* ll)
{
    if(ll == NULL)
        return NULL;
    ll->head = deleteFrontHelper(ll->head);
    return ll;
}
NODE* deleteEndHelper(NODE* head)
{
    if(head == NULL)
        return NULL;
    if(head->next == NULL)
    {
        free(head);
        return NULL;
    }
    NODE* temp = head;
    while(temp->next->next != NULL)
    {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    return head;
}
LIST* deleteEnd(LIST* ll)
{
    if(ll == NULL)
        return NULL;
    ll->head = deleteEndHelper(ll->head);
    return ll;
}
NODE* deletePosHelper(NODE* head, int pos)
{
    if(head == NULL || pos < 1)
        return NULL;
    
    if(pos == 1)
        return deleteFrontHelper(head);

    NODE* curr = head;
    NODE* prev = NULL;
    int count = 1;

    while(curr != NULL && count < pos)
    {
        prev = curr;
        curr = curr->next;
        count++;
    }

    if(curr == NULL)
        return head;

    prev->next = curr->next;
    free(curr);
    return head;
}
LIST* deletePos(LIST* ll, int pos)
{
    if(ll == NULL)
        return NULL;
    ll->head = deletePosHelper(ll->head, pos);
    return ll;
}
LIST* destroyList(LIST* ll)
{
    if(ll == NULL)
        return NULL;
        
    NODE* curr = ll->head;
    while(curr != NULL)
    {
        NODE* temp = curr;
        curr = curr->next;
        free(temp);
    }
    
    ll->head = NULL;
    free(ll);
    return NULL;
}
void printList(LIST* ll)
{
    if(ll->head == NULL)
    {
        printf("Empty list\n");
        return;
    }
    NODE* temp = ll->head;
    while(temp != NULL)
    {
        printf("%d", temp->info);
        temp = temp->next;
        if(temp!=NULL)
        {
            printf("->");
        }
    }
}
int searchElement(LIST* ll, int ele)
{
    if(ll == NULL || ll->head == NULL)
        return -1;

    NODE* temp = ll->head;
    int index = 1;
    while(temp != NULL)
    {
        if(temp->info == ele)
            return index;

        temp = temp->next;
        index++;
    }
    return -1;   
}
int lengthListHelper(NODE* head)
{
    int length = 0;
    NODE* temp = head;
    while(temp != NULL)
    {
        temp = temp->next;
        length++;
    }
    return length;
}
int lengthList(LIST* ll)
{
    if(ll == NULL || ll->head == NULL)  
        return 0;
    return lengthListHelper(ll->head);
}
NODE* reverseListIterHelper(NODE* head)
{
    NODE* prev = NULL;
    NODE* next = NULL;  
    NODE* curr = head;
    while(curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
LIST* reverseListIter(LIST* ll)
{
    if(ll==NULL)
        return NULL;
    ll->head = reverseListIterHelper(ll->head);
    return ll;
}
NODE* reverseListRecurHelper(NODE* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    NODE* tail = reverseListRecurHelper(head->next);
    head->next->next = head;
    head->next = NULL;
    return tail;
}
LIST* reverseListRecur(LIST* ll)
{
    if(ll==NULL)
        return NULL;
    ll->head = reverseListRecurHelper(ll->head);
    return ll;
}
NODE* middleElement(NODE* head)
{
    NODE* slow = head;
    NODE* fast = head;
    while(fast!= NULL && fast->next != NULL)
    {
        slow = slow->next; //One step
        fast = fast->next->next; //Two step
    }
    return slow;
}
LIST* concatList(LIST* ll1, LIST* ll2)
{
    if(ll1 != NULL && ll2 == NULL)
        return ll1;
    if(ll1 == NULL && ll2 != NULL)
        return ll2;
    if(ll1 == NULL && ll2 == NULL)
        return NULL;
    NODE* temp1 = ll1->head;
    while(temp1->next != NULL)
    {
        temp1 = temp1->next;
    }
    temp1->next = ll2->head;
    return ll1;
}
int isCircularHelper(NODE* head)
{
    if(head == NULL)
        return 0;
    NODE* slow = head;
    NODE* fast = head;
    while(fast!=NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
            return 1;
    }
    return 0;
}
int isCircular(LIST* ll)
{
    if(ll==NULL)
        return 0;
    return isCircularHelper(ll->head);
}
NODE* sortListHelper(NODE* head)
{
    if(head == NULL || head->next == NULL)
        return head;
    
    int len = lengthListHelper(head);
    
    for(int i = 0; i < len-1; i++)
    {
        NODE* curr = head;
        for(int j = 0; j < len-i-1; j++)
        {
            if(curr->info > curr->next->info)
            {
                int temp = curr->info;
                curr->info = curr->next->info;
                curr->next->info = temp;
            }
            curr = curr->next;
        }
    }
    return head;
}
LIST* sortListAscending(LIST* ll)
{
    if(ll == NULL)
        return NULL;
    ll->head = sortListHelper(ll->head);
    return ll;
}
LIST* sortListDescending(LIST* ll)
{
    if(ll == NULL)
        return NULL;
    ll = sortListAscending(ll);
    ll = reverseListRecur(ll);  
    return ll;
}
int main()
{
    LIST* ll = createList(NULL);
    LIST* ll2 = createList(NULL);  // for concat operation
    int choice, element, position;
    NODE* middle;
    
    do
    {
        printf("\n\nLinked List Operations:");
        printf("\n1. Insert Front");
        printf("\n2. Insert End");
        printf("\n3. Insert at Position");
        printf("\n4. Delete Front");
        printf("\n5. Delete End");
        printf("\n6. Delete from Position");
        printf("\n7. Search Element");
        printf("\n8. Print List");
        printf("\n9. Length of List");
        printf("\n10. Reverse List (Iterative)");
        printf("\n11. Reverse List (Recursive)");
        printf("\n12. Find Middle Element");
        printf("\n13. Concatenate Lists");
        printf("\n14. Check if Circular");
        printf("\n15. Sort List");
        printf("\n16. Destroy List");
        printf("\n0. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter element: ");
                scanf("%d", &element);
                insertFront(ll, element);
                break;
                
            case 2:
                printf("Enter element: ");
                scanf("%d", &element);
                insertEnd(ll, element);
                break;
                
            case 3:
                printf("Enter element and position: ");
                scanf("%d %d", &element, &position);
                insertPos(ll, element, position);
                break;
                
            case 4:
                deleteFront(ll);
                break;
                
            case 5:
                deleteEnd(ll);
                break;
                
            case 6:
                printf("Enter position: ");
                scanf("%d", &position);
                deletePos(ll, position);
                break;
                
            case 7:
                printf("Enter element to search: ");
                scanf("%d", &element);
                position = searchElement(ll, element);
                if(position != -1)
                    printf("Element found at position %d\n", position);
                else
                    printf("Element not found\n");
                break;
                
            case 8:
                printList(ll);
                break;
                
            case 9:
                printf("Length of list: %d\n", lengthList(ll));
                break;
                
            case 10:
                reverseListIter(ll);
                printf("List reversed iteratively\n");
                break;
                
            case 11:
                reverseListRecur(ll);
                printf("List reversed recursively\n");
                break;
                
            case 12:
                middle = middleElement(ll->head);
                if(middle)
                    printf("Middle element: %d\n", middle->info);
                else
                    printf("List is empty\n");
                break;
                
            case 13:
                printf("Enter elements for second list (0 to stop):\n");
                while(1) {
                    scanf("%d", &element);
                    if(element == 0) break;
                    insertEnd(ll2, element);
                }
                ll = concatList(ll, ll2);
                printf("Lists concatenated\n");
                break;
                
            case 14:
                if(isCircular(ll))
                    printf("List is circular\n");
                else
                    printf("List is not circular\n");
                break;
                
            case 15:
                printf("\n1. Sort Ascending\n2. Sort Descending\nEnter choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                if(sortChoice == 1)
                {
                    sortListAscending(ll);
                    printf("List sorted in ascending order\n");
                }
                else if(sortChoice == 2)
                {
                    sortListDescending(ll);
                    printf("List sorted in descending order\n");
                }
                else
                    printf("Invalid choice!\n");
                break;
                
            case 16:
                ll = destroyList(ll);
                printf("List destroyed\n");
                break;
                
            case 0:
                ll = destroyList(ll);
                ll2 = destroyList(ll2);
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 0);
    
    return 0;
}
