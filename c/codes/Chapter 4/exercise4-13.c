#include <stdio.h>
#include <string.h>

// Recursive function to reverse a string
void reverse_recursive(char s[], int low, int high) {
    if (low >= high) 
        return;  // Base case: stop when pointers meet or cross

    // Swap characters at low and high positions
    char temp = s[low];
    s[low] = s[high];
    s[high] = temp;

    // Recursive call with next positions
    reverse_recursive(s, low + 1, high - 1);
}

// Wrapper function to start recursion
void reverse(char s[]) {
    int length = strlen(s);
    if (length > 1)  // Only reverse if more than one character
        reverse_recursive(s, 0, length - 1);
}

// Main function to test reverse()
int main() {
    char str1[] = "hello";
    char str2[] = "recursion";

    reverse(str1);
    printf("Reversed: %s\n", str1);

    reverse(str2);
    printf("Reversed: %s\n", str2);

    return 0;
}
