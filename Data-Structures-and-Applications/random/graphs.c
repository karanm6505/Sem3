#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
typedef struct node{
    int info;
    struct node* next;
}NODE;
void initGraphList(NODE* v[]);
void createGraph(int a[MAX][MAX],NODE* v[MAX],int n);
void addEdgeList(NODE *v[MAX],int src,int dest);
void displayAdjacencyMatrix(int a[MAX][MAX],int n);
void displayAdjacencyList(NODE* v[MAX],int n);
void dfsMatrix(int a[MAX][MAX],int n,int visited[],int src);
void dfsList(NODE* v[MAX],int n,int visited[],int src);
void bfsMatrix(int a[MAX][MAX],int n,int visited[],int src);
void bfsList(NODE* v[MAX],int n,int visited[],int src);
int main()
{
    int n, src, choice;
    int a[MAX][MAX] = {0};
    NODE* v[MAX];
    int visited[MAX] = {0};
    initGraphList(v);
    printf("Enter number of vertices\n");
    scanf("%d", &n);
    createGraph(a, v, n);

    do {
        printf("\nMenu:\n");
        printf("1. Display Adjacency Matrix\n");
        printf("2. Display Adjacency List\n");
        printf("3. Perform DFS (Adjacency Matrix)\n");
        printf("4. Perform DFS (Adjacency List)\n");
        printf("5. Perform BFS (Adjacency Matrix)\n");
        printf("6. Perform BFS (Adjacency List)\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Adjacency Matrix\n");
                displayAdjacencyMatrix(a, n);
                break;
            case 2:
                printf("Adjacency List\n");
                displayAdjacencyList(v, n);
                break;
            case 3:
                printf("Enter source vertex for DFS: adjacency matrix\n");
                scanf("%d", &src);
                dfsMatrix(a, n, visited, src);
                break;
            case 4:
                for (int i = 0; i < n; i++) visited[i] = 0; // Resetting visited
                printf("Enter the source vertex for DFS: adjacency list \n");
                scanf("%d", &src);
                dfsList(v, n, visited, src);
                break;
            case 5:
                for (int i = 0; i < n; i++) visited[i] = 0; // Resetting visited
                printf("Enter the source vertex for BFS: adjacency matrix \n");
                scanf("%d", &src);
                bfsMatrix(a, n, visited, src);
                break;
            case 6:
                for (int i = 0; i < n; i++) visited[i] = 0; // Resetting visited
                printf("Enter the source vertex for BFS: adjacency list \n");
                scanf("%d", &src);
                bfsList(v, n, visited, src);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);
}
void initGraphList(NODE* v[MAX])
{
    for(int i=0;i<MAX;i++)
    {
        v[i] = NULL;
    }
}
void createGraph(int a[MAX][MAX],NODE* v[],int n)
{
    printf("Enter the source and destination vertex of the edge\n");
    printf("Enter -1,-1 to stop\n");
    int src,dest;
    while(1)
    {
        scanf("%d %d",&src,&dest);
        if(src==-1 && dest==-1)
            break;
        a[src][dest] = 1;
        a[dest][src] = 1; //because it's undirectional
        addEdgeList(v,src,dest);
        addEdgeList(v,dest,src);

    }
}
void addEdgeList(NODE* v[MAX],int src,int dest)
{
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    newnode->info = dest;
    newnode->next = NULL;
    if(v[src] == NULL || v[src]->info>dest)
    {
        newnode->next = v[src];
        v[src] = newnode;
    }
    else
    {
        NODE* temp = v[src];
        while(temp->next != NULL && temp->next->info < dest)
        {
            temp =  temp->next;
        }
        newnode->next = temp->next;
        temp->next = newnode;
    }
}
void displayAdjacencyMatrix(int a[MAX][MAX], int n)
{
    for(int i = 0;i<n;i++)
    {
        for(int j = 0; j<n;j++)
        {
            printf("%d",a[i][j]);
        }
        printf("\n");
    }
}
void displayAdjacencyList(NODE* v[MAX],int n)
{
    for(int i=0;i<n;i++)
    {
        printf("Vertex %d",i);
        NODE* p = v[i];
        while(p!=NULL)
        {
            printf("%d ->",p->info);
            p = p->next;
        }
        printf("NULL \n");
    }
}
void dfsMatrix(int a[MAX][MAX],int n,int visited[],int src)
{
    visited[src] = 1;
    printf("%d",src);
    for(int i=0;i<n;i++)
    {
        if(visited[i]==0&&a[src][i]==1)
        {
            dfsMatrix(a,n,visited,i);
        }
    }
}
void dfsList(NODE* v[],int n,int visited[],int src)
{
    visited[src]=1;
    printf("%d",src);
    NODE *p = v[src];
    while(p!=NULL)
    {
        if(visited[p->info]==0)
        {
            dfsList(v,n,visited,p->info);
        }
        p = p->next;
    }
}
void bfsMatrix(int a[MAX][MAX],int n, int visited[],int src)
{
    int queue[MAX],front=0,rear=0;
    queue[rear++] = src;
    visited[src]=1;
    while(front<rear)
    {
        int u = queue[front++];
        printf("%d",u);
        for(int i =0;i<n;i++)
        {
            if(a[u][i]==1&&visited[i]==0)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
        printf("\n");
    }
}
void bfsList(NODE* v[],int n,int visited[],int src)
{
    int queue[MAX],front=0,rear=0;
    queue[rear++] = src;
    visited[src] = 1;
    while(front<rear)
    {
        int u = queue[front++];
        printf("%d",u);
        NODE *p = v[u];
        while(p!=NULL)
        {
            if(visited[p->info]==0)
            {
                queue[rear++] = p->info;
                visited[p->info] = 1;
            }
            p=p->next;
        }
        printf("\n");
    }
}