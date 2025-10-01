#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
  char ch[4096];
  int fd1,fd2,nret;
  struct stat buf;
  printf("argc:%d\n",argc);
  fd1 = open(argv[1],O_RDONLY,0); 
  if(fd1 < 0)
  {
    printf("File not exist\n");
    exit(1);
  }
  printf("fd:%d\n",fd1);
  fd2 = open(argv[2],O_WRONLY |O_CREAT| O_TRUNC,0); 
  if(fd2 < 0)
  {
    printf("File already exist for write\n");
    exit(1);
  }
/*  while(1)
  {
    nret = read(fd1,&ch,1); 
    if(nret <= 0)
    break;
    write(fd2,&ch,1);
  }*/
  fstat(fd1,&buf);
  do
  {
    nret = read(fd1,ch,buf.st_blksize); 
    write(fd2,ch,nret);
  }
  while(nret == buf.st_blksize);
  close(fd1);
  close(fd2);
}  
