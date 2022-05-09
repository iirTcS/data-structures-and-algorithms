#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphL* createGraphAdjList(int numberOfNodes) {
	TGraphL *graph = malloc(sizeof(*graph));
	graph->nn = numberOfNodes;
	graph->adl = malloc(sizeof(ATNode) * numberOfNodes);
	for (int i = 0; i < numberOfNodes; i++) {
		// graph->adl[i] = malloc(sizeof(TNode));
		graph->adl[i] = NULL;
	}
	return graph;
}

void addEdgeList(TGraphL* graph, int v1, int v2) {
	if (graph) {
			ATNode new1 = malloc(sizeof(TNode));
			new1->next = graph->adl[v1];
			new1->v = v2;
			graph->adl[v1] = new1;

			
			ATNode new = malloc(sizeof(TNode));
			new->next = graph->adl[v2];
			new->v = v1;
			graph->adl[v2] = new;
	}
}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
	// Visited node
	visited[s] = 1;
	enqueue(path, s);

	// Every neighbour
	for (TNode* aux = graph->adl[s]; aux!= NULL; aux = aux->next) {
		if (visited[aux->v] == 0) {
			dfsRecHelper(graph, visited, path, aux->v);
		}
	}
}

List* dfsRecursive(TGraphL* graph, int s) {
	List *path = createList();
	int *visited = calloc(sizeof(int), graph->nn);
	dfsRecHelper(graph, visited, path, s);
	free(visited);
	return path;
}

List* bfs(TGraphL* graph, int s) {
	Queue *q = createQueue();
	List *l = createList();
	int *visited = calloc(sizeof(int), graph->nn);
	enqueue(q, s);
	enqueue(l, s);
	visited[s] = 1;

	while (!isQueueEmpty(q)) {
		int v = front(q);
		dequeue(q);
		for (TNode *aux = graph->adl[v]; aux != NULL; aux = aux->next) {
			if (visited[aux->v] == 0) {
				visited[aux->v] = 1;
				enqueue(l,aux->v);
				enqueue(q, aux->v);
			}
		}
	}
	destroyQueue(q);
	free(visited);
	return l;
}


void destroyGraphAdjList(TGraphL* graph) {
	for (int i = 0; i < graph->nn; i++) {
		TNode* it = graph->adl[i]; 
		while (it != NULL) {
			TNode* aux = it;
			it = it->next;
			free(aux);
		}
	}
	free(graph->adl);
	free(graph);
}

void removeEdgeList(TGraphL* graph, int v1, int v2) {
	TNode* it = graph->adl[v1];
	TNode* prev = NULL;
	while(it != NULL && it->v != v2){
		prev = it;
		it = it->next;
	}

	if(it == NULL)return;

	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while(it != NULL && it->v != v1){
		prev = it;
		it = it->next;
	}
	if(it == NULL) return;
	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL* graph, int v) {
	for(int i = 0; i < graph->nn;i++){
		removeEdgeList(graph,v,i);
	}
}
