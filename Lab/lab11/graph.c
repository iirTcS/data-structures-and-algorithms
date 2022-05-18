#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
}	TGraphL;


void alloc_list(TGraphL * G, int n)
{
    int i;
    G->nn = n;
	G->adl = (ATNode*) malloc((n+1) * sizeof(ATNode));
	for(i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL *G)
{
    int i;
    ATNode it;
    for(i = 1; i < G->nn; i++){
		it = G->adl[i];
		while(it != NULL){
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
 TNode *t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v2; t->c=c; t->next = G->adl[v1]; G->adl[v1]=t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v1;  t->c=c; t->next = G->adl[v2]; G->adl[v2]=t;
}


void dijkstra(TGraphL G, int s)
{
    MinHeap *h = newQueue(G.nn);
	int val[G.nn];

	for (int i = 0; i < G.nn; i++) {
		val[i] = INT_MAX - 100;
	}
	val[s] = 0;
	insert(h, s, val[s]);

	while (!isEmpty(h)) {
		MinHeapNode * u = removeMin(h);

		for(ATNode t = G.adl[u->v]; t != NULL; t = t->next) {
			if (val[t->v] > val[u->v] + t->c) {
				val[t->v] = val[u->v] + t->c;
				if (isInMinHeap(h,t->v)) {
					for (int i = 0; i < h->size; i++) {
						if (h->elem[i]->v == t->v) {
							h->elem[i]->d = val[t->v];
							SiftUp(h, t->v, val[t->v]);
							break;
						}
					}
				} else {
					insert(h, t->v, val[t->v]);
				}
			}
		}
	}
	printf("Start node: %d\n",s);

	for (int i = 0; i < G.nn; i++) {
		if (i != s)
		printf("node: %d -- dist: %d\n",i, val[i]);
	}
	printf("\n");
	
}

void Prim(TGraphL G) {
	
	MinHeap *h = newQueue(G.nn);
	int val[G.nn];
	int color[G.nn];
	int dad[G.nn];

	for (int i = 0; i < G.nn; i++) {
		val[i] = INT_MAX;
		color[i] = 0;
		dad[i] = 0;
	}
	val[0] = 0; dad[0] = 0;
	insert(h,0, val[0]);


	while (!isEmpty(h)) { 
		MinHeapNode * u = removeMin(h);
		for(ATNode t = G.adl[u->v]; t != NULL; t = t->next) {
			if (color[t->v] == 0 && t->c < val[t->v]) {
				val[t->v] = t->c;
				dad[t->v] = u->v;

				if (isInMinHeap(h,t->v)) {
					for (int i = 0; i < h->size; i++) {
						if (h->elem[i]->v == t->v) {
							h->elem[i]->d = val[t->v];
							SiftUp(h, t->v, val[t->v]);
						}
					}
				} else {
					insert(h, t->v, val[t->v]);
				}

			}
		}
		color[u->v] = 1;
	}

    printf("Start node: %d\n",0);

	for (int i = 1; i < G.nn; i++) {
		printf("Parent[%d] node[%d]\n",dad[i], i);
	}
}


int main()
{
    int i,v1,v2,c;
	int V,E;
	TGraphL G;
	ATNode t;
	freopen ("graph.in", "r", stdin);
	scanf ("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i=1; i<=E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
	    insert_edge_list(&G, v1,v2, c);
	}

	for(i=0;i<G.nn;i++)
	{
    	printf("%d : ", i);
    	for(t = G.adl[i]; t != NULL; t = t->next)
   			 printf("[%d; %d] ",t->v, t->c);
    		 printf("\n");
	}
	dijkstra(G,0);
	Prim(G);

	return 0;
}
