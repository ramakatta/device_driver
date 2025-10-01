#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	int fd;
	struct stat buf;
	fd = open(argv[1],O_RDONLY);
	if(fd < 0)
	{
		printf("file does not exist\n");
		exit(1);
	}
        printf("%d:fd",fd);
	if(fstat(fd,&buf)!=-1)
	printf("file size:%lu block size:%lu\n",buf.st_size,buf.st_blksize);
}
