#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int** matrix;
    int cnt_v;
    int capacity_v;
} graph;


void init_graph(graph* g, int v) {
    g->cnt_v = v;
    g->capacity_v = v;

    g->matrix = (int**)malloc(g->capacity_v * sizeof(int*));
    for (int i = 0; i < g->capacity_v; i++) {
        g->matrix[i] = (int*)malloc(g->capacity_v * sizeof(int));
    }
}

void resize_graph(graph* g, int v) {
    if (v <= g->capacity_v) {
        g->cnt_v = v;
        return;
    }

    g->matrix = (int**)realloc(g->matrix, v * sizeof(int*));

    for (int i = g->capacity_v; i < v; i++) {
        g->matrix[i] = (int*)malloc(v * sizeof(int));
    }

    for (int i = 0; i < v; i++) {
        g->matrix[i] = (int*)realloc(g->matrix[i], v * sizeof(int));

        if (i < g->capacity_v) {
            for (int j = g->capacity_v; j < v; j++) {
                g->matrix[i][j] = 0;
            }
        }
        else {
            for (int j = 0; j < v; j++) {
                g->matrix[i][j] = 0;
            }
        }
    }
    g->capacity_v = v;
    g->cnt_v = v;
}


void add_edge(graph* g, int from, int to) {
    int mx_v = (from > to) ? from : to;
    if (mx_v >= g->cnt_v) {
        resize_graph(g, mx_v + 1);
    }

    g->matrix[from][to] = 1;
}


void remove_edge(graph* g, int from, int to) {
    if (from >= 0 && from < g->cnt_v && to >= 0 && to < g->cnt_v) {
        g->matrix[from][to] = 0;
    }
}


void print_graph(graph* g) {
    printf("  ");
    for (int i = 0; i < g->cnt_v; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < g->cnt_v; i++) {
        printf("%d ", i);
        for (int j = 0; j < g->cnt_v; j++) {
            printf("%d ", g->matrix[i][j]);
        }
        printf("\n");
    }
}


void free_graph(graph* g) {
    for (int i = 0; i < g->capacity_v; i++) {
        free(g->matrix[i]);
    }
    free(g->matrix);
    g->capacity_v = 0;
    g->cnt_v = 0;
}


int topological_sort(graph* g, int* result) {
    int* in_degree = (int*)calloc(g->cnt_v, sizeof(int));
    for (int i = 0; i < g->cnt_v; i++) {
        for (int j = 0; j < g->cnt_v; j++) {
            if (g->matrix[i][j] == 1) {
                in_degree[j] += 1;
            }
        }
    }
    int* queue = (int*)malloc(g->cnt_v * sizeof(int));
    int front = 0;
    int back = 0;
    for (int i = 0; i < g->cnt_v; i++) {
        if (in_degree[i] == 0) {
            queue[back] = i;
            back += 1;
        }
    }
    int from;
    int ans_index = 0;
    while (front < back) {
        from = queue[front];
        front += 1;
        result[ans_index] = from;
        ans_index += 1;
        for (int j = 0; j < g->cnt_v; j++) {
            if (g->matrix[from][j] == 1) {
                in_degree[j] -= 1;
                if (in_degree[j] == 0) {
                    queue[back] = j;
                    back += 1;
                }
            }
        }
    }
    free(queue);
    free(in_degree);
    return ans_index == g->cnt_v ? 1 : 0;

}
