#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef QueueNode TcelQ;
typedef QueueNode *ACelQ;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

typedef Queue TCoada;
typedef Queue *AQ;


Queue* createQueue(void){
	Queue *q = malloc(sizeof(*q));
	q->front = NULL;
	q->rear = NULL;
	q->size = 0;
	return q;
} 

int isQueueEmpty(Queue *q){
	if (q->rear != NULL && q->front != NULL && q->size == 0) return 0;
	else return 1;
}

void enqueue(Queue *q, Item elem){
	if (q) {
		if (q->front == NULL) {
			QueueNode *new = malloc(sizeof(*new));
			new->elem = elem;
			new->next = NULL;
			q->front = new;
			q->rear = new;
			q->size++;
		} else {
			QueueNode *new = malloc(sizeof(*new));
			new->elem = elem;
			new->next = NULL;
			q->rear->next = new;
			q->rear = new;
			q->size++;
		}
	} else {
		printf("Eroare\n");
		exit(1);
	}
	return;
}

Item front(Queue* q){
	return q->front->elem;
}

void dequeue(Queue* q){
	QueueNode *temp = q->front;
	q->front = q->front->next;
	q->size--;
	if (q->front == NULL) {
		q->rear = NULL;
	}
	free(temp);
}

void destroyQueue(Queue *q){
	while(q->front != NULL) {
		QueueNode *aux = q->front;
		q->front = q->front->next;
		free(aux);
	}
	free(q);
}

#endif
