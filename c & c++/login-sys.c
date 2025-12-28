#include <stdio.h>
#include <string.h>

int main() {
    char username[20], password[20];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 &&
        strcmp(password, "1234") == 0)
        printf("Login successful!\n");
    else
        printf("Invalid login!\n");

    return 0;
}
