#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALLOCATIONS 1000
#define MAX_SAFE_SIZE (1024 * 1024 * 100) // 100MB max

// Struct to keep track of allocated memory
typedef struct {
    void *ptr;
    size_t size;
    int is_freed;
} Allocation;

Allocation allocations[MAX_ALLOCATIONS];
int allocation_count = 0;

// Safe malloc wrapper
void *xmalloc(size_t size) {
    if (size == 0 || size > MAX_SAFE_SIZE) {
        fprintf(stderr, "xmalloc error: invalid size requested (%zu bytes)\n", size);
        return NULL;
    }

    void *ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "xmalloc error: malloc failed\n");
        return NULL;
    }

    if (allocation_count >= MAX_ALLOCATIONS) {
        fprintf(stderr, "xmalloc error: too many allocations\n");
        free(ptr);
        return NULL;
    }

    allocations[allocation_count].ptr = ptr;
    allocations[allocation_count].size = size;
    allocations[allocation_count].is_freed = 0;
    allocation_count++;

    return ptr;
}

// Safe free wrapper
void xfree(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "xfree error: NULL pointer passed\n");
        return;
    }

    for (int i = 0; i < allocation_count; i++) {
        if (allocations[i].ptr == ptr) {
            if (allocations[i].is_freed) {
                fprintf(stderr, "xfree error: pointer already freed\n");
                return;
            }

            free(ptr);
            allocations[i].is_freed = 1;
            printf("xfree: memory freed successfully\n");
            return;
        }
    }

    fprintf(stderr, "xfree error: pointer not found in allocation list\n");
}

// Test program
int main() {
    int *nums = (int *)xmalloc(5 * sizeof(int));
    if (!nums) return 1;

    for (int i = 0; i < 5; i++)
        nums[i] = i * 10;

    for (int i = 0; i < 5; i++)
        printf("nums[%d] = %d\n", i, nums[i]);

    xfree(nums);
    xfree(nums);  // Second free should produce an error

    int *bad = (int *)12345;  // Invalid pointer
    xfree(bad);               // Should produce error

    return 0;
}
