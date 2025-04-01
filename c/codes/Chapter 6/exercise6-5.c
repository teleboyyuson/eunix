#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist { /* Table entry */
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE]; /* Hash table */

/* Hash function */
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* Lookup name in hash table */
struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

/* Install name-definition pair in hash table */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* Not found */
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *)np->defn); /* Free old definition */
    }
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* Remove a name-definition pair from the hash table */
void undef(char *name) {
    struct nlist *np, *prev = NULL;
    unsigned hashval = hash(name);

    for (np = hashtab[hashval]; np != NULL; prev = np, np = np->next) {
        if (strcmp(name, np->name) == 0) { /* Found */
            if (prev == NULL) /* First in chain */
                hashtab[hashval] = np->next;
            else
                prev->next = np->next;
            free(np->name);
            free(np->defn);
            free(np);
            return;
        }
    }
}

/* Print the hash table */
void print_table() {
    struct nlist *np;
    for (int i = 0; i < HASHSIZE; i++) {
        for (np = hashtab[i]; np != NULL; np = np->next)
            printf("%s -> %s\n", np->name, np->defn);
    }
}

/* Main function to test */
int main() {
    install("MAX", "100");
    install("PI", "3.14159");
    install("E", "2.71828");

    printf("Before undef:\n");
    print_table();

    undef("PI");

    printf("\nAfter undef(\"PI\"):\n");
    print_table();

    return 0;
}
