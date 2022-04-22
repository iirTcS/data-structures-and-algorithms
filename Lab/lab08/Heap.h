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
	if (idx != h->size) {
		while (h->elem[idx].prior < h->elem[getLeftChild(idx)].prior ) {
			int sc = 0;
			if (getLeftChild(idx) < h->size || getRightChild(idx) < h->size) {
				if (getRightChild(idx) >= h->size) {
					sc = getLeftChild(idx);
					ItemType aux = h->elem[idx];
					h->elem[idx] = h->elem[sc];
					h->elem[sc] = aux;
					break;
				} else if (h->elem[getLeftChild(idx)].prior < h->elem[getRightChild(idx)].prior) {
					sc = getRightChild(idx);
				} else {
					sc = getLeftChild(idx);
				}
				if (sc >= h->size) {
					break;
				}
				ItemType aux = h->elem[idx];
				h->elem[idx] = h->elem[sc];
				h->elem[sc] = aux;
				idx = sc;
				if (idx >= h->size){
					break;
				}
			} else {
				break;
			}
		}
		
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

