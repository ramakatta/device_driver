#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  int fd,temp_fd;
  fd = open("dupdemo.txt", O_RDWR | O_CREAT | O_TRUNC,0660);
  if(fd < 0)
  {
    printf("Could not open file\n");
    exit(2);
  }
  printf("Sample string one\n");
  dup2(fd,1);
  printf("Sample string one\n");
  printf("Sample string two\n");
  puts("Sample string three\n");
  puts("Sample string three\n");
}
