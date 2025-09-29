#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  char buf[81],buf1[81];
  int option,nbytes,n,fd;

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

  while(1)
  {
    printf("Enter 1 to read device, 2 write to device and 3 to exit\n");
    scanf("%d", &option);
    switch(option)
    {
      case 1:
        printf("Enter number of bytes to read\n");
        scanf("%d", &nbytes);
        if(nbytes > 80)
          nbytes = 80;
	memset(buf1,0,80);
        n = read(fd,buf1,nbytes);
        printf("Read %d bytes\n",n);
        buf1[n] = '\0';
        printf("Read string is: %s\n", buf1);
        break;

      case 2:
        printf("Enter message to write to device\n");
        __fpurge(stdin);
        fgets(buf,80,stdin);
        n = write(fd,buf, strlen(buf));
        printf("When wrote %d bytes, %d bytes got written\n",strlen(buf),n);
        break;

      case 3:
        close(fd);
        exit(0);

      default:
        printf("Invalid option\n");
    }
  }
}
