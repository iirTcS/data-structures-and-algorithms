#include "utils.h"
#include "stack.h"

int dfs_cycle_detection(Graph* graph, int pos, int* visited, int* stack, char** name)
{
    if (visited[pos] == 0) 
    {
        visited[pos] = 1;
        stack[pos] = 1;

        ANode node = graph->Ad_List[pos]->next;
        int next_pos = 0;
        while (node != NULL)
        {
            find_node(graph, node->name, &next_pos);

            if ( !visited[next_pos] && dfs_cycle_detection(graph, next_pos, visited, stack, name)) {
                printf("%s\n",graph->Ad_List[next_pos]->name);
                return 1;
            }
            else if (stack[next_pos]) {
                printf("%s\n",graph->Ad_List[next_pos]->name);
                return 1;
            }
            
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
        print_graph(graph);

    for (int i = 0; i < graph->nr_nodes; i++)
    {
        printf("== %s\n", graph->Ad_List[i]->name);
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