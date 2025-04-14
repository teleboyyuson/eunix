#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MY_BUFSIZ 1024
#define OPEN_MAX 20  // max # of files open at once

// Custom FILE-like structure
typedef struct _iobuf {
    int cnt;        // characters left
    char *ptr;      // next character position
    char *base;     // buffer base
    int flag;       // mode of access
    int fd;         // file descriptor
} FILE_SIM;

enum _flags {
    _READ  = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF   = 010,
    _ERR   = 020
};

FILE_SIM _iob[OPEN_MAX];

// Flush buffer of FILE_SIM
int _flushbuf(int c, FILE_SIM *f) {
    int bufsize;

    if ((f->flag & (_WRITE | _ERR)) != _WRITE)
        return EOF;

    bufsize = (f->flag & _UNBUF) ? 1 : MY_BUFSIZ;

    if (f->base == NULL) {
        f->base = (char *) malloc(bufsize);
        if (f->base == NULL) {
            f->flag |= _UNBUF;
            bufsize = 1;
        } else {
            f->ptr = f->base;
        }
    }

    int n = f->ptr - f->base;
    if (n > 0) {
        if (write(f->fd, f->base, n) != n) {
            f->flag |= _ERR;
            return EOF;
        }
    }

    f->ptr = f->base;
    f->cnt = bufsize - 1;

    if (c != EOF) {
        *f->ptr++ = c;
        return (unsigned char) c;
    }

    return 0;
}

// Flush one stream or all
int fflush_sim(FILE_SIM *f) {
    if (f == NULL) {
        int status = 0;
        for (int i = 0; i < OPEN_MAX; i++) {
            if ((_iob[i].flag & _WRITE) && fflush_sim(&_iob[i]) == EOF)
                status = EOF;
        }
        return status;
    }

    if ((f->flag & _WRITE) == 0)
        return EOF;

    return _flushbuf(EOF, f);
}

// Close stream
int fclose_sim(FILE_SIM *f) {
    if (f == NULL)
        return EOF;

    if (fflush_sim(f) == EOF)
        return EOF;

    if (close(f->fd) == -1)
        return EOF;

    if (f->base != NULL)
        free(f->base);

    f->base = NULL;
    f->ptr = NULL;
    f->cnt = 0;
    f->flag = 0;
    f->fd = -1;

    return 0;
}

// Test main
int main() {
    // test your functions here
    printf("Testing _flushbuf and related functions...\n");

    // Example: open file, write, flush, close, etc.
    FILE *fp = fopen("test.txt", "w");
    if (fp == NULL) {
        perror("fopen failed");
        return 1;
    }

    fputs("This should be written to file\n", fp);
    fflush(fp);  // force write to file
    fputs("Another line\n", fp);
    fclose(fp);

    return 0;
}
