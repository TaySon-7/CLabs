#include <stdio.h>
#include <stdlib.h>
#include <_string.h>

int max(const int a, const int b) {
    return a > b ? a : b;
}


typedef struct Node {
    double data;
    char* key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;


int height(Node* node) {
    if (node == NULL) return 0;
    return node->height;
}

Node* right_turn(Node* node) {
    Node* left = node->left;
    Node* left_right = left->right;
    left->right = node;
    node->left = left_right;

    node->height = 1 + max(height(node->left), height(node->right));
    left->height = 1 + max(height(left->left), height(left->right));
    return left;
}


Node* left_turn(Node* node) {
    Node* right = node->right;
    Node* right_left = right->left;
    right->left = node;
    node->right = right_left;

    node->height = 1 + max(height(node->left), height(node->right));
    right->height = 1 + max(height(right->left), height(right->right));
    return right;
}


Node* add_node(Node* root, char*key, double data) {
    if (root == NULL) {
        root = (Node*)malloc(sizeof(Node));
        root->data = data;
        root->key = (char*)malloc((strlen(key) + 1) * sizeof(char));
        strcpy(root->key, key);
        root->left = NULL;
        root->right = NULL;
        root->height = 1;
        return root;
    }
    if (strcmp(key, root->key) < 0) {
        root->left = add_node(root->left, key, data);
    }
    else if (strcmp(key, root->key) > 0) {
        root->right = add_node(root->right, key, data);
    }
    else {
        root->data = data;
        return root;
    }
    root->height = 1 + max(height(root->left), height(root->right));

    const int balance = height(root->left) - height(root->right);

    if (balance > 1 && strcmp(key, root->left->key) < 0) {
        return right_turn(root);
    }
    if (balance > 1 && strcmp(key, root->left->key) > 0) {
        root->left = left_turn(root->left);
        return right_turn(root);
    }
    if (balance < -1 && strcmp(key, root->right->key) < 0) {
        root->right = right_turn(root->right);
        return left_turn(root);
    }
    if (balance < -1 && strcmp(key, root->right->key) > 0) {
        return left_turn(root);
    }
    return root;
}


Node* delete_node(Node* root, char*key) {
    if (root == NULL) {
        return NULL;
    }
    if (strcmp(key, root->key) < 0) {
        root->left = delete_node(root->left, key);
    }
    else if (strcmp(key, root->key) > 0) {
        root->right = delete_node(root->right, key);
    }
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root->key);
            free(root);
            return NULL;
        }
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root->key);
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            Node* temp = root->left;
            free(root->key);
            free(root);
            return temp;
        }
        Node* temp = root->left;
        while (temp->right != NULL) {
            temp = temp->right;
        }
        free(root->key);
        root->key = (char*)malloc((strlen(temp->key) + 1) * sizeof(char));
        strcpy(root->key, temp->key);
        root->data = temp->data;
        root->left = delete_node(root->left, temp->key);
    }

    root->height = 1 + max(height(root->left), height(root->right));
    const int balance = height(root->left) - height(root->right);
    if (balance > 1 && height(root->left->left) >= height(root->left->right)) {
        return right_turn(root);
    }
    if (balance > 1 && height(root->left->left) < height(root->left->right)) {
        root->left = left_turn(root->left);
        return right_turn(root);
    }
    if (balance < -1 && height(root->right->left) <= height(root->right->right)) {
        return left_turn(root);
    }
    if (balance < -1 && height(root->right->left) > height(root->right->right)) {
        root->right = right_turn(root->right);
        return left_turn(root);
    }

    return root;
}


void free_tree(Node* root) {
    if (root == NULL) {
        return;;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root->key);
    free(root);
}


void print_tree(Node* root, int level) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf(" ");
    }
    printf("%s %.5lf\n", root->key, root->data);
    print_tree(root->left, level + 1);
    print_tree(root->right, level + 1);
}


double search(Node* root, char*key) {
    if (root == NULL) {
        printf("%s is empty\n", key);
        return -404;;
    }
    if (strcmp(key, root->key) < 0) {
        return search(root->left, key);
    }
    if (strcmp(key, root->key) > 0) {
        return search(root->right, key);
    }
    return root->data;
}

