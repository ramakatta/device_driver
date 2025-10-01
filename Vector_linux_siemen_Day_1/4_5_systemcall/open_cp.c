#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
  int fd,fd2;
  char ch;
  int offset = 0;

  if(argc < 3)
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

  fd2 = open(argv[2],O_RDWR|O_CREAT);
  printf("file desc:%d\n",fd2);
  if(fd2 < 0)
  {
    printf("Could not open file\n");
    exit(2);
  }
  while(read(fd,&ch,1)==1)
  {
     write(fd2,&ch,1);
  }
  printf("\n");
  close(fd);
  close(fd2);
}

