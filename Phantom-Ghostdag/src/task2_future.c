#include "utils.h"

void future_helper(Graph* graph, int* future_nodes, int node_id)
{
    for (int i = 0; i < graph->nr_nodes; i++)
    {
        ANode test_node = graph->Ad_List[i]->next;
        while (test_node != NULL)
        {
            if (test_node->id == node_id && !future_nodes[i])
            {
                future_nodes[i] = 1;
                future_helper(graph, future_nodes, i);
            }
            test_node = test_node->next;
        }
    }
}

char* future(Graph* graph, ANode node)
{   
    int* future_nodes = calloc(graph->nr_nodes, sizeof(int));
    
    future_helper(graph, future_nodes, node->id);

    int count = 0;
    for (int i = 0; i < graph->nr_nodes; i++)
    {
        if (future_nodes[i])
            count++;
    }

    char** node_names = malloc(sizeof(char*)*count);
    count = 0;
    for (int i = 0; i < graph->nr_nodes; i++)
    {
        if (future_nodes[i]) 
        {
            node_names[count++] = graph->Ad_List[i]->name;
        }
    }
    free(future_nodes);
    return format_respone(node_names, count, FUTURE, node->name);
}