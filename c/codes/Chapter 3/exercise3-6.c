#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char s[]) {
    int i, j;
    char temp;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

void itoa(int n, char s[], int width) {
    int i = 0, sign = n;
    
    if (n < 0)
        n = -n;

    do {
        s[i++] = (n % 10) + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';

    while (i < width) // Pad with spaces if necessary
        s[i++] = ' ';

    s[i] = '\0';
    reverse(s);
}

int main() {
    char buffer[20];

    itoa(123, buffer, 6);
    printf("'%s'\n", buffer); // Should print: '   123'

    itoa(-45, buffer, 5);
    printf("'%s'\n", buffer); // Should print: '  -45'

    itoa(7890, buffer, 10);
    printf("'%s'\n", buffer); // Should print: '      7890'

    return 0;
}
