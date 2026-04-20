#include <assert.h>
#include "func.c"

int check_balance(Node* root) {
    if (root == NULL) {
        return 1;
    }
    int balance = height(root->left) - height(root->right);
    if (balance > 1 || balance < -1) {
        return 0;
    }
    int l = check_balance(root->left);
    int r = check_balance(root->right);
    if (l + r == 2) {
        return 1;
    }
    return 0;
}


void test_add_node_right_rotate() {
    Node* root = NULL;
    root = add_node(root, "aaaaa", 10.5);
    root = add_node(root, "aaaa", 11.5);
    root = add_node(root, "aaa", 12.5);
    assert(root->right->data == 10.5);
    assert(check_balance(root) == 1);
}


void test_add_node_left_rotate() {
    Node* root = NULL;
    root = add_node(root, "aa", 10.5);
    root = add_node(root, "aaa", 11.5);
    root = add_node(root, "aaaa", 12.5);
    assert(root->left->data == 10.5);
    assert(check_balance(root) == 1);
}


void test_add_node_right_left_rotate() {
    Node* root = NULL;
    root = add_node(root, "a", 10.5);
    root = add_node(root, "aaa", 11.5);
    root = add_node(root, "aa", 12.5);
    assert(strcmp(root->left->key, "a") == 0);
    assert(check_balance(root) == 1);
}


void test_add_node_left_right_rotate() {
    Node* root = NULL;
    root = add_node(root, "aaaa", 10.5);
    root = add_node(root, "aa", 11.5);
    root = add_node(root, "aaa", 12.5);
    assert(strcmp(root->right->key, "aaaa") == 0);
    assert(check_balance(root) == 1);
}


void test_del_node_balanced() {
    Node* root = NULL;
    root = add_node(root, "aaaa", 10.5);
    root = add_node(root, "aaa", 11.5);
    root = add_node(root, "aaaaa", 12.5);
    root = add_node(root, "aaaaaa", 13.5);
    root = delete_node(root, "aaaa");
    assert(check_balance(root) == 1);
    root = add_node(root, "aaaa", 10.5);
    assert(strcmp(root->key, "aaaaa") == 0);
    Node* root1 = NULL;
    root1 = add_node(root1, "aaa", 10.5);
    root1 = add_node(root1, "aa", 11.5);
    root1 = add_node(root1, "aaaaa", 12.5);
    root1 = add_node(root1, "aaaa", 13.5);
    root1 = delete_node(root1, "aaa");
    assert(check_balance(root1) == 1);
}


void test_tree_many_values() {
    Node* root = NULL;
    root = add_node(root, "apple", 10.5);
    root = add_node(root, "banana", 20.3);
    root = add_node(root, "cherry", 15.7);
    root = add_node(root, "date", 8.2);
    root = add_node(root, "elderberry", 25.9);
    root = add_node(root, "fig", 12.4);
    root = add_node(root, "grape", 18.6);
    root = add_node(root, "honeydew", 5.1);
    root = add_node(root, "kiwi", 30.8);
    root = add_node(root, "lemon", 3.7);
    root = add_node(root, "mango", 22.0);
    root = add_node(root, "nectarine", 14.3);
    root = add_node(root, "orange", 9.9);
    root = add_node(root, "papaya", 27.5);
    root = add_node(root, "quince", 11.2);
    root = add_node(root, "raspberry", 16.8);
    root = add_node(root, "strawberry", 7.4);
    root = add_node(root, "tangerine", 19.1);
    root = add_node(root, "watermelon", 35.0);
    root = add_node(root, "yuzu", 13.6);
    assert(check_balance(root) == 1);
    root = delete_node(root, "banana");
    assert(check_balance(root) == 1);
    root = delete_node(root, "cherry");
    assert(check_balance(root) == 1);
}

int main() {
    test_add_node_right_rotate();
    test_add_node_left_rotate();
    test_add_node_right_left_rotate();
    test_add_node_left_right_rotate();
    test_del_node_balanced();
    test_tree_many_values();
    printf("All tests passed\n");
}