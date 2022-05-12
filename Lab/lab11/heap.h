#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

typedef struct MinHeapNode
{
    int  v;
    int d;
} MinHeapNode;


typedef struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    MinHeapNode **elem;
} MinHeap;


MinHeapNode* newNode(int v, int d)
{
    MinHeapNode* new = malloc(sizeof(MinHeapNode));
    new->d = d;
    new->v = v;
    return new;
}

MinHeap* newQueue(int capacity)
{
    MinHeap *q = malloc(sizeof(*q));
    q->size = 0;
    q->capacity = capacity;
    q->pos = NULL;
    q->elem = malloc(capacity * sizeof(MinHeapNode *));
    q->pos = malloc(capacity * sizeof(int));
}

void swap(MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode **tmp = a;
    a = b;
    b = tmp;
}

int getLeftChild(int i) {
    return 2 * i + 1;
}

int getRightChild(int i) {
    return 2 * i + 2;
}

int getParent(int i) {
    return floor((i - 1) / 2);
}

void SiftDown(MinHeap* h, int idx)
{
    int leftChild = getLeftChild(idx);
    int rightChild = getRightChild(idx);
    int smallest = idx;

    if (leftChild < h->size && h->elem[leftChild]->d < h->elem[smallest]->d) {
        smallest = leftChild;
    }

    if (rightChild < h->size && h->elem[rightChild]->d < h->elem[smallest]->d) {
        smallest = rightChild;
    }

     if (smallest != idx) {
        swap(&(h->elem[idx]), &(h->elem[smallest]));

        /* Carry on. */
        SiftDown(h, smallest);
    }

}

int isEmpty(MinHeap* h)
{
    return (h == NULL) || (h->size == 0);
}

MinHeapNode* removeMin(MinHeap* h)
{
    
}

void SiftUp(MinHeap* h, int v, int d)
{
    // int parent = getParent()
}

void insert(MinHeap* h, int v, int d)
{
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->elem = realloc(h->elem, h->capacity * sizeof(MinHeapNode*));
        h->pos = realloc(h->pos, h->capacity * sizeof(int));
    }

    h->elem[h->size] = newNode(v,d);
    h->size++;
}

int isInMinHeap(MinHeap *h, int v)
{
  
}

#endif

