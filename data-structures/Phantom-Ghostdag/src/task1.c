#include "utils.h"
#include "stack.h"

int dfs_cycle_detection(Graph* graph, int pos, int* visited, int* stack, char** name)
{
    if (visited[pos] == 0) 
    {
        visited[pos] = 1;
        stack[pos] = 1;

        ANode node = graph->Ad_List[pos]->next;
        while (node != NULL)
        {
            if ( !visited[node->id] && dfs_cycle_detection(graph, node->id, visited, stack, name))
                return 1;
            else if (stack[node->id])
                return 1;
            
            node = node->next;
        } 
    }    
    stack[pos] = 0;
    return 0;
}

char* check_cycle(Graph* graph) {
    int * visited = calloc(graph->nr_nodes, sizeof(int));
    int *stack = calloc(graph->nr_nodes, sizeof(int));
    char* name = NULL;
    
    for (int i = 0; i < graph->nr_nodes; i++)
    {
        if ( !visited[i] && dfs_cycle_detection(graph, i, visited, stack, &name)) 
        {
            free(visited);
            free(stack);
            return CYCLE;  
        }

    }
    free(visited);
    free(stack);
    return NO_CYCLE;
}