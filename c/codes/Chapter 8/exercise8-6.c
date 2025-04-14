#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom calloc function
void *my_calloc(size_t n, size_t size) {
    size_t total = n * size;

    if (n != 0 && total / n != size) {
        return NULL; // overflow
    }

    void *ptr = malloc(total);
    if (ptr == NULL) return NULL;

    memset(ptr, 0, total);
    return ptr;
}

int main() {
    int *arr = (int *)my_calloc(5, sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);
    return 0;
}

