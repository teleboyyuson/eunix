#include <stdio.h>
#include <string.h> // For strcspn function

int any(const char s1[], const char s2[]) {
    for (int i = 0; s1[i] != '\0'; i++) {
        for (int j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                return i; // Return the index of the first match
            }
        }
    }
    return -1; // Return -1 if no characters match
}

int main() {
    char s1[100], s2[100];

    // Get user input for both strings
    printf("Enter the first string (s1): ");
    fgets(s1, sizeof(s1), stdin);

    printf("Enter the second string (s2): ");
    fgets(s2, sizeof(s2), stdin);

    // Remove the newline character if present
    s1[strcspn(s1, "\n")] = '\0';
    s2[strcspn(s2, "\n")] = '\0';

    // Call the any function
    int result = any(s1, s2);

    if (result != -1) {
        printf("The first matching character is at index %d\n", result);
    } else {
        printf("No characters from s2 found in s1\n");
    }

    return 0;
}
