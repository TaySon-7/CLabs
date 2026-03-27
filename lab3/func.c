#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_OF_INPUT 100

typedef struct {
    void** items;
    int top;
    int capacity;
} stack;


stack* init_stack() {
    stack* st = (stack*)malloc(sizeof(stack));
    if (st == NULL) {
        return NULL;
    }
    st->top = -1;
    st->capacity = MAX_SIZE_OF_INPUT;
    st->items = (void**)malloc(st->capacity * sizeof(void*));
    if (st->items == NULL) {
        printf("Not enough memory for stack\n");
    }
    return st;
}

void push_stack(void* item, stack* st) {
    if (st->top < st->capacity - 1) {
        st->top++;
        st->items[st->top] = item;
    }
    else {
        st->capacity = st->capacity * 2;
        st->items = realloc(st->items, st->capacity * sizeof(void*));
        if (st->items == NULL) {
            printf("Out of memory\n");
        }
        st->top++;
        st->items[st->top] = item;
    }
}

char* pop_stack(stack* st) {
    if (st->top == -1) {
        return NULL;
    }
    char* item = st->items[st->top];
    st->top--;
    return item;
}

char* peek_stack(stack* st) {
    if (st->top == -1) {
        return NULL;
    }
    return st->items[st->top];
}

int priority(const char s) {
    if (s == '+' || s == '-') {
        return 1;
    }
    if (s == '*' || s == '/') {
        return 2;
    }
    if (s == '^') {
        return 3;
    }
    if (s == '~') {
        return 4;
    }
    return 0;
}

int is_oper(const char s) {
    if (s == '+' || s == '-' || s == '*' || s == '/' || s == '^' || s == '~') {
        return 1;
    }
    return 0;
}

char* string_input() {
    long long capacity = MAX_SIZE_OF_INPUT;
    long long length = 0;
    char* str = (char*)malloc(sizeof(char) * capacity);
    if (str == NULL) {
        printf("Memory allocation error");
        return NULL;
    }
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        str[length] = c;
        length++;
        if (length >= capacity) {
            capacity *= 2;
            char* temp = (char*)realloc(str, sizeof(char) * capacity);
            if (temp == NULL) {
                printf("Memory allocation error");
                free(str);
                return NULL;
            }
            str = temp;
        }
    }
    str[length] = '\0';
    return str;
}

int is_unary_oper(const char s) {
    return s == '~';
}


stack* parsing_expr_to_postfix(const char* expr) {
    stack* st_out = init_stack();
    stack* st_oper = init_stack();
    int var_checksum = 0;
    int operand_checksum = 0;
    const unsigned int len = strlen(expr);
    unsigned int i = 0;
    int unary_expected = 1;

    while (i < len) {
        if (expr[i] == ' ') {
            i++;
            continue;
        }

        if (isdigit(expr[i])) {
            int capacity = 20;
            char* number = (char*)malloc((capacity + 1) * sizeof(char));
            int k_n = 0;
            while (i < len && isdigit(expr[i])) {
                number[k_n] = expr[i];
                k_n++;
                i++;
                if (k_n >= capacity && i < len && isdigit(expr[i])) {
                    capacity *= 2;
                    char* tmp = (char*)realloc(number, (capacity + 1) * sizeof(char));
                    if (tmp == NULL) {
                        free(number);
                        return NULL;
                    }
                    number = tmp;
                }
            }
            number[k_n] = '\0';
            push_stack(number, st_out);
            unary_expected = 0;
            var_checksum += 1;
        }
        else if (isalpha(expr[i])) {
            char* op = (char*)malloc(2 * sizeof(char));
            op[0] = expr[i];
            op[1] = '\0';
            var_checksum += 1;
            push_stack(op, st_out);
            i++;
            unary_expected = 0;
        }
        else if (is_oper(expr[i]) || expr[i] == '~') {
            if (expr[i] == '-' && unary_expected) {
                char* op = (char*)malloc(2 * sizeof(char));
                op[0] = '~';
                op[1] = '\0';
                push_stack(op, st_oper);
                unary_expected = 1;
                i++;
                continue;
            }
            char current_op = expr[i];

            while (st_oper->top != -1) {
                char* top_op = peek_stack(st_oper);
                if (top_op[0] == '(') break;

                int top_priority = priority(top_op[0]);
                int curr_priority = priority(current_op);
                if (top_priority >= curr_priority) {
                    char* op = pop_stack(st_oper);
                    push_stack(op, st_out);
                } else {
                    break;
                }
            }
            char* op = (char*)malloc(2 * sizeof(char));
            op[0] = current_op;
            op[1] = '\0';
            operand_checksum += 1;
            push_stack(op, st_oper);
            i++;
            unary_expected = 1;
        }
        else if (expr[i] == '(') {
            char* op = (char*)malloc(2 * sizeof(char));
            op[0] = '(';
            op[1] = '\0';
            push_stack(op, st_oper);
            i++;
            unary_expected = 1;
        }
        else if (expr[i] == ')') {
            int flag = 1;
            while (st_oper->top != -1 && peek_stack(st_oper)[0] != '(') {
                char* op = pop_stack(st_oper);
                push_stack(op, st_out);
            }
            if (st_oper->top != -1 && peek_stack(st_oper)[0] == '(') {
                pop_stack(st_oper);
                flag = 0;
            }
            if (flag) {
                printf("bracket error )");
                return NULL;
            }
            i++;
            unary_expected = 0;
        }
        else {
            printf("unexpected character '%c'\n", expr[i]);
            return NULL;
        }
    }

    while (st_oper->top != -1) {
        char* op = pop_stack(st_oper);
        if (op[0] != '(') {
            push_stack(op, st_out);
        }
        else {
            printf("Unexpected character '%c'\n", op[0]);
            return NULL;
        }
    }
    if (var_checksum != operand_checksum + 1){
    printf("Wrong checksum\n");
        return NULL;
}
    free(st_oper->items);
    free(st_oper);

    return st_out;
}

