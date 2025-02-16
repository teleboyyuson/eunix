#include <stdio.h>

/* Faster bitcount using x &= (x - 1) trick */
int bitcount(unsigned int x) {
    int count = 0;
    while (x) {
        x &= (x - 1); // deletes the rightmost 1-bit
        count++;
    }
    return count;
}

int main() {
    unsigned int x;
    printf("Enter a number: ");
    scanf("%u", &x);

    int count = bitcount(x);
    printf("Number of 1 bits in %u: %d\n", x, count);

    return 0;
}
