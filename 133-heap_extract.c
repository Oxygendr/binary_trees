#include <stdlib.h>

typedef struct heap_node {
    int data;
    struct heap_node *left;
    struct heap_node *right;
} heap_t;

int get_height(heap_t *node) {
    if (node == NULL) {
        return 0;
    }
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

heap_t *get_last_node(heap_t *node, int height, int current_height) {
    if (node == NULL) {
        return NULL;
    }

    if (current_height == height) {
        return node;
    }

    heap_t *left_node = get_last_node(node->left, height, current_height + 1);
    heap_t *right_node = get_last_node(node->right, height, current_height + 1);

    if (right_node != NULL) {
        return right_node;
    }

    return left_node;
}

void heapify_down(heap_t *node) {
    heap_t *largest_node = node;

    if (node->left != NULL && node->left->data > largest_node->data) {
        largest_node = node->left;
    }

    if (node->right != NULL && node->right->data > largest_node->data) {
        largest_node = node->right;
    }

    if (largest_node != node) {
        int temp = node->data;
        node->data = largest_node->data;
        largest_node->data = temp;
        heapify_down(largest_node);
    }
}

int heap_extract(heap_t **root) {
    if (*root == NULL) {
        return 0;
    }

    int root_data = (*root)->data;
    heap_t *last_node = get_last_node(*root, get_height(*root), 1);

    if (last_node == *root) {
        free(*root);
        *root = NULL;
        return root_data;
    }

    (*root)->data = last_node->data;

    heap_t *parent_of_last_node = get_last_node(*root, get_height(*root) - 1, 1);

    if (parent_of_last_node->left == last_node) {
        parent_of_last_node->left = NULL;
    } else {
        parent_of_last_node->right = NULL;
    }

    free(last_node);

    heapify_down(*root);

    return root_data;
}

