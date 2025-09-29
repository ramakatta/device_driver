#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
//#include "t1040_immap.h"
int fd;
void mysighndlr(int signo)
{
  int flgs;
    printf("Signal %d received\n",signo);

  flgs = fcntl(fd,F_GETFL);
  fcntl(fd,F_SETFL,flgs | FASYNC);

}
int main(int argc,char *argv[])
{
 char buf[100];
 int stat,len,flgs,data;
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

 printf("fd = %d\n",fd);
 signal(SIGIO, mysighndlr);
 fcntl(fd,F_SETOWN,getpid());
 flgs = fcntl(fd,F_GETFL);
 fcntl(fd,F_SETFL,flgs | FASYNC);
 while(1)
 { printf("enter data\n");
   scanf("%d",&data);
 }
}


