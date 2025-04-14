#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 1024

typedef struct _iobuf {
    int fd;
    char *base;
    char *ptr;
    int cnt;
    int flag;
} FILE_CUSTOM;

enum _flags {
    _READ = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF = 010,
    _ERR = 020
};

int fseek_custom(FILE_CUSTOM *fp, long offset, int origin) {
    if (fp->flag & _WRITE) {
        if (fp->base != NULL) {
            int n = fp->ptr - fp->base;
            if (write(fp->fd, fp->base, n) != n) {
                fp->flag |= _ERR;
                return -1;
            }
        }
    } else if (fp->flag & _READ) {
        if (origin == SEEK_CUR) {
            offset -= fp->cnt;
        }
        fp->cnt = 0;
        fp->ptr = fp->base;
    }

    if (lseek(fp->fd, offset, origin) == -1) {
        fp->flag |= _ERR;
        return -1;
    }

    return 0;
}

int main() {
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    FILE_CUSTOM myfile;
    char buffer[BUFSIZE];

    myfile.fd = fd;
    myfile.base = buffer;
    myfile.ptr = buffer;
    myfile.cnt = 0;
    myfile.flag = _READ;

    if (fseek_custom(&myfile, 10, SEEK_SET) == 0) {
        printf("Successfully seeked 10 bytes from start of file.\n");
    } else {
        printf("Seek failed.\n");
    }

    close(fd);
    return 0;
}


