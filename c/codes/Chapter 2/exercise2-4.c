#include <stdio.h>

void squeeze(char s1[], const char s2[]) {
    int i, j, k, found;

    for (i = j = 0; s1[i] != '\0'; i++) {
        found = 0;
        // Check if s1[i] is in s2
        for (k = 0; s2[k] != '\0'; k++) {
            if (s1[i] == s2[k]) {
                found = 1;
                break;
            }
        }
        // If not found, keep the character in s1
        if (!found) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0'; // Null-terminate the modified string
}

int main() {
    char s1[] = "hello world";
    const char s2[] = "aeiou";

    printf("Before squeeze: %s\n", s1);
    squeeze(s1, s2);
    printf("After squeeze: %s\n", s1);

    return 0;
}
