#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// getline: read a line into s, return length
int getline_ptr(char *s, int lim) {
    char *p = s;
    int c;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        *p++ = c;
    }
    if (c == '\n') {
        *p++ = c;
    }
    *p = '\0';
    return p - s;
}

// atoi: convert string to integer
int atoi_ptr(const char *s) {
    int n = 0;
    while (*s >= '0' && *s <= '9') {
        n = 10 * n + (*s - '0');
        s++;
    }
    return n;
}

// itoa: convert integer to string
void itoa_ptr(int n, char *s) {
    char *p = s;
    int sign;

    if ((sign = n) < 0) {
        n = -n;
    }

    do {
        *p++ = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) {
        *p++ = '-';
    }
    *p = '\0';

    // Reverse the string
    for (char *start = s, *end = p - 1; start < end; start++, end--) {
        char temp = *start;
        *start = *end;
        *end = temp;
    }
}

// reverse: reverse string s in place
void reverse_ptr(char *s) {
    char *end = s + strlen(s) - 1;
    while (s < end) {
        char temp = *s;
        *s++ = *end;
        *end-- = temp;
    }
}

// strindex: return index of t in s, -1 if none
int strindex_ptr(const char *s, const char *t) {
    const char *p, *q, *r;

    for (p = s; *p != '\0'; p++) {
        for (q = p, r = t; *r != '\0' && *q == *r; q++, r++)
            ;
        if (*r == '\0') {
            return p - s;
        }
    }
    return -1;
}

int main() {
    char line[100];
    int len = getline_ptr(line, 100);
    printf("Line: %sLength: %d\n", line, len);

    printf("atoi_ptr(\"12345\"): %d\n", atoi_ptr("12345"));

    char s[20];
    itoa_ptr(-123, s);
    printf("itoa_ptr(-123): %s\n", s);

    char str[] = "Hello";
    reverse_ptr(str);
    printf("Reversed: %s\n", str);

    printf("strindex_ptr(\"hello world\", \"world\"): %d\n", strindex_ptr("hello world", "world"));

    return 0;
}
