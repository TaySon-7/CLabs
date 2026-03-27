#include <assert.h>
#include "func.c"
#include <assert.h>


void test_parse_to_opn_string() {
    char* input = "1 + 5 * 100 + 1000";
    stack* str = parsing_expr_to_postfix(input);
    char result[100] = "";
    for (int i = 0; i <= str->top; i++) {
        strcat(result, str->items[i]);
        strcat(result, " ");
    }
    printf("%s\n", result);
    assert(strcmp(result, "1 5 100 * + 1000 + ") == 0 && "ошибка на проверке парсинга в опн");
}


void test_brackets_errors() {
    char* input1 = "(1 + 5) * 100) + 1000";
    stack* st1 = parsing_expr_to_postfix(input1);
    printf("\n");
    assert(st1 == NULL);
    char* input2 = "-(5 * 10) * (10 / 1";
    stack* st2 = parsing_expr_to_postfix(input2);
    printf("\n");
    assert(st2 == NULL);
    char* input3 = "(1 + 5)( * 100 + 1000";
    stack* st3 = parsing_expr_to_postfix(input3);
    assert(st3 == NULL);
}


void test_different_operands() {
    char* input1 = "(1 + 5 % 100) + 1000";
    stack* st1 = parsing_expr_to_postfix(input1);
    printf("\n");
    assert(st1 == NULL);
    char* input2 = "18 + 4  & 10";
    stack* st2 = parsing_expr_to_postfix(input2);
    printf("\n");
    assert(st2 == NULL);
    char* input3 = "18 + 4  10";
    stack* st3 = parsing_expr_to_postfix(input3);
    assert(st3 == NULL);
    char* input4 = "18 + 4 + 10 100";
    stack* st4 = parsing_expr_to_postfix(input4);
    assert(st4 == NULL);
}

int tree_check_unary(node* root, int flag) {
    if (root == NULL) return 0;
    int flag1 = tree_check_unary(root->left, flag);
    int flag2 = tree_check_unary(root->right, flag);
    if (root->is_unary) {
        return flag1 + flag2 + 1;
    }
    if (strcmp(root->value, "-") == 0) {
        return flag1 + flag2 + 2;
    }
    return flag1 + flag2;
}

void test_build_tree() {
    char* input1 = "-5 * 10 - 1";
    stack* st1 = parsing_expr_to_postfix(input1);
    node * root = build_tree(st1);
    int flag = tree_check_unary(root, 0);
    assert(flag == 3 && "ошибка при переводе в дерево");
    char* input2 = "5 * 3 - 10 * (-5 - 10)";
    stack* st2 = parsing_expr_to_postfix(input2);
    node * root1 = build_tree(st2);
    int flag1 = tree_check_unary(root1, 0);
    assert(flag1 == 5 && "ошибка при переводе в дерево");
}


void test_rebuild_tree() {
    char* input1 = "-5 * 10 - 1";
    stack* st1 = parsing_expr_to_postfix(input1);
    node * root = build_tree(st1);
    tree_to_unary_minus(root);
    int flag = tree_check_unary(root, 0);
    assert(flag == 2);
    char* input2 = "5 * 3 - 10 * (-5 - 10)";
    stack* st2 = parsing_expr_to_postfix(input2);
    node * root1 = build_tree(st2);
    tree_to_unary_minus(root1);
    int flag1 = tree_check_unary(root1, 0);
    assert(flag1 == 3);
}


int main() {
    test_parse_to_opn_string();
    test_brackets_errors();
    test_different_operands();
    test_build_tree();
    test_rebuild_tree();
    printf("All tests passed\n");
    return 0;
}