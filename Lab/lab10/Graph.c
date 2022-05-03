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
		graph->adl[i]->next = NULL;
	}
	return graph;
}

void addEdgeList(TGraphL* graph, int v1, int v2) {
	//TODO: 1
}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
	//TODO: 2
}

List* dfsRecursive(TGraphL* graph, int s) {
	// TODO 2
	return NULL;
}

List* bfs(TGraphL* graph, int s){
	// TODO: 3
	return NULL;
}


void destroyGraphAdjList(TGraphL* graph){
	// TODO: 4
}

void removeEdgeList(TGraphL* graph, int v1, int v2){
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

void removeNodeList(TGraphL* graph, int v){
	for(int i = 0; i < graph->nn;i++){
		removeEdgeList(graph,v,i);
	}
}
