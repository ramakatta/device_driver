/* $ gcc -D_FILE_OFFSET_BITS=64 -o largefile lagefile.c  
 * 		OR
 * #define _FILE_OFFSET_BITS 64
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
        int fd;
        off_t size = 1024*1024*4000LL;
        const char *file = "/var/tmp/largefile_test";

        fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
        lseek(fd, size, SEEK_SET);
        write(fd, "TEST", 4);
        close(fd);

        exit(EXIT_SUCCESS);
}
