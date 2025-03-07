#include <stdio.h>

// Macro to swap two variables of type t
#define swap(t, x, y) do { t temp = x; x = y; y = temp; } while (0)

int main() {
    int a = 5, b = 10;
    double x = 3.14, y = 2.71;
    char c1 = 'A', c2 = 'B';

    printf("Before swapping: a = %d, b = %d\n", a, b);
    swap(int, a, b);
    printf("After swapping:  a = %d, b = %d\n", a, b);

    printf("Before swapping: x = %.2f, y = %.2f\n", x, y);
    swap(double, x, y);
    printf("After swapping:  x = %.2f, y = %.2f\n", x, y);

    printf("Before swapping: c1 = %c, c2 = %c\n", c1, c2);
    swap(char, c1, c2);
    printf("After swapping:  c1 = %c, c2 = %c\n", c1, c2);

    return 0;
}
