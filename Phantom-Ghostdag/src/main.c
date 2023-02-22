#include "utils.h"

void task3_main() {
    // printf("Task3\n");
}

int main(int argc, char *argv[]) {
    
    FILE *fd_in = fopen("blockdag.in", "r");
    FILE *fd_out = fopen("blockdag.out", "w");

    if (!fd_in && !fd_out)
    {
        printf("I/O problem");
        exit(EXIT_FAILURE);
    }

    Graph* graph = create_graph(fd_in);

    switch (argc)
    {
    case 2:
        if (strncmp(argv[1], TASK1, 3) == 0) 
        {
            fprintf(fd_out, "%s", check_cycle(graph));
            break;
        }
    case 3:
        if (strncmp(argv[1], TASK2, 3) == 0) 
        {
            char ** solutions = check_node_realtions(graph, argv[2]);
            for (int i = 0; i < 4; i++)
            {
                fprintf(fd_out, "%s \n", solutions[i]);
                free(solutions[i]);
            }
            free(solutions);
            break;
        } 
        else if (strncmp(argv[1], TASK3, 3) == 0) 
        {
            task3_main();
            break;
        }
    default:
        printf("Incorrect arguments\n");
        break;
    }

    destroy_graph(graph);
    fclose(fd_in);
    fclose(fd_out);

}