#ifndef FUNC_H
#define FUNC_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int** matrix;
    int cnt_v;
    int capacity_v;
} graph;

void init_graph(graph* g, int v);
void resize_graph(graph* g, int v);
void add_edge(graph* g, int from, int to);
void remove_edge(graph* g, int from, int to);
void print_graph(graph* g);
void free_graph(graph* g);
int topological_sort(graph* g, int* result);

#ifdef __cplusplus
}
#endif

#endif
