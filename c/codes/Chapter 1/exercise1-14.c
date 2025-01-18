#include <stdio.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 20  // Maximum word length to track
#define IN  1               // Inside a word
#define OUT 0               // Outside a word

void print_horizontal_histogram(int word_lengths[], int max_length);
void print_vertical_histogram(int word_lengths[], int max_length);

int main() {
    int c, state = OUT;
    int word_lengths[MAX_WORD_LENGTH + 1] = {0};
    int current_length = 0;

    printf("Enter text (Ctrl+D to end input):\n");

    while ((c = getchar()) != EOF) {
        if (isspace(c)) {
            if (state == IN) {
                // End of a word
                state = OUT;
                if (current_length <= MAX_WORD_LENGTH) {
                    word_lengths[current_length]++;
                }
                current_length = 0;
            }
        } else {
            // Inside a word
            state = IN;
            current_length++;
        }
    }

    // Handle the last word in the input
    if (current_length > 0 && current_length <= MAX_WORD_LENGTH) {
        word_lengths[current_length]++;
    }

    printf("\nVertical Histogram of Word Lengths:\n");
    print_vertical_histogram(word_lengths, MAX_WORD_LENGTH);

    return 0;
}

// Function to print a vertical histogram
void print_vertical_histogram(int word_lengths[], int max_length) {
    int max_count = 0;

    // Find the maximum count for scaling the histogram
    for (int i = 1; i <= max_length; i++) {
        if (word_lengths[i] > max_count) {
            max_count = word_lengths[i];
        }
    }

    // Print the histogram vertically
    for (int row = max_count; row > 0; row--) {
        for (int length = 1; length <= max_length; length++) {
            if (word_lengths[length] >= row) {
                printf("  #  ");
            } else {
                printf("     ");
            }
        }
        printf("\n");
    }

    // Print the base with word lengths
    for (int length = 1; length <= max_length; length++) {
        printf(" %3d ", length);
    }
    printf("\n");
}
