#include "utils.h"

int* anticone_helper(Graph* graph, ANode node)
{
    int* visited = calloc(graph->nr_nodes, sizeof(int));
    past_helper(graph, visited, node->id);
    future_helper(graph, visited, node->id);
    return visited;
}

char* anticone(Graph* graph, ANode node)
{    
    int* visited = anticone_helper(graph, node);

    int count = 0;

    for (int i = 0; i < graph->nr_nodes; i++)
    {
        if (!visited[i])
            count++;
    }

    char** node_names = malloc(sizeof(char*)*count);
    count = 0;
    for (int i = 0; i < graph->nr_nodes; i++)
    {
        if (!visited[i]) 
        {
            node_names[count++] = graph->Ad_List[i]->name;
        }
    }
    free(visited);
    return format_respone(node_names, count, ANTICONE, node->name);
}