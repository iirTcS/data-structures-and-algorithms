#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TASK1 "-c1"
#define TASK2 "-c2"
#define TASK3 "-c3"
#define NO_CYCLE "correct"
#define CYCLE "impossible"

typedef struct TNode
{
    char* name;
    struct TNode *next;
    struct TNode *original;
} Graph_Node, *ANode;


typedef struct TGraph
{
    int nr_nodes;
    ANode* Ad_List;
} Graph;



char* check_cycle(Graph* graph);


ANode create_node(char* name);
ANode find_node(Graph* graph, char* name, int* index);
Graph* create_graph(FILE *fd_in);
char** fread_nodes_name(FILE *fd, int* nr_of_names);
void destroy_graph(Graph* graph);
void delete_list_of_names(char** list, int nr);
void print_graph(Graph* graph);


#endif