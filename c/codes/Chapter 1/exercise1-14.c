#include <stdio.h>
#include <ctype.h>

#define CHAR_RANGE 128 // Range of ASCII characters (0-127)

void print_vertical_histogram(int frequencies[], int range);

int main() {
    int c;
    int frequencies[CHAR_RANGE] = {0};

    printf("Enter text (Ctrl+D to end input):\n");

    // Read input and count frequencies of each character
    while ((c = getchar()) != EOF) {
        if (c >= 0 && c < CHAR_RANGE) {
            frequencies[c]++;
        }
    }

    printf("\nVertical Histogram of Character Frequencies:\n");
    print_vertical_histogram(frequencies, CHAR_RANGE);

    return 0;
}

// Function to print a vertical histogram
void print_vertical_histogram(int frequencies[], int range) {
    int max_frequency = 0;

    // Find the maximum frequency
    for (int i = 0; i < range; i++) {
        if (frequencies[i] > max_frequency) {
            max_frequency = frequencies[i];
        }
    }

    // Print the histogram vertically
    for (int row = max_frequency; row > 0; row--) {
        for (int i = 0; i < range; i++) {
            if (frequencies[i] > 0) { // Only include characters that appear in input
                if (frequencies[i] >= row) {
                    printf("  #  ");
                } else {
                    printf("     ");
                }
            }
        }
        printf("\n");
    }

    // Print the character labels
    for (int i = 0; i < range; i++) {
        if (frequencies[i] > 0) {
            if (isprint(i)) { // Printable character
                printf("  %c  ", i);
            } else { // Non-printable character
                printf(" %02X  ", i);
            }
        }
    }
    printf("\n");
}
    }
    printf("\n");
}
