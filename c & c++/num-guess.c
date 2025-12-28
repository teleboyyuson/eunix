#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int guess, number;
    srand(time(0));
    number = rand() % 100 + 1;

    do {
        printf("Guess the number (1-100): ");
        scanf("%d", &guess);

        if (guess > number)
            printf("Too high!\n");
        else if (guess < number)
            printf("Too low!\n");
        else
            printf("Correct! 🎉\n");

    } while (guess != number);

    return 0;
}
