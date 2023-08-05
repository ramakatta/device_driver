#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define error(x, y) fprintf(stderr, "%s: error while %s on %s: %s\n", argv[0], x, y, strerror(errno));

int main(int argc, char *argv[])
{
    int src, dst;
    int ret = EXIT_FAILURE;
    ssize_t nread, nwritten;
    struct stat info;

    char *buf;

    if (argc < 3) {
        fprintf(stderr, "usage: %s source destination.\n", argv[0]);
        goto exit_program;
    }    
    
    if (stat(argv[1], &info) == -1) {
        error("stat", argv[1]);
        goto exit_program;
    }

    if ((src = open(argv[1], O_RDONLY)) == -1) {
        error("opening", argv[1]);
        goto exit_program;
    }

    if ((dst = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0644)) == -1) { 
        /* S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH */
        error("opening", argv[2]);
        goto close_source;
    
    }
    
    if ((buf = (char *)mmap(NULL, info.st_size, 
                            PROT_READ | PROT_WRITE, 
                            MAP_PRIVATE, src, 0)) == MAP_FAILED) {
        error("mmap", argv[2]);
        goto close_dest;
    }

    if ((nwritten = write(dst, buf, info.st_size)) == -1) {
        error("reading", argv[1]);
        goto free_memory;
    }

    ret = EXIT_SUCCESS;

free_memory:
    munmap(buf, info.st_size);
close_dest:
    close(dst);
close_source:
    close(src);
exit_program:    
    return ret; 
}

