#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 50

typedef struct Heap
{
    int arr[MAX];
    int size;
    bool isHeap;
}Heap;
void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void Heapify(Heap* heap, int index)
{
    int greater;
    if(heap->isHeap)
    {
        return;
    }
    else
    {
        int lchild = 2 * index + 1;
        int rchild = 2 * index + 2;
        if (lchild >= heap->size) return;
        if (rchild >= heap->size) greater = lchild;
        else greater = (heap->arr[lchild] > heap->arr[rchild]) ? lchild : rchild;

        if (heap->arr[greater] > heap->arr[index])
        {
            swap(&heap->arr[greater], &heap->arr[index]);
            Heapify(heap, greater);
        }
        return;
    }
    return;
}
void HeapButtomUp(Heap* heap)

int main()