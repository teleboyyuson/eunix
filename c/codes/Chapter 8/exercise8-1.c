#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void filecopy(int fd);

int main(int argc, char *argv[]) {
    int fd;
    
    if (argc == 1) {
        // No arguments, read from standard input
        filecopy(STDIN_FILENO);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY)) == -1) {
                perror("cat: cannot open file");
                exit(1);
            }
            filecopy(fd);
            close(fd);
        }
    }
    return 0;
}

void filecopy(int fd) {
    char buffer[BUFFER_SIZE];
    ssize_t n;

    while ((n = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, n) != n) {
            perror("cat: write error");
            exit(1);
        }
    }
}
