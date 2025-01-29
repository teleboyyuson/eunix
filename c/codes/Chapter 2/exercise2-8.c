#include <stdio.h>

unsigned rightrot(unsigned x, int n) {
    int num_bits = sizeof(unsigned) * 8;
    n = n % num_bits;  // Ensure n is within the number of bits

    // Perform the rotation
    unsigned right_part = x >> n;  
    unsigned left_part = (x & ((1U << n) - 1)) << (num_bits - n);

    // Debug: Print intermediate binary results
    printf("x (original): 0b");
    for (int i = num_bits - 1; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
    printf("\n");

    printf("Right Part: 0b");
    for (int i = num_bits - 1; i >= 0; i--) {
        printf("%d", (right_part >> i) & 1);
    }
    printf("\n");

    printf("Left Part:  0b");
    for (int i = num_bits - 1; i >= 0; i--) {
        printf("%d", (left_part >> i) & 1);
    }
    printf("\n");

    return right_part | left_part;
}

void print_binary(unsigned x) {
    int num_bits = sizeof(unsigned) * 8;
    for (int i = num_bits - 1; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
}

int main() {
    unsigned x;
    int n;

    printf("Enter the value of x (as an unsigned integer): ");
    scanf("%u", &x);

    printf("Enter the number of positions to rotate (n): ");
    scanf("%d", &n);

    unsigned result = rightrot(x, n);

    // Print original and result in binary
    printf("x (original): 0b");
    print_binary(x);
    printf("\n");

    printf("Result:       0b");
    print_binary(result);
    printf("\n");

    printf("Decimal Result: %u\n", result);

    return 0;
}


