#include <stdio.h>
#include <stdlib.h>

void itoa_recursive(int n, char s[], int index);

void itoa(int n, char s[]) {
    if (n < 0) { 
        s[0] = '-'; 
        n = -n;  // Convert to positive
        itoa_recursive(n, s, 1);
    } else {
        itoa_recursive(n, s, 0);
    }
}

void itoa_recursive(int n, char s[], int index) {
    if (n / 10)  // Recursively process remaining digits
        itoa_recursive(n / 10, s, index);
    
    s[index] = (n % 10) + '0';  // Convert last digit to character
    s[index + 1] = '\0';  // Null-terminate string
}

int main() {
    char str[20];

    itoa(12345, str);
    printf("itoa(12345) = %s\n", str);

    itoa(-9876, str);
    printf("itoa(-9876) = %s\n", str);

    return 0;
}
