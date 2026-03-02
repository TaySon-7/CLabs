#include <stdio.h>
#include "func.c"
#include <assert.h>

void test_adding_nodes() {
    node* root = NULL;
    root = add_node(5, root);
    assert(root->data == 5);
    root = add_node(6, root);
    root = add_node(7, root);
    assert(root->right->data == 6);
    assert(root->right->right->data == 7);
    root = add_node(0, root);
    assert(root->left->data == 0);
    free_tree(root);
}

void test_adding_similar_nodes() {
    node* root = NULL;
    root = add_node(5, root);
    root = add_node(5, root);
    assert(root->left == NULL);
    assert(root->right == NULL);
}

void test_deletion_nodes_without_balancing() {
    node* root = NULL;
    root = delete_node(root, 5);
    assert(root == NULL);
    root = add_node(5, root);
    root = add_node(6, root);
    root = add_node(7, root);
    root = add_node(0, root);
    root = delete_node(root, 0);
    assert(root->left == NULL);
    root = add_node(2, root);
    root = add_node(3, root);
    root = delete_node(root, 2);
    assert(root->left->data == 3);
    root = delete_node(root, 6);
    assert(root->right->data == 7);
    free_tree(root);
}

void test_deletion_nodes_with_balancing() {
    node* root = NULL;
    root = add_node(5, root);
    root = add_node(6, root);
    root = add_node(7, root);
    root = add_node(0, root);
    root = delete_node(root, 0);
    root = add_node(2, root);
    root = add_node(3, root);
    root = delete_node(root, 2);
    root = delete_node(root, 6);
    root = add_node(12, root);
    root = delete_node(root, 7);
    root = add_node(8, root);
    root = add_node(7, root);
    root = add_node(9, root);
    root = add_node(15, root);
    root = add_node(13, root);
    root = add_node(16, root);
    root = delete_node(root, 8);
    assert(root->right->left->data == 9);
    free_tree(root);
}

void test_depth_tree() {
    node* root = NULL;
    int result = depth(root);
    assert(result == 0);
    root = add_node(5, root);
    root = add_node(6, root);
    root = add_node(7, root);
    result = depth(root);
    assert(result == 3);
    root = add_node(4, root);
    root = add_node(3, root);
    result = depth(root);
    assert(result == 3);
    root = add_node(12, root);
    assert(depth(root) == 4);
    free_tree(root);
}

int main() {
    test_adding_nodes();
    test_adding_similar_nodes();
    test_deletion_nodes_without_balancing();
    test_deletion_nodes_with_balancing();
    test_depth_tree();
    return 0;
}