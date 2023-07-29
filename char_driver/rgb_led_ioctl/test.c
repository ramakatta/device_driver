#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "ioctl_const.h"

int main(int argc, char *argv[])
{
  char buf;
  int option,n,fd;
  char port;

  if(argc == 2)
    fd = open(argv[1], O_RDWR);
  else
    fd = open("/dev/mydev", O_RDWR);
  if(fd<0)
  {
    perror("open /dev/mydev: ");
    exit(0);
  }
  printf("Opened /dev/mydev successfully. Got fd as %d\n",fd);
  port = 20;
  ioctl(fd, SET_GPIO_OUT,&port);
  port = 10;
  ioctl(fd, SET_GPIO_OUT,&port);
  port = 11;
  ioctl(fd, SET_GPIO_OUT,&port);
  while(1)
  {
    printf("Enter 1 to read LED value, 2 write to LED and 3 to exit\n");
    scanf("%d", &option);
    switch(option)
    {
      case 1:
        n = read(fd,&buf,1);
        printf("Read %d bytes\n",n);
        printf("Read value is: %x\n", buf);
        break;
      case 2:
        printf("Enter value to write to LED\n");
        __fpurge(stdin);
        scanf("%x",&buf);
        n = write(fd,&buf, 1);
        break;
      case 3:
        close(fd);
        exit(0);

      default:
        printf("Invalid option\n");
    }
  }
}
                  
