#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.c"

void generate(char**keys, char**values, int n) {
    int j;
    char*key;
    char*value;
    for (int i = n - 1; i >= 0; i--) {
        j = rand() % (i + 1);
        key = keys[i];
        value = values[i];
        keys[i] = keys[j];
        values[i] = values[j];
        keys[j] = key;
        values[j] = value;
    }
}


int main() {
    srand(time(NULL));
    table* t = init_table("input2.txt");
    char ** keys = t->keys;
    char ** values = t->values;
    int n = t->len;
    generate(keys, values, n);
    FILE* file1 = fopen("input2.txt", "w");
    fprintf(file1, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(file1, "%s\n", keys[i]);
        fprintf(file1, "%s\n", values[i]);
    }
    fclose(file1);
    free(keys);
    free(values);
    return 0;
}