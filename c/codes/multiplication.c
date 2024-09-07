#include <stdio.h>

int main() {
    int num1, num2, result;

    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);

    result = num1 * num2;

    printf("Multiplication of %d and %d is: %d\n", num1, num2, result);

    return 0;
}