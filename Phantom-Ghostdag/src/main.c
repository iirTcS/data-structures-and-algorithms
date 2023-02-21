#include "utils.h"

void task2_main() {
    printf("Task2\n");
}

void task3_main() {
    printf("Task3\n");
}

int main(int argc, char *argv[]) {
    
    FILE *fd_in = fopen("blockdag.in", "r");
    FILE *fd_out = fopen("blockdag.out", "w");

    Graph* graph = create_graph(fd_in);

    switch (argc)
    {
    case 2:
        if (strncpy(argv[1], TASK1, 3)) 
        {
            fprintf(fd_out,"%s\n",check_cycle(graph));
            break;
        }
    case 3:
        if (strncpy(argv[1], TASK2, 3)) 
        {
            task2_main();
            break;
        } 
        else if (strncpy(argv[1], TASK3, 3)) 
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