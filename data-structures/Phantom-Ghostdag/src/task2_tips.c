#include "utils.h"

char* tips(Graph* graph)
{
    int* visited = calloc(graph->nr_nodes, sizeof(int));
    int count = 0;
    for (int i = 0; i < graph->nr_nodes; i++)
    {
        ANode node = graph->Ad_List[i]->next;
        if (node)
            while (node != NULL)
            {
                if (!visited[node->id]) 
                {
                    visited[node->id] = 1;
                    count++;
                }
                node = node->next;
            }
    }

    char** nodes_names = malloc(sizeof(char*) * count);
    count = 0;
    for (int i = 0; i < graph->nr_nodes; i++)
    {
        if(!visited[i])
            nodes_names[count++] = graph->Ad_List[i]->name;
    }
    free(visited);
    
    return format_respone(nodes_names, count, TIPS, GRAPH);
}