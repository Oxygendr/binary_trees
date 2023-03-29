#include <stdlib.h>

typedef struct heap_node {
    int data;
    struct heap_node *left;
    struct heap_node *right;
} heap_t;

void heap_to_sorted_array_helper(heap_t *node, int *arr, int *index) {
    if (node == NULL) {
        return;
    }

    heap_to_sorted_array_helper(node->left, arr, index);
    arr[*index] = node->data;
    (*index)++;
    heap_to_sorted_array_helper(node->right, arr, index);
}

int *heap_to_sorted_array(heap_t *heap, size_t *size) {
    // Determine the size of the heap
    int heap_size = 0;
    heap_to_sorted_array_helper(heap, NULL, &heap_size);
    *size = heap_size;

    // Create an array to store the sorted elements
    int *sorted_arr = (int *) malloc(sizeof(int) * heap_size);

    // Fill the array with the sorted elements
    int index = 0;
    heap_to_sorted_array_helper(heap, sorted_arr, &index);

    return sorted_arr;
}

