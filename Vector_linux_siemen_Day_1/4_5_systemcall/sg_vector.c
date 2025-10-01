#include<sys/stat.h>
#include<sys/uio.h>
#include<fcntl.h>
#include<stdio.h>
#define STR_SIZE 150
int main(int argc, char *argv[])
{
   int fd,fd_wr;
   struct iovec iov[3];
   struct stat myStruct,myStruct_wr;
   /* First buffer */
   int x=0,x_wr=0;
   /* Second buffer */
   char str[STR_SIZE],str_wr[STR_SIZE];
   /* Third buffer */
   ssize_t numRead, totRequired;
   if (argc != 2 || strcmp(argv[1], "--help") == 0)
      printf("%s file\n", argv[0]);
   
   fd_wr = open("test", O_WRONLY);
   if (fd_wr == -1)
   {
      perror("open");
      return -1;
   }
   fstat(fd_wr,&myStruct_wr);
   write(fd_wr,&myStruct_wr,sizeof(struct stat));
   x_wr=100;
   write(fd_wr,&x_wr,sizeof(int));
   strcpy(str_wr,"Hellow");
   write(fd_wr,str_wr,sizeof(str_wr));
   close(fd_wr);

   fd = open(argv[1], O_RDONLY);
   if (fd == -1)
   {
      perror("open");
      return -1;
   }

   totRequired = 0;

   iov[0].iov_base = &myStruct;
   iov[0].iov_len = sizeof(struct stat);
   totRequired += iov[0].iov_len;
   iov[1].iov_base = &x;
   iov[1].iov_len = sizeof(x);
   totRequired += iov[1].iov_len;
   iov[2].iov_base = str;
   iov[2].iov_len = STR_SIZE;
   totRequired += iov[2].iov_len;
   numRead = readv(fd, iov, 3);
   if (numRead == -1)
     perror("readv");

   if (numRead < totRequired)
   {
      printf("Read fewer bytes than requested\n");
   } 
      printf("total bytes requested: %ld; bytes read: %ld\n",(long) totRequired, (long) numRead);
      printf("Filesize:%d  Blocksize:%d blocks:%d\n",myStruct.st_size,myStruct.st_blksize,myStruct.st_blocks);
      printf("%s %d\n",(char*)str,x);
}
