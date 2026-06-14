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

    char *buf,*buf2;

    if (argc < 2) {
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
    if ((buf = (char *)mmap(NULL, info.st_size, 
                            PROT_READ | PROT_WRITE, 
                            MAP_PRIVATE, src, 0)) == MAP_FAILED) {
        error("mmap", argv[2]);
        goto close_source;
    }
    printf("%s",buf);
     if( msync(buf, info.st_size,MS_SYNC) < 0)
    {
       perror("msync failed");
       goto exit_mmap;

    }
    if(mlock(buf, info.st_size)< 0)
    {
       perror("mlock failed");
       goto exit_mmap;
    }
    return 0;
exit_mmap:
    munmap(buf, info.st_size);
close_source:
    close(src);
exit_program:    
    return ret; 
}



