#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_SIZE 16 
int main(int argc, char *argv[])
{
  int fd;
  int nbytes = 0;
  char buffer[MAX_SIZE];

  if(argc < 2)
  {
    printf("Filename is missing\n");
    exit(1);
  }

  fd = open(argv[1],O_RDONLY);
  printf("file desc:%d\n",fd);
  if(fd < 0)
  {
    printf("Could not open file\n");
    exit(2);
  }
  if(lseek(fd, 0-MAX_SIZE,SEEK_END) < 0)
   lseek(fd,0,SEEK_SET);
  nbytes=read(fd,buffer,MAX_SIZE);
  printf("nbytes read:%d\n",nbytes);
  puts(buffer);
  close(fd);
}

