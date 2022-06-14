#include "header.h"

Graph init_graph(int nr_V) {
    Graph graph = malloc(sizeof(*graph));
    graph->nr_V = nr_V;
    graph->nr_E = 0;
    graph->adjLists = malloc(sizeof(List) * nr_V);
    for (int i = 0; i < nr_V; i++) {
        graph->adjLists[i]=malloc(sizeof(Tlist));
        graph->adjLists[i]->next = NULL;
    }
    
    return graph;
}
void add_edge(Graph graph, List *list, char* node) {
    List new_node = malloc(sizeof(*new_node));
    new_node->node = node;
    for (int i = 0; i < graph->nr_V; i++) {
        if (strlen(node) == strlen(graph->adjLists[i]->node) && strncmp(node, graph->adjLists[i]->node, strlen(node)) == 0) {
            new_node->pos = i;
        }    
    }
        new_node->next = (*list)->next;
    (*list)->next = new_node;

    graph->nr_E++;
    return;
}

void print_graph(Graph graph) {
    printf("Nr_E %d\n", graph->nr_E);
    for (int i = 0; i < graph->nr_V; i++) {
        printf("Node [%s] :", graph->adjLists[i]->node);
        List itr = graph->adjLists[i]->next;
        while (itr != NULL) {
            printf("%s ",itr->node);
            itr = itr->next;
        }
        printf("\n");
    }
    return;
}

Graph create_graph() {
    FILE *in = fopen("blockdag.in", "r");
    int nr_nodes = 0;
    fscanf(in, "%d", &nr_nodes);
    Graph graph = init_graph(nr_nodes);
    // printf("%d\n",nr_nodes);

    for (int i = 0; i < nr_nodes; i++) {
        char* node = malloc(WORD);
        fscanf(in,"%s", node);
        graph->adjLists[i]->node = node;
        graph->adjLists[i]->pos = i;
    }
    fscanf(in,"\n");

    char *buffer = malloc(LINE);
    while (fgets(buffer,LINE,in)) {
        char *node = strtok(buffer," :\n");

        for (int i = 0; i < graph->nr_V; i++) {
            if (strlen(node) == strlen(graph->adjLists[i]->node) && strncmp(node, graph->adjLists[i]->node, strlen(node)) == 0) {
                node = strtok(NULL, " :\n");

                while (node != NULL) {
                    char *node_name = calloc(1, strlen(node) + 1);
                    strncpy(node_name, node, strlen(node));
                    add_edge(graph ,&(graph->adjLists[i]), node_name);

                    node = strtok(NULL, " :\n");
                }
                break;
            }
        }
        
        
    }
    free(buffer);
    fclose(in);
    
    return graph;
}

void delete_graph(Graph graph) {
    if (graph == NULL) return;
    
    for (int i = 0; i < graph->nr_V; i++) {
        List iter = graph->adjLists[i];
        while (iter != NULL) {
            List aux = iter->next;
            free(iter->node);
            free(iter);
            iter = aux;
        }
    }
    free(graph->adjLists);
    free(graph);

}

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("No parameters\n");
    } else {
        Graph graph = create_graph();
        if (strncmp(argv[1], "-c1", 3) == 0){
            task1(graph);
        }
        if (strncmp(argv[1], "-c2", 3) == 0){
            if (argc == 2) {
                printf("Not enough parameters\n");
            } else {
                task2(graph, argv[2]);
            }
        }
        if (strncmp(argv[1], "-c3", 3) == 0){
            if (argc == 2) {
                printf("No enough parameters\n");
            } else {
                task3(graph);
            }
        }
        delete_graph(graph);
    }

    return 0;
}