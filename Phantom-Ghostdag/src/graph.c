#include "utils.h"

ANode create_node(char* name)
{
    ANode node = malloc(sizeof(Graph_Node));
    node->name = name;
    node->next = NULL;
    node->original = NULL;
    return node;
}

ANode find_node(Graph* graph, char* name, int* index)
{
    for (int j = 0; j < graph->nr_nodes; j++)
    {
        if (strlen(name) == strlen(graph->Ad_List[j]->name) &&
            strncmp(graph->Ad_List[j]->name, name,strlen(name)) == 0) {
            if (index)
                *index = j;
            return graph->Ad_List[j];
        }
    }
}

Graph* create_graph(FILE *fd_in)
{
    Graph * graph = malloc(sizeof(Graph));

    fscanf(fd_in, "%d\n", &graph->nr_nodes);
    graph->Ad_List = malloc(sizeof(ANode) * graph->nr_nodes);

    int nr_of_names = 0;
    char **list_of_names = fread_nodes_name(fd_in, &nr_of_names);

    for (int i = 0; i < graph->nr_nodes; i++)
    {
        graph->Ad_List[i] = create_node(list_of_names[i]);
    }

    free(list_of_names);

    for (int i = 0; i < graph->nr_nodes; i++)
    {
        list_of_names = fread_nodes_name(fd_in, &nr_of_names);
        ANode node = find_node(graph, list_of_names[0], NULL);
        free(list_of_names[0]);
        
        for (int j = 1; j < nr_of_names; j++)
        {   
            ANode next_node = create_node(list_of_names[j]);
            next_node->original = find_node(graph, list_of_names[j], NULL);
            node->next = next_node;
            node = next_node;
            next_node = NULL;
        }
        free(list_of_names);
    }
    return graph;
}

void destroy_graph(Graph* graph)
{
    for (int i = 0; i < graph->nr_nodes; i++)
    {
        ANode current_node = graph->Ad_List[i];
        ANode next_node = current_node->next;

        while (next_node != NULL)
        {
            free(current_node->name);
            free(current_node);
            current_node = next_node;
            next_node = current_node->next;
        }
        free(current_node->name);
        free(current_node);
    }
    free(graph->Ad_List);
    free(graph);
}


char** fread_nodes_name(FILE *fd, int* nr_of_names)
{
    char line[256] = {'\0'};
    fgets(line, 256, fd);
    char **list_of_names = malloc(sizeof(char*));
    int nr_in_list = 1;
    int size = sizeof(char);

    for(int i = 0; i < strlen(line); i++)
    {
        if (line[i] == ' ' && line[i+1] == ':')
        {
            i+=2;
        }

        if (size != sizeof(char))
        {
            list_of_names[nr_in_list - 1] = realloc(list_of_names[nr_in_list - 1], size);
        }
        else
        {
            list_of_names[nr_in_list - 1] = malloc(size);
        }

        if (line[i] == '\n')
        {
            list_of_names[nr_in_list - 1][size - 1] = '\0';
            break;
        }
        else if (line[i] == ' ')
        {
            list_of_names[nr_in_list - 1][size - 1] = '\0';
            size = sizeof(char);
            list_of_names = realloc(list_of_names, sizeof(char*) * (++nr_in_list));
        }
        else
        {
            list_of_names[nr_in_list - 1][size - 1] = line[i];
            size+=sizeof(char);
        }        
    }
    
    *nr_of_names = nr_in_list;
    return list_of_names;
}

void delete_list_of_names(char** list, int nr)
{
    for (int i = 0; i < nr; i++)
    {
        free(list[i]);
    }
    free(list);
}

void print_graph(Graph* graph)
{
    for (int i = 0; i < graph->nr_nodes; i++)
    {
        printf("[%s] : ", graph->Ad_List[i]->name);
        ANode next = graph->Ad_List[i]->next;
        while (next != NULL)
        {
            printf("( %s )", next->name);
            next = next->next;
        }
        printf("\n");
    }
}