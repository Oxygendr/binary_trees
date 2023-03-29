#include <stdlib.h>

typedef struct heap_node {
    int data;
    struct heap_node *left;
    struct heap_node *right;
} heap_t;

void heapify_up(heap_t *node) {
    if (node == NULL || node->left == NULL) {
        return;
    }

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
        heapify_up(largest_node);
    }
}

heap_t *array_to_heap(int *array, size_t size) {
    if (array == NULL || size == 0) {
        return NULL;
    }

    heap_t *root = malloc(sizeof(heap_t));
    if (root == NULL) {
        return NULL;
    }

    root->data = array[0];
    root->left = NULL;
    root->right = NULL;

    for (int i = 1; i < size; i++) {
        heap_t *new_node = malloc(sizeof(heap_t));
        if (new_node == NULL) {
            return NULL;
        }

        new_node->data = array[i];
        new_node->left = NULL;
        new_node->right = NULL;

        heap_t *current_node = root;

        while (current_node->left != NULL) {
            current_node = current_node->left;
        }

        if (current_node->left == NULL) {
            current_node->left = new_node;
        } else {
            current_node->right = new_node;
        }

        heapify_up(new_node);
    }

    return root;
}

