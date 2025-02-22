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

void itoa(int n, char s[]) {
    int i = 0, sign = n;

    // Handle INT_MIN separately
    if (n == INT_MIN) {
        n = -(n + 1);  // Avoid overflow
        do {
            s[i++] = (n % 10) + '0';
        } while ((n /= 10) > 0);
        s[0]++;  // Adjust last digit because of the earlier +1
    } else {
        if (n < 0)
            n = -n;
        do {
            s[i++] = (n % 10) + '0';
        } while ((n /= 10) > 0);
    }

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}

int main() {
    char buffer[20];

    int num = INT_MIN;  // Testing with the largest negative number
    itoa(num, buffer);
    printf("itoa(%d) = %s\n", num, buffer);

    num = -1234;  // Regular negative number
    itoa(num, buffer);
    printf("itoa(%d) = %s\n", num, buffer);

    num = 5678;  // Positive number
    itoa(num, buffer);
    printf("itoa(%d) = %s\n", num, buffer);

    return 0;
}
