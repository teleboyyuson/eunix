#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define NOISE_WORDS_SIZE 5

struct tnode {
    char *word;
    int *lines;
    int line_count;
    int line_alloc;
    struct tnode *left;
    struct tnode *right;
};

char *noise_words[] = {"the", "and", "of", "to", "a"};

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int);
int is_noise_word(char *);

int main(void) {
    struct tnode *root = NULL;
    char word[MAXWORD];
    int line = 1;
    int c;

    while ((c = getword(word, MAXWORD)) != EOF) {
        if (isalpha(word[0]) && !is_noise_word(word)) {
            root = addtree(root, word, line);
        }
        if (c == '\n')
            line++;
    }
    treeprint(root);
    return 0;
}

struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup_custom(char *s) {
    char *p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

struct tnode *addtree(struct tnode *p, char *w, int line) {
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup_custom(w);
        p->lines = (int *) malloc(sizeof(int) * 10);
        p->lines[0] = line;
        p->line_count = 1;
        p->line_alloc = 10;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        if (p->line_count == 0 || p->lines[p->line_count - 1] != line) {
            if (p->line_count >= p->line_alloc) {
                p->line_alloc *= 2;
                p->lines = (int *) realloc(p->lines, sizeof(int) * p->line_alloc);
            }
            p->lines[p->line_count++] = line;
        }
    } else if (cond < 0) {
        p->left = addtree(p->left, w, line);
    } else {
        p->right = addtree(p->right, w, line);
    }
    return p;
}

void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%s: ", p->word);
        for (int i = 0; i < p->line_count; i++)
            printf("%d ", p->lines[i]);
        printf("\n");
        treeprint(p->right);
    }
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getchar()))
        if (c == '\n')
            return '\n';

    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getchar()) && *w != '_') {
            ungetc(*w, stdin);
            break;
        }
    *w = '\0';
    return word[0];
}

int is_noise_word(char *word) {
    for (int i = 0; i < NOISE_WORDS_SIZE; i++)
        if (strcmp(word, noise_words[i]) == 0)
            return 1;
    return 0;
}
