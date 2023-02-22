#include "utils.h"

char *format_respone(char** nodes_names, int names_count, char* type, char* node)
{
    const int special_char = 5;
    char *formated_string = calloc(strlen(type) + strlen(node) + special_char, sizeof(char));
    int size = 0;
    
    strncat(formated_string, type, strlen(type));
    formated_string[strlen(formated_string)] = '(';
    strncat(formated_string, node, strlen(node));
    formated_string[strlen(formated_string)] = ')';
    formated_string[strlen(formated_string)] = ' ';
    formated_string[strlen(formated_string)] = ':';
    for (int i = 0; i < names_count; i++)
    {
        int length = strlen(formated_string);
        formated_string = realloc(formated_string, 
                                length + strlen(nodes_names[i]) + 2);
        
        formated_string[length] = ' ';
        formated_string[length + 1] = '\0';
        strncat(formated_string, nodes_names[i], strlen(nodes_names[i]));   
    }
    if (nodes_names)
        free(nodes_names);
    return formated_string;
}

void bfs(Graph* graph, int *visited, int pos)
{
    if(visited[pos] == 0)
    {
        visited[pos] = 1;
        ANode node = graph->Ad_List[pos]->next;
        while (node != NULL)
        {
            visited[node->id] = 1;
            node = node->next;
        }

        node = graph->Ad_List[pos]->next;
        while (node != NULL)
        {
            visited[node->id] = 0;
            bfs(graph, visited, node->id);
            node = node->next;
        }
    }
    return;
}


char** check_node_realtions(Graph* graph, char* node_name)
{
    char ** to_return = malloc(sizeof(char*) * 4);
    ANode node = find_node(graph, node_name, NULL);
    to_return[0] = past(graph, node);
    to_return[1] = future(graph, node);
    to_return[2] = anticone(graph, node);
    to_return[3] = tips(graph);
    return to_return;
}