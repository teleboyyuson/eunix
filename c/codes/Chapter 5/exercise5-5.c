#include <stdio.h>
#include <string.h>

// strncpy: Copy at most n characters of t to s
void strncpy_custom(char *s, const char *t, int n) {
    while (n-- > 0 && (*s++ = *t++))
        ;
    while (n-- > 0)
        *s++ = '\0';
}

// strncat: Concatenate at most n characters of t to s
void strncat_custom(char *s, const char *t, int n) {
    while (*s)  // Move to end of s
        s++;
    while (n-- > 0 && (*s++ = *t++))
        ;
    *s = '\0';  // Null-terminate
}

// strncmp: Compare at most n characters of s and t
int strncmp_custom(const char *s, const char *t, int n) {
    for (; n > 0; s++, t++, n--) {
        if (*s != *t)
            return *s - *t;
        if (*s == '\0')
            break;
    }
    return 0;
}

int main() {
    char s1[50] = "Hello";
    char s2[] = "World!";
    char buffer[50];

    // Test strncpy
    strncpy_custom(buffer, s2, 3);
    buffer[3] = '\0';  // Manually null-terminate
    printf("strncpy_custom: %s\n", buffer);

    // Test strncat
    strncat_custom(s1, s2, 3);
    printf("strncat_custom: %s\n", s1);

    // Test strncmp
    int result = strncmp_custom("Hello", "Help", 3);
    printf("strncmp_custom: %d\n", result);

    return 0;
}
