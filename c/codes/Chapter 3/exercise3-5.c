#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]) {
    int i, j;
    char temp;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

void itob(int n, char s[], int b) {
    int i = 0, sign = n;
    unsigned int num = (sign < 0) ? -n : n;  // Handle negative numbers

    do {
        int digit = num % b;
        s[i++] = (digit < 10) ? digit + '0' : digit - 10 + 'A'; // Convert to appropriate char
    } while ((num /= b) > 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

int main() {
    char buffer[33];

    itob(255, buffer, 16);
    printf("255 in base 16: %s\n", buffer); // Should print "FF"

    itob(-255, buffer, 16);
    printf("-255 in base 16: %s\n", buffer); // Should print "-FF"

    itob(255, buffer, 2);
    printf("255 in base 2: %s\n", buffer); // Should print "11111111"

    itob(-255, buffer, 2);
    printf("-255 in base 2: %s\n", buffer); // Should print "-11111111"

    itob(255, buffer, 8);
    printf("255 in base 8: %s\n", buffer); // Should print "377"

    return 0;
}
