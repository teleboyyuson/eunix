#include <stdio.h>

int main() {
    char text[100];
    int key;

    printf("Enter text: ");
    scanf(" %[^\n]", text);
    printf("Enter key: ");
    scanf("%d", &key);

    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = text[i] + key;
    }

    printf("Encrypted text: %s\n", text);
    return 0;
}
