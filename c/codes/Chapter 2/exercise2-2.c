#include <stdio.h>

int main() {
    int i = 0; // Initialization
    while (1) { // Infinite loop
        if (i >= 10) { // First condition: i < 10
            break;
        }
        if (i % 2 != 0) { // Second condition: i % 2 == 0
            break;
        }

        // Loop body
        printf("%d\n", i);

        i++; // Increment
    }
    return 0;
}
