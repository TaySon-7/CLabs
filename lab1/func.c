#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
}typedef node;

node* add_node(int data, node* root) {
    if (root == NULL) {
        node* temp = (node*)malloc(sizeof(node));
        if (temp == NULL) {
            printf("Memory allocation error");
            exit(1);
        }
        temp->data = data;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    if (data < root->data) {
        root->left = add_node(data, root->left);
    }
    else if (data > root->data) {
        root->right = add_node(data, root->right);
    }
    else {
        printf("В упорядоченном двоичном дереве не могут хранится дубликаты\n");
    }
    return root;
}

node* delete_node(node* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = delete_node(root->left, data);
    }
    else if (data > root->data) {
        root->right = delete_node(root->right, data);
    }
    else {
        if (root->left == NULL) {
            node* temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL) {
            node* temp = root;
            root = root->left;
            free(temp);
        }
        else {
            node* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data);
        }
    }
    return root;
}
void print_tree(node* root, int level) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);
    print_tree(root->left, level + 1);
    print_tree(root->right, level + 1);
}

void free_tree(node* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int depth(node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + depth(root->left) + depth(root->right);
}


