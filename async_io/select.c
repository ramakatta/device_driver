#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
//#include "t1040_immap.h"
int main(int argc,char *argv[])
{
char buf[100];
int stat,len,flgs,data;
fd_set fds;
int fd,retval;
struct timeval tv;
if(argc < 2)
{
 printf("Enter device file name\n");
 return -1;
}
fd = open(argv[1], O_RDONLY);
if(fd<0)
{
printf("Unable to open the device\n");
exit(0);
}
FD_ZERO(&fds);
FD_SET(fd,&fds);
tv.tv_sec = 10;
tv.tv_usec = 10;
while(1)
{
retval = select(fd+1,&fds,0,0,&tv);
if(retval == -1)
printf("error\n");
if(retval)
{
  if(FD_ISSET(fd,&fds))
   {
      printf("got it\n");
    }
}
else
printf("timeout\n");
}
}




