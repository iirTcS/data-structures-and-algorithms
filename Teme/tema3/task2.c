#include "header.h"

void print_sorted(Graph graph, int *visited, FILE *out) {
    int nr_nodes = 0;
    for (int i = 0; i < graph->nr_V; i++) {
        if (visited[i]) {
            nr_nodes++;
        }
    }

    while(nr_nodes > 0) {
        char* min = calloc(WORD,1);
        for (int i = 0; i < WORD; i++) {
            min[i] = 'Z';
        }
        
        int pos = 0;
        for (int j = 0; j < graph->nr_V; j++) {
            if (visited[j]) {
                if (strncmp(min,graph->adjLists[j]->node, strlen(graph->adjLists[j]->node)) > 0) {
                    pos = j;
                    free(min);
                    min = calloc(WORD,1);
                    strncpy(min,graph->adjLists[j]->node, strlen(graph->adjLists[j]->node));
                }
            }
        }
        nr_nodes--;
        fprintf(out, " %s", min);
        visited[pos] = 0;
        free(min);
    }
    fprintf(out,"\n");
}

void dfs_mod_past(Graph graph, int** vis, int node) {
    int *visited = (*vis);
    visited[node] = 1;
    List iter = graph->adjLists[node]->next;
    while (iter != NULL) {
        if (!visited[iter->pos]) {
            dfs_mod_past(graph, vis, iter->pos);
        }
        iter = iter->next;
    }

}

void past(Graph graph, char* node, FILE *out) {
    int *visited = calloc(graph->nr_V, sizeof(int));
    for (int i = 0; i < graph->nr_V; i++) {
        if ((strlen(node) == strlen(graph->adjLists[i]->node)) &&
            (strncmp(graph->adjLists[i]->node, node, strlen(node)) == 0)) {
                List iter = graph->adjLists[i]->next;
                while (iter != NULL) {
                    dfs_mod_past(graph, &visited, iter->pos);
                    iter = iter->next;
                }
            }
    }
    fprintf(out, " %s", graph->adjLists[0]->node);
    visited[0] = 0;

    print_sorted(graph, visited, out);

    free(visited);
    return;
}

// int dfs_mod_future(Graph graph, int ** vis, int** b,int i, char* node) {
//     printf("%d node\n",i);
//     int *visited = (*vis);
//     int *been = (*b);
//     List iter = graph->adjLists[i]->next;
//     while (iter != NULL) {
//         if ((strlen(node) == strlen(iter->node)) &&
//             (strncmp(iter->node, node, strlen(node)) == 0)) {
//             return 1;
//         }
//         if (!visited[iter->pos]) {
//             return dfs_mod_future(graph, vis, b, iter->pos, node);
//         }
//         iter = iter->next;
//     }
//     // visited[i] = 0;
//     return 0;
// }

// void future(Graph graph, char* node, FILE *out) {
//     int *visited = calloc(graph->nr_V, sizeof(int));
//     int *been = calloc(graph->nr_V, sizeof(int));
//     int pos = 0;
//     for (int i = 0; i < graph->nr_V; i++) {
        
//     }
    

//     for (int i = 0; i < graph->nr_V; i++) {
//         been[i] = dfs_mod_future(graph, &visited,i,);
//         free(visited);
//         visited = calloc(graph->nr_V, sizeof(int));
//     }

//     print_sorted(graph, been, out);
    
//     free(visited);
//     free(been);
//     return;
// }

void task2(Graph graph, char* node) {
    FILE *out = fopen("blockdag.out", "w");
    fprintf(out, "past(%s) :",node);
    past(graph, node, out);

    fprintf(out, "future(%s) :",node);
    // future(graph, node, out);
    fclose(out);
}