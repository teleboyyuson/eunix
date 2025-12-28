#include <stdio.h>

char board[9] = {'1','2','3','4','5','6','7','8','9'};

void display() {
    printf("\n %c | %c | %c ", board[0], board[1], board[2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[3], board[4], board[5]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
}

int main() {
    int player = 1, choice;
    char mark;

    for (int i = 0; i < 9; i++) {
        display();
        player = (player % 2) ? 1 : 2;
        printf("Player %d, choose position: ", player);
        scanf("%d", &choice);

        mark = (player == 1) ? 'X' : 'O';
        board[choice - 1] = mark;
        player++;
    }
    display();
    return 0;
}
