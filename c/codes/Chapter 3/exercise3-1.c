#include <stdio.h>
#include <time.h>

int binary_search(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low < high) {
        int mid = (low + high) / 2;
        if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return (arr[low] == target) ? low : -1;
}

int main() {
    int arr[100000];
    for (int i = 0; i < 100000; i++) {
        arr[i] = i;
    }

    int target = 67890;

    clock_t start = clock();
    int result = binary_search(arr, 100000, target);
    clock_t end = clock();

    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found.\n");
    }

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
