#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"

int main(void) {
    const int sizes[] = {100, 500, 1000, 2000, 4000};
    const int repeats[] = {100};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);

    printf("| Vertices | Time per op (ms) |\n");

    for (int t = 0; t < num_tests; t++) {
        int n = sizes[t];

        graph g;
        init_graph(&g, n);
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < i + 9 && j < n; j++) {
                add_edge(&g, i, j);
            }
        }

        int* result = malloc(n * sizeof(int));
        if (!result) {
            printf("| %8d | error |\n", n);
            free_graph(&g);
            continue;
        }

        topological_sort(&g, result);


        for (int rp = 0; rp < 1; rp++) {
            int rep = repeats[rp];

            clock_t start = clock();
            for (int r = 0; r < rep; r++) {
                topological_sort(&g, result);
            }
            clock_t end = clock();

            double ms = (double)(end - start) / CLOCKS_PER_SEC * 1000.0 / rep;
            printf("| %8d | %15.3f      |\n", n, ms);
        }
        free(result);
        free_graph(&g);
    }

    return 0;
}