#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
}ItemType;

typedef struct heap{
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType *elem; // array of elements
} PriQueue, *APriQueue;


PriQueue* makeQueue(int maxHeapSize){
	PriQueue *queue = malloc(sizeof(*queue));
	queue->maxHeapSize = maxHeapSize;
	queue->elem = malloc(sizeof(ItemType) * maxHeapSize);
	queue->size = 0;
	return queue;
}

int getLeftChild(int i){
	return 2*i + 1;
}

int getRightChild(int i) {
	return 2*i + 2;
}

int getParent(int i) {
	return (i - 1) / 2;
}

ItemType getMax(APriQueue h) {
	return h->elem[0];
}

void siftUp(APriQueue h, int idx) {
	if (idx != 0) {
		while(idx != 0 && h->elem[idx].prior > h->elem[getParent(idx)].prior) {
			ItemType aux = h->elem[idx];
			h->elem[idx] = h->elem[getParent(idx)];
			h->elem[getParent(idx)] = aux;
			idx = getParent(idx);
		}
	}
	return;
}


void insert(PriQueue *h, ItemType x) {
	if (h->size  == h->maxHeapSize){
		h->elem = realloc(h->elem, h->maxHeapSize * 2 * sizeof(ItemType));
		h->maxHeapSize = h->maxHeapSize * 2;
	}
	h->elem[h->size] = x;
	siftUp(h, h->size);
	h->size++;
}

void siftDown(APriQueue h, int idx){
	while (getLeftChild(idx) < h->size) {
		int schimb = getLeftChild(idx);
		if (schimb < h->size - 1 && h ->elem[schimb].prior < h->elem[getRightChild(idx)].prior) {
			schimb = getRightChild(idx);
		}
		if (h->elem[idx].prior > h->elem[schimb].prior) {
			break;
		}
		ItemType aux = h->elem[idx];
		h->elem[idx] = h->elem[schimb];
		h->elem[schimb] = aux;
		idx = schimb;
	}
}

void removeMax(APriQueue h) {
	h->elem[0] = h->elem[h->size - 1];
	--h->size;
	siftDown(h, 0);
}

void freeQueue(APriQueue h){
	free(h->elem);
	free(h);
}

#endif

