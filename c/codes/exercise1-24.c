#include <stdio.h>
#include <stdbool.h>

#define MAXLINE 1000

void check_syntax(const char *line);
bool is_quote_escaped(const char *line, int pos);

int main() {
    char line[MAXLINE];

    printf("Enter your C code (Ctrl+D to finish):\n");
    while (fgets(line, MAXLINE, stdin)) {
        check_syntax(line);
    }

    return 0;
}

void check_syntax(const char *line) {
    int parens = 0, brackets = 0, braces = 0;
    bool in_single_quote = false, in_double_quote = false, in_comment = false;

    for (int i = 0; line[i] != '\0'; i++) {
        char c = line[i];

        if (in_comment) {
            if (c == '*' && line[i + 1] == '/') {
                in_comment = false;
                i++; // Skip next character
            }
            continue;
        }

        if (in_single_quote) {
            if (c == '\'' && !is_quote_escaped(line, i)) {
                in_single_quote = false;
            }
            continue;
        }

        if (in_double_quote) {
            if (c == '"' && !is_quote_escaped(line, i)) {
                in_double_quote = false;
            }
            continue;
        }

        switch (c) {
            case '/':
                if (line[i + 1] == '*') {
                    in_comment = true;
                    i++; // Skip next character
                }
                break;

            case '\'':
                if (!in_single_quote && !in_double_quote) {
                    in_single_quote = true;
                }
                break;

            case '"':
                if (!in_double_quote && !in_single_quote) {
                    in_double_quote = true;
                }
                break;

            case '(': 
                parens++;
                break;

            case ')': 
                parens--;
                if (parens < 0) {
                    printf("Unmatched closing parenthesis detected!\n");
                    parens = 0;
                }
                break;

            case '[':
                brackets++;
                break;

            case ']':
                brackets--;
                if (brackets < 0) {
                    printf("Unmatched closing bracket detected!\n");
                    brackets = 0;
                }
                break;

            case '{':
                braces++;
                break;

            case '}':
                braces--;
                if (braces < 0) {
                    printf("Unmatched closing brace detected!\n");
                    braces = 0;
                }
                break;

            default:
                break;
        }
    }

    if (in_comment) {
        printf("Unclosed comment detected!\n");
    }
    if (in_single_quote) {
        printf("Unclosed single quote detected!\n");
    }
    if (in_double_quote) {
        printf("Unclosed double quote detected!\n");
    }
    if (parens > 0) {
        printf("Unmatched opening parenthesis detected!\n");
    }
    if (brackets > 0) {
        printf("Unmatched opening bracket detected!\n");
    }
    if (braces > 0) {
        printf("Unmatched opening brace detected!\n");
    }
}

bool is_quote_escaped(const char *line, int pos) {
    int backslash_count = 0;
    for (int i = pos - 1; i >= 0 && line[i] == '\\'; i--) {
        backslash_count++;
    }
    return (backslash_count % 2) == 1;
}
