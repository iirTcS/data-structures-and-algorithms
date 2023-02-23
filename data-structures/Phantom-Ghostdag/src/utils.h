#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TASK1 "-c1"
#define TASK2 "-c2"
#define TASK3 "-c3"
#define NO_CYCLE "correct\n"
#define CYCLE "impossible\n"
#define PAST "past"
#define TIPS "tips"
#define FUTURE "future"
#define ANTICONE "anticone"
#define GRAPH "G"
#define START_NODE "Genesis"

typedef struct TNode
{
    char* name;
    struct TNode *next;
    int id;
} Graph_Node, *ANode;


typedef struct TGraph
{
    int nr_nodes;
    ANode* Ad_List;
} Graph;


ANode create_node(char* name);
ANode find_node(Graph* graph, char* name, int* index);
Graph* create_graph(FILE *fd_in);
char** fread_nodes_name(FILE *fd, int* nr_of_names);
void destroy_graph(Graph* graph);
void delete_list_of_names(char** list, int nr);
void print_graph(Graph* graph);

/* Task1 */
char* check_cycle(Graph* graph);

/* Task2 */
char** check_node_realtions(Graph* graph , char* node);
char* anticone(Graph* graph, ANode node);
char* future(Graph* graph, ANode node);
char* tips(Graph* graph);
char* past(Graph* graph, ANode node);
char* format_respone(char** nodes_names, int names_count, char* type, char* node);
void past_helper(Graph* graph, int *visited, int pos);
void future_helper(Graph* graph, int* future_nodes, int node_id);
int* anticone_helper(Graph* graph, ANode node);

/* Task3 */
void task3_main(Graph* graph, int k);

#endif