#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_OF_LINE 256

typedef struct {
    char** keys;
    char** values;
    int len;
} table;

table* init_table(char* filename) {
    table* t = (table*) malloc(sizeof(table));
    int len;
    FILE* file = fopen(filename, "r");
    char* str;
    str = malloc(sizeof(char) * MAX_SIZE_OF_LINE);
    fgets(str, MAX_SIZE_OF_LINE, file);
    len = strlen(str);
    if (str[len - 1] == '\n') str[len - 1] = '\0';
    int n = atoi(str);
    free(str);
    char** keys = (char**) malloc(n * sizeof(char*));
    if (keys == NULL) {
        perror("malloc");
    }
    char** values = (char**) malloc(n * sizeof(char*));
    if (values == NULL) {
        perror("malloc");
    }
    for (int i = 0; i < n; i++){
        keys[i] = (char*) malloc(MAX_SIZE_OF_LINE * sizeof(char));
        if (keys[i] == NULL) {
            perror("malloc");
        }
        values[i] = (char*) malloc(MAX_SIZE_OF_LINE * sizeof(char));
        if (values[i] == NULL) {
            perror("malloc");
        }
        if (fgets(keys[i], MAX_SIZE_OF_LINE, file) == NULL) break;
        len = strlen(keys[i]);
        if (keys[i][len - 1] == '\n') keys[i][len - 1] = '\0';
        if (fgets(values[i], MAX_SIZE_OF_LINE, file) == NULL) break;
        len = strlen(values[i]);
        if (values[i][len - 1] == '\n') values[i][len - 1] = '\0';
    }
    fclose(file);
    t->keys = keys;
    t->values = values;
    t->len = n;
    return t;
}


void insertionSort(char** arr, int n, char** brr) {
    int i, j;
    char* key;
    char* value;
    for (i = 1; i < n; i++) {
        key = arr[i];
        value = brr[i];
        j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            brr[j + 1] = brr[j];

            j = j - 1;
        }
        arr[j + 1] = key;
        brr[j + 1] = value;
    }
}


char* binarySearch(char** arr, char**brr, int n, char* key) {
    int low = 0;
    int high = n - 1;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        int cmp = strcmp(arr[mid], key);
        if (cmp == 0) {
            return brr[mid];
        }
        if (cmp > 0) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    printf("Введён неверный ключ");
    return NULL;
}



