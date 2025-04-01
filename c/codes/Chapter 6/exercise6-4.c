#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

/* Tree node structure */
struct tnode {
    char *word;
    int count;
    struct tnode *left, *right;
};

/* Function prototypes */
struct tnode *addtree(struct tnode *, char *);
void tree_to_array(struct tnode *, struct tnode **, int *);
int compare(const void *, const void *);
void print_sorted(struct tnode **, int);
int getword(char *, int);

/* Add a word to the binary tree */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;
    if (p == NULL) {
        p = (struct tnode *)malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

/* Convert tree to an array */
void tree_to_array(struct tnode *p, struct tnode **arr, int *index) {
    if (p != NULL) {
        tree_to_array(p->left, arr, index);
        arr[(*index)++] = p;
        tree_to_array(p->right, arr, index);
    }
}

/* Comparator function for sorting */
int compare(const void *a, const void *b) {
    struct tnode *nodeA = *(struct tnode **)a;
    struct tnode *nodeB = *(struct tnode **)b;
    return nodeB->count - nodeA->count; // Descending order
}

/* Print sorted words */
void print_sorted(struct tnode **arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%4d %s\n", arr[i]->count, arr[i]->word);
    }
}

/* Read words from input */
int getword(char *word, int lim) {
    int c;
    char *w = word;
    while (isspace(c = getchar())) 
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getchar())) {
            ungetc(*w, stdin);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

/* Main function */
int main() {
    struct tnode *root = NULL;
    struct tnode *word_array[1000]; // Assume max 1000 words
    int count = 0;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) // Only add words
            root = addtree(root, word);
    }

    tree_to_array(root, word_array, &count);
    qsort(word_array, count, sizeof(struct tnode *), compare);
    print_sorted(word_array, count);

    return 0;
}
