/*
 * example.c: very simple example of port I/O
 *
 * This code does nothing useful, just a port write, a pause,
 * and a port read. Compile with `gcc -O2 -o example example.c',
 * and run as root with `./example'.
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/io.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BASE_PORT 0x70 /* lp1 */

int main()
{
  char val = 0;
  int fd = -1;
  fd = open("/dev/port",O_RDWR);
  if(!fd)
  {
    printf("Unable to open /dev/port\n");
    return -1;
  }
   lseek(fd,BASE_PORT,SEEK_SET);
   write(fd,&val,1);
   val = 0;
   lseek(fd,BASE_PORT+1,SEEK_SET);
   read(fd,&val,1);
  printf("seconds:%x\n",val); 
  
}
