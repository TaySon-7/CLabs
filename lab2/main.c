#include <stdio.h>
#include <time.h>
#include "func.c"

int main() {
    table* t = init_table("input2.txt");
    char ** keys = t->keys;
    char ** values = t->values;
    int n = t->len;
    printf("No sorted table:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", keys[i]);
        printf("%s\n", values[i]);
    }
    printf("\n");
    insertionSort(keys, n, values);
    printf("Sorted table:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", keys[i]);
        printf("%s\n", values[i]);
    }
    printf("\n");
    printf("There is the automatically sorted table from Pushkin's poetry\n");
    printf("1. You can find value by entering your key\n");
    printf("2. Exit\n");
    int choice;
    char* key;
    char* value;
    key = (char*) malloc(MAX_SIZE_OF_LINE * sizeof(char));
    if (key == NULL) {
        perror("malloc");
    }
    while (1) {
        printf("Your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case 1:
                printf("Enter key:");
                if (scanf("%s", key) == 1) {
                    value = binarySearch(keys, values, n, key);
                    printf("%s\n", value);
                }
                else {
                    printf("Invalid input!\n");
                }
                while (getchar() != '\n');
                break;
            case 2:
                free(keys);
                free(values);
                free(key);
                return 0;
            default:
                printf("Wrong choice\n");
                break;
        }
    }
}