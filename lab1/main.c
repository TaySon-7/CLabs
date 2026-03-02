#include <stdio.h>
#include "func.c"

int main(){
    int choice;
    int data;
    int c;
    node* root = NULL;
    printf("Hello, It is binary tree!\n");
    printf("You have this actions to build your tree and check its depth:\n");
    printf("1. Add new node, at first you don't have nodes in your tree\n");
    printf("2. print your tree on screen\n");
    printf("3. delete node with data\n");
    printf("4. depth of your tree\n");
    printf("5. exit\n");
    while (1) {
        printf("Your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter data:");
                if (scanf("%d", &data) == 1) {
                    printf("Adding: %d\n", data);
                }
                while (getchar() != '\n');
                break;
            case 2:
                print_tree(root, 0);
                printf("\n");
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                root = delete_node(root, data);
                break;
            case 4:
                printf("%d\n", depth(root));
                break;
            case 5:
                free_tree(root);
                return 0;
            default:
                printf("Wrong choice\n");
                break;
        }
    }
}