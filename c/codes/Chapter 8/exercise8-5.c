#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

// Function declarations
void fsize(const char *name);
void print_inode_info(const char *name, struct stat *st);

// Main program
int main(int argc, char **argv) {
    if (argc == 1) {
        fsize(".");  // Default: current directory
    } else {
        while (--argc > 0)
            fsize(*++argv);
    }
    return 0;
}

// Print detailed inode information
void print_inode_info(const char *name, struct stat *st) {
    struct passwd *pw = getpwuid(st->st_uid);
    struct group  *gr = getgrgid(st->st_gid);

    char modtime[64];
    strftime(modtime, sizeof(modtime), "%Y-%m-%d %H:%M:%S", localtime(&st->st_mtime));

    printf("\nFile: %s\n", name);
    printf("Size: %ld bytes\n", (long)st->st_size);
    printf("Inode: %ld\n", (long)st->st_ino);
    printf("Mode: %o\n", st->st_mode);
    printf("Links: %ld\n", (long)st->st_nlink);
    printf("Owner: %s (UID: %d)\n", pw ? pw->pw_name : "Unknown", st->st_uid);
    printf("Group: %s (GID: %d)\n", gr ? gr->gr_name : "Unknown", st->st_gid);
    printf("Last Modified: %s\n", modtime);
}

// Recursively process file or directory
void fsize(const char *name) {
    struct stat st;

    if (lstat(name, &st) < 0) {
        fprintf(stderr, "Error accessing %s: %s\n", name, strerror(errno));
        return;
    }

    // If it's a directory, recurse
    if (S_ISDIR(st.st_mode)) {
        DIR *dp = opendir(name);
        if (dp == NULL) {
            fprintf(stderr, "Cannot open directory %s: %s\n", name, strerror(errno));
            return;
        }

        struct dirent *entry;
        while ((entry = readdir(dp)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            fsize(path);
        }
        closedir(dp);
    }

    // Print info for the file or directory
    print_inode_info(name, &st);
}

