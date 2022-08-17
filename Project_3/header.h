#ifndef _header_
#define _header_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define WORD 10
#define LINE 255

typedef struct list {
	char *node;
    int pos;
	struct list *next;
}Tlist,*List;

typedef struct Tgraph {
	int nr_V;       // nr de noduri din graf
	int nr_E;
	List *adjLists; // vectorul cu listele de adiacență
}Tgraph,*Graph;

void delete_graph(Graph);
Graph create_graph();
void print_graph(Graph);
void add_edge(Graph, List *, char*);
Graph init_graph(int);

void task1();
int is_dag(Graph);

void task2(Graph, char*);

void task3(Graph);




#endif