typedef struct node {
    char* value;
    struct node* left;
    struct node* right;
    int is_unary;
} node;

node* create_node(const char* value) {
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        printf("Out of memory\n");
        return NULL;
    }
    new_node->value = (char*)malloc(strlen(value) + 1);
    strcpy(new_node->value, value);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->is_unary = 0;
    return new_node;
}


node* build_tree(stack* st_post) {
    stack* st = init_stack();
    for (int i = 0; i <= st_post->top; i++) {
        char* token = st_post->items[i];
        if (token[0] == '~') {
            node* nd = create_node("-");
            nd->is_unary = 1;
            nd->right = (node*)pop_stack(st);
            nd->left = NULL;
            push_stack(nd, st);
        }
        else if (is_oper(token[0])) {
            node* nd = create_node(token);
            nd->right = (node*)pop_stack(st);
            nd->left = (node*)pop_stack(st);
            push_stack(nd, st);
        }
        else {
            node* nd = create_node(token);
            push_stack(nd, st);
        }
    }
    node* root = (node*)pop_stack(st);
    if (st->top != -1) {
        printf("Error: some operands are not used");
        return NULL;
    }
    free(st->items);
    free(st);
    return root;
}


void print_tree(node* root, int level) {
    if (!root) return;

    for (int i = 0; i < level; i++) printf("  ");
        printf("%s\n", root->value);
        print_tree(root->right, level + 1);
        print_tree(root->left, level + 1);

}


void tree_to_unary_minus(node * root) {
    if (root == NULL) return;

    tree_to_unary_minus(root->left);
    tree_to_unary_minus(root->right);

    if (root->is_unary == 0 && root->value[0] == '-') {
        node* um = create_node("-");
        um->is_unary = 1;
        um->left = NULL;
        um->right = root->right;
        free(root->value);
        root->value = (char*)malloc(2 * sizeof(char));
        strcpy(root->value, "+");
        root->right = um;
    }
}


void printInfix(node *node) {
    if  (!node) return;

    if (is_oper(node->value[0])) {
        printf("(");
    }

    if (node->is_unary) {
        printf("-");
    } else {
        printInfix(node->left);
    }

    if (isdigit(node->value[0])) {
        printf("%s", node->value);
    } else if (isalpha(node->value[0])) {
        printf("%s", node->value);
    } else {
        if (is_oper(node->value[0]) && node->is_unary == 0) {
            printf("%c", node->value[0]);
        }
    }

    printInfix(node->right);

    if (is_oper(node->value[0])) {
        printf(")");
    }
}
