#include "header.h"

int is_cycle(Graph graph, int i, int **r, int **v) {
    int *recall = (*r);
    int *visited = (*v);
    if (recall[i]) {
        return 1;
    }

    if (visited[i]) {
        return 0;
    }

    recall[i] = 1;
    visited[i] = 1;
    List iter = graph->adjLists[i]->next;
        while (iter != NULL) {  
            if (is_cycle(graph, iter->pos, r, v)) {
                return 1;
            }
            iter = iter->next;
        }
    recall[i] = 0;
    return 0;
}

int is_dag(Graph graph) {
    int *recall = calloc(graph->nr_V, sizeof(int));
    int *visited = calloc(graph->nr_V, sizeof(int));
    for (int i = 0; i < graph->nr_V; i++) {
        if (is_cycle(graph, i, &recall, &visited)) {
            free(recall);
            free(visited);
            return 0;
        }
    }
    free(recall);
    free(visited);
    return 1;
}

void task1(Graph graph){
    FILE *out = fopen("blockdag.out", "w");
    fprintf(out, "%s\n", ((is_dag(graph)) ? "correct" : "impossible"));
    fclose(out);
}