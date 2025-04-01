#include <stdio.h>
#include <string.h>

int strend(const char *s, const char *t) {
    int len_s = strlen(s);
    int len_t = strlen(t);

    // If t is longer than s, it cannot be at the end
    if (len_t > len_s)
        return 0;

    // Compare the last len_t characters of s with t
    return strcmp(s + len_s - len_t, t) == 0;
}

int main() {
    char s[] = "Hello, World!";
    char t[] = "World!";
    char u[] = "Hello";

    printf("Does '%s' end with '%s'? %d\n", s, t, strend(s, t)); // Should return 1
    printf("Does '%s' end with '%s'? %d\n", s, u, strend(s, u)); // Should return 0

    return 0;
}
