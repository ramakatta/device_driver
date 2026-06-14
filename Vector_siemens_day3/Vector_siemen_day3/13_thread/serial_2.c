#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<termios.h>
#include<pthread.h>
int fd1,fd2,fd;
void *thfun(void*);
void serial_init(char *pname)
{
   struct termios options;
   fd = open(pname,O_RDWR | O_NOCTTY);

   if(strcmp(pname,"/dev/ttyUSB0")==0)
      fd1=fd;
   else
      fd2=fd;

   if(fd < 0)
   {
	perror("open_port:Unable to open /dev/ttyUSB0\n");
   }
   else
   {
	//fcntl(fd,F_SETFL,FNDELAY);
   }
   tcgetattr(fd,&options);	
   cfsetispeed(&options,B9600);
   cfsetospeed(&options,B9600);

   options.c_cflag |= (CLOCAL | CREAD);

   //Set character size   
   options.c_cflag &=~ CSIZE;
   options.c_cflag |=  CS8;
   
   //Set Parity - No Parity (8N)
   
   options.c_cflag &=~ PARENB;
   options.c_cflag &=~ CSTOPB;
   options.c_cflag &=~ CSIZE;
   options.c_cflag |=  CS8;

   //Disable Hardware flowcontrol
   //Enable Raw Input
   
   options.c_lflag &=~ (ICANON | ECHO | ECHOE | ISIG);
	
   options.c_oflag &= ~OPOST;

   if(tcsetattr(fd,TCSANOW,&options) == -1)
	printf("Error with tcsetattr = %s\n",strerror(errno));
   else
	printf("tcsetattr success\n");

   fcntl(fd,F_SETFL,0);
}
 

int main()
{
   printf("Welcome to serial program test\n");
   int n,bytes,res;
   char c;
   char buffer;
   pthread_t th1;
   serial_init("/dev/ttyUSB0");
   serial_init("/dev/ttyUSB1");

   res = pthread_create(&th1,NULL,thfun,"Thread1");

  
   while(1)
   {
	read(0,&buffer,1);
        write(fd1,&buffer,1);
	read(fd2,&buffer,1);
   }

}

void *thfun(void *arg)
{
  char ch;
  while(1)
  {
    read(0,&ch,1);
    write(fd2,&ch,1);
    read(fd1,&ch,1);
  }
}
