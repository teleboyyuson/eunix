#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    // Step 1: Extract the rightmost n bits of y
    unsigned mask_y = y & ((1U << n) - 1);

    // Step 2: Shift these bits to align with position p in x
    unsigned y_bits = mask_y << (p - n + 1);

    // Step 3: Create a mask to clear n bits at position p in x
    unsigned mask_x = ~(((1U << n) - 1) << (p - n + 1));

    // Step 4: Combine modified x with the new bits from y
    return (x & mask_x) | y_bits;
}

int main() {
    unsigned x = 0b10101010; // Example input x (170 in decimal)
    unsigned y = 0b11001100; // Example input y (204 in decimal)
    int p = 5;               // Position p (zero-indexed)
    int n = 3;               // Number of bits n

    unsigned result = setbits(x, p, n, y);

    printf("x (original): 0b10101010\n");
    printf("y (original): 0b11001100\n");
    printf("Result:       0b");
    for (int i = sizeof(unsigned) * 8 - 1; i >= 0; i--) {
        printf("%d", (result >> i) & 1);
    }
    printf("\nDecimal Result: %u\n", result);

    return 0;
}
