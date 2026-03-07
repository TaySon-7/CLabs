#include <stdio.h>
#include <assert.h>
#include "func.c"


void test_sort_first_order(char** correct_keys, char** correct_values, char** keys, char** values) {
    insertionSort(keys, 21, values);
    for (int i = 0; i < 21; i++) {
        assert(strcmp(correct_keys[i], keys[i]) == 0);
        assert(strcmp(correct_values[i], values[i]) == 0);
    }
}


void test_sort_second_order(char** correct_keys, char** correct_values) {
    table* t = init_table("input2.txt");
    char** keys = t->keys;
    char** values = t->values;
    int n = t->len;
    insertionSort(keys, n, values);
    for (int i = 0; i < n; i++) {
        assert(strcmp(correct_keys[i], keys[i]) == 0);
        assert(strcmp(correct_values[i], values[i]) == 0);
    }
    free(keys);
    free(values);
}


void test_sort_third_order(char** correct_keys, char** correct_values) {
    table* t = init_table("input3.txt");
    char** keys = t->keys;
    char** values = t->values;
    int n = t->len;
    insertionSort(keys, n, values);
    for (int i = 0; i < n; i++) {
        assert(strcmp(correct_keys[i], keys[i]) == 0);
        assert(strcmp(correct_values[i], values[i]) == 0);
    }
    free(keys);
    free(values);

}


void test_binary_search(char** correct_keys, char** correct_values, int n) {
    for (int i = 0; i < n; i++) {
        assert(strcmp(binarySearch(correct_keys, correct_values, n, correct_keys[i]), correct_values[i]) == 0);
    }
}


void test_binary_search_after_generation(char** correct_keys, char** correct_values) {
    table* t = init_table("input2.txt");
    char** keys = t->keys;
    char** values = t->values;
    int n = t->len;
    insertionSort(keys, n, values);
    for (int i = 0; i < n; i++) {
        assert(strcmp(binarySearch(correct_keys, correct_values, n, correct_keys[i]), correct_values[i]) == 0);
    }
    free(keys);
    free(values);
}


int main() {
    table* t = init_table("input1.txt");
    char** keys = t->keys;
    char** values = t->values;
    int n = t->len;
    char** keys1 = malloc(sizeof(char*) * n);
    char** values1 = malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        keys1[i] = (char*) malloc(MAX_SIZE_OF_LINE * sizeof(char));
        if (keys1[i] == NULL) {
            perror("malloc");
        }
        values1[i] = (char*) malloc(MAX_SIZE_OF_LINE * sizeof(char));
        if (values1[i] == NULL) {
            perror("malloc");
        }
        strcpy(keys1[i], keys[i]);
        strcpy(values1[i], values[i]);
    }
    test_sort_first_order(keys, values, keys1, values1);
    test_sort_second_order(keys, values);
    test_sort_third_order(keys, values);
    test_binary_search(keys, values, n);
    free(keys);
    free(values);
    free(keys1);
    free(values1);
    return 0;
}