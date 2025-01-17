#include <stdio.h>
#include <ctype.h>
#include <string.h>

int htoi(const char s[]);

int main() {
    char hex1[] = "0x1A3F";
    char hex2[] = "1A3F";
    char hex3[] = "0XFF";
    char hex4[] = "abc";

    printf("Hexadecimal: %s -> Integer: %d\n", hex1, htoi(hex1));
    printf("Hexadecimal: %s -> Integer: %d\n", hex2, htoi(hex2));
    printf("Hexadecimal: %s -> Integer: %d\n", hex3, htoi(hex3));
    printf("Hexadecimal: %s -> Integer: %d\n", hex4, htoi(hex4));

    return 0;
}

int htoi(const char s[]) {
    int i = 0, value = 0;

    // Skip optional "0x" or "0X"
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        i = 2;
    }

    // Convert the string
    for (; s[i] != '\0'; i++) {
        char c = s[i];
        int digit = 0;

        if (isdigit(c)) {
            digit = c - '0'; // Convert '0'-'9' to 0-9
        } else if (c >= 'a' && c <= 'f') {
            digit = c - 'a' + 10; // Convert 'a'-'f' to 10-15
        } else if (c >= 'A' && c <= 'F') {
            digit = c - 'A' + 10; // Convert 'A'-'F' to 10-15
        } else {
            // Invalid character
            return -1; // Return -1 for error
        }

        value = value * 16 + digit; // Accumulate value
    }

    return value;
}
