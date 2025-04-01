#include <stdio.h>

void strcat_ptr(char *s, const char *t) {
    // Move s to the end of the original string
    while (*s)
        s++;
    
    // Copy t to the end of s
    while ((*s++ = *t++))
        ;
}

int main() {
    char s[100] = "Hello, ";
    char t[] = "World!";
    
    strcat_ptr(s, t);

    printf("Concatenated string: %s\n", s);

    return 0;
}
