#include <stdio.h>
#include <stdlib.h>

#include "func.h"

void clear_graph(graph* g) {
    for (int i = 0; i < g->cnt_v; i++) {
        for (int j = 0; j < g->cnt_v; j++) {
            g->matrix[i][j] = 0;
        }
    }
}

static void print_graph_to_stream(FILE* out, graph* g) {
    fprintf(out, "  ");
    for (int i = 0; i < g->cnt_v; i++) {
        fprintf(out, "%d ", i);
    }
    fprintf(out, "\n");
    for (int i = 0; i < g->cnt_v; i++) {
        fprintf(out, "%d ", i);
        for (int j = 0; j < g->cnt_v; j++) {
            fprintf(out, "%d ", g->matrix[i][j]);
        }
        fprintf(out, "\n");
    }
}

static void print_topological_sort_to_stream(FILE* out, graph* g) {
    int* result = (int*)malloc(sizeof(int) * g->cnt_v);
    int res = topological_sort(g, result);

    if (res == 0) {
        fprintf(out, "The topological sort is empty\n");
    }
    else {
        for (int i = 0; i < g->cnt_v; i++) {
            fprintf(out, "%d ", result[i]);
        }
        fprintf(out, "\n");
    }

    free(result);
}

static void print_topological_sort_to_file(graph* g, const char* filename) {
    FILE* out = fopen(filename, "w");
    if (out == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    print_topological_sort_to_stream(out, g);
    fclose(out);
    printf("Topological sort was written to %s\n", filename);
}

static void print_graph_to_file(graph* g, const char* filename) {
    FILE* out = fopen(filename, "w");
    if (out == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    print_graph_to_stream(out, g);
    fclose(out);
    printf("Graph was written to %s\n", filename);
}

static void skip_input_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        if (freopen(argv[1], "r", stdin) == NULL) {
            printf("Error opening input file %s\n", argv[1]);
            return 1;
        }
        if (freopen(argv[2], "w", stdout) == NULL) {
            printf("Error opening output file %s\n", argv[2]);
            return 1;
        }
    }
    else if (argc != 1) {
        printf("Usage: %s [input.txt output.txt]\n", argv[0]);
        return 1;
    }

    printf("There is the graph programm, that can do topological sort\n");
    printf("At first, init a graph with n vertices: ");
    printf("1. add adge from x to y\n");
    printf("2. delete adge from x to y\n");
    printf("3. topological sort\n");
    printf("4. topological sort to file\n");
    printf("5. print graph\n");
    printf("6. print graph to file\n");
    printf("7. Exit\n");

    graph g;
    int n;
    int from;
    int to;
    int choice;

    printf("Enter a number of vertices: ");
    if (scanf("%d", &n) != 1) {
        printf("Wrong number of vertices\n");
        return 1;
    }

    init_graph(&g, n);
    clear_graph(&g);

    while (1) {
        printf("Your choice: ");
        if (scanf("%d", &choice) != 1) {
            free_graph(&g);
            return 0;
        }
        skip_input_line();

        switch (choice) {
            case 1:
                printf("Enter a 'from' vertice: ");
                scanf("%d", &from);
                printf("Enter a 'to' vertice: ");
                scanf("%d", &to);
                add_edge(&g, from, to);
                break;
            case 2:
                printf("Enter a 'from' vertice: ");
                scanf("%d", &from);
                printf("Enter a 'to' vertice: ");
                scanf("%d", &to);
                remove_edge(&g, from, to);
                break;
            case 3:
                print_topological_sort_to_stream(stdout, &g);
                break;
            case 4:
                print_topological_sort_to_file(&g, "topsort.txt");
                break;
            case 5:
                print_graph_to_stream(stdout, &g);
                printf("\n");
                break;
            case 6:
                print_graph_to_file(&g, "graph.txt");
                break;
            case 7:
                free_graph(&g);
                return 0;
            default:
                printf("Wrong choice\n");
                break;
        }
    }
}
