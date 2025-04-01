#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define DEFAULT_GROUP_LENGTH 6

struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
};

/* Function prototypes */
struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int);
int is_variable(char *);

/* Global settings */
int group_length = DEFAULT_GROUP_LENGTH;

int main(int argc, char *argv[]) {
    struct tnode *root = NULL;
    char word[MAXWORD];

    if (argc > 1) {
        group_length = atoi(argv[1]);  // Set grouping length from command line
    }

    while (getword(word, MAXWORD) != EOF) {
        if (is_variable(word)) {
            root = addtree(root, word, group_length);
        }
    }

    treeprint(root);
    return 0;
}

/* Add a node to the tree */
struct tnode *addtree(struct tnode *p, char *w, int n) {
    int cond;
    if (p == NULL) {
        p = (struct tnode *) malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->left = p->right = NULL;
    } else if ((cond = strncmp(w, p->word, n)) == 0) {
        ;  // Ignore exact matches within group length
    } else if (cond < 0) {
        p->left = addtree(p->left, w, n);
    } else {
        p->right = addtree(p->right, w, n);
    }
    return p;
}

/* Print tree in-order */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%s\n", p->word);
        treeprint(p->right);
    }
}

/* Get next word from input */
int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getchar()))  // Skip whitespace
        ;

    if (c != EOF) {
        *w++ = c;
    }

    if (isalpha(c) || c == '_') {  // Variable names start with letter or _
        for (; --lim > 0; w++) {
            if (!isalnum(*w = getchar()) && *w != '_') {
                ungetc(*w, stdin);
                break;
            }
        }
    } else if (c == '\"' || c == '\'') {  // Skip strings and character constants
        int quote = c;
        while ((c = getchar()) != quote) {
            if (c == '\\')  // Handle escape sequences
                getchar();
            if (c == EOF)
                break;
        }
    } else if (c == '/') {  // Skip comments
        int next = getchar();
        if (next == '/') {  // Single-line comment
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        } else if (next == '*') {  // Multi-line comment
            while ((c = getchar()) != EOF) {
                if (c == '*' && (c = getchar()) == '/')
                    break;
            }
        } else {
            ungetc(next, stdin);
        }
    }

    *w = '\0';
    return c;
}

/* Check if a word is a valid variable name */
int is_variable(char *word) {
    if (!isalpha(word[0]) && word[0] != '_')
        return 0;
    return 1;
}
