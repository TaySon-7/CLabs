#include <stdio.h>
#include <stdio.h>
#include "func.c"

int main() {
    printf("There is the calculator, that make your minus to be unar\n");
    printf("1. Calculate a mathematical expression\n");
    printf("2. Exit\n");
    char* expression;
    int choice;
    while (1) {
        printf("Your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case 1:
                printf("Enter a mathematical expression:");
                expression = string_input();
                printf("%s\n", expression);
                stack* opn = parsing_expr_to_postfix(expression);
                if (opn == NULL) {
                    printf("Invalid expression\n");
                    break;
                }
                printf("Постфиксная форма: ");
                for (int i = 0; i <= opn->top; i++) {
                    printf("%s", (char*)opn->items[i]);
                }
                printf("\n");
                node* root = build_tree(opn);
                if (root == NULL) {
                    printf("Invalid expression\n");
                    break;
                }
                print_tree(root, 0);
                tree_to_unary_minus(root);
                printf("\n");
                print_tree(root, 0);
                printf("\n");
                printInfix(root);
                printf("\n");
                break;
            case 2:
                return 0;
            default:
                printf("Wrong choice\n");
                break;
        }
    }
}