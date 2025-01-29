#include <stdio.h>

unsigned invert(unsigned x, int p, int n) {
    // Create a mask for the n bits starting at position p
    unsigned mask = ((1U << n) - 1) << (p - n + 1);

    // XOR the mask with x to invert the targeted bits
    return x ^ mask;
}

int main() {
    unsigned x;
    int p, n;

    // Get input from the user
    printf("Enter the value of x (as an unsigned integer): ");
    scanf("%u", &x);

    printf("Enter the position p (zero-indexed): ");
    scanf("%d", &p);

    printf("Enter the number of bits to invert (n): ");
    scanf("%d", &n);

    // Call the invert function
    unsigned result = invert(x, p, n);

    // Print original and result in binary
    printf("x (original): 0b");
    for (int i = sizeof(unsigned) * 8 - 1; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
    printf("\n");

    printf("Result:       0b");
    for (int i = sizeof(unsigned) * 8 - 1; i >= 0; i--) {
        printf("%d", (result >> i) & 1);
    }
    printf("\n");

    printf("Decimal Result: %u\n", result);

    return 0;
}
