#include <stdio.h>

int main()
{
    //Display variables
    int num1, num2, result;
    //Request user input
    printf("Basic Multiplication\n\n"); 
    printf("Enter the first integer: ");
    scanf("%d", &num1);
    printf("Enter the second integer: ");
    scanf("%d", &num2);
    //Display result
    result = num1 * num2;

    printf("The product of %d and %d is: %d\n", num1, num2, result);

    return 0;
}
