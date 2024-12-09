#include <stdio.h>

int main() {
    int n, i;
    float sum = 0.0;

    // Ask the user for the number of elements
    printf("Enter the number of elements (up to 100): ");
    scanf("%d", &n);

    // Validate size
    if (n <= 0 || n > 100) {
        printf("Invalid size! Please enter a number between 1 and 100.\n");
        return 1;
    }

    int numbers[n];  // Declare the array

    // Input the elements
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &numbers[i]);
        sum += numbers[i];  // Add to the sum
    }

    // Calculate the average
    float average = sum / n;

    // Find the largest element
    int max = numbers[0];
    for (i = 1; i < n; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    // Output the results
    printf("\nResults:\n");
    printf("Average: %.2f\n", average);
    printf("Largest number: %d\n", max);

    return 0;
}
