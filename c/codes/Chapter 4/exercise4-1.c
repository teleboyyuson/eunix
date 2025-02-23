#include <stdio.h>

int strrindex(char s[], char t) {
    int i, pos = -1;
    
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == t) {
            pos = i;  // Update position whenever 't' is found
        }
    }

    return pos;
}

int main() {
    char s[] = "hello world";
    char t = 'o';

    int result = strrindex(s, t);
    if (result != -1)
        printf("Rightmost occurrence of '%c' is at index %d\n", t, result);
    else
        printf("Character '%c' not found in string\n", t);

    return 0;
}
