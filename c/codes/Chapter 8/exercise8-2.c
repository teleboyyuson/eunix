#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

typedef struct _iobuf {
    int fd;              // File descriptor
    char *ptr;           // Next character position in buffer
    char *base;          // Buffer base address
    int cnt;             // Number of characters left
    int read;            // Read mode flag
    int write;           // Write mode flag
    int unbuf;           // Unbuffered flag
    int eof;             // EOF flag
    int err;             // Error flag
} FILEX;

FILEX *fopenx(const char *filename, const char *mode);
int _fillbuf(FILEX *fp);
int _flushbuf(int c, FILEX *fp);

#define getcx(fp)  ((--(fp)->cnt >= 0) ? (unsigned char) *(fp)->ptr++ : _fillbuf(fp))

int main() {
    FILEX *fp = fopenx("test.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    int c;
    while ((c = getcx(fp)) != EOF)
        putchar(c);

    close(fp->fd);
    free(fp->base);
    free(fp);
    return 0;
}


FILEX *fopenx(const char *filename, const char *mode) {
    int fd;
    FILEX *fp = (FILEX *) malloc(sizeof(FILEX));

    if (fp == NULL) return NULL;

    if (*mode == 'r') {
        fd = open(filename, O_RDONLY);
        fp->read = 1;
        fp->write = 0;
    } else if (*mode == 'w') {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        fp->read = 0;
        fp->write = 1;
    } else {
        free(fp);
        return NULL;
    }

    if (fd == -1) {
        free(fp);
        return NULL;
    }

    fp->fd = fd;
    fp->cnt = 0;
    fp->ptr = NULL;
    fp->base = NULL;
    fp->unbuf = 0;
    fp->eof = 0;
    fp->err = 0;

    return fp;
}

int _fillbuf(FILEX *fp) {
    if (!fp->read || fp->eof || fp->err) return EOF;

    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(BUFSIZE)) == NULL) {
            fp->err = 1;
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->base, BUFSIZE);
    
    if (fp->cnt <= 0) {
        if (fp->cnt == 0)
            fp->eof = 1;
        else
            fp->err = 1;
        return EOF;
    }
    
    return (unsigned char) *fp->ptr++;
}
