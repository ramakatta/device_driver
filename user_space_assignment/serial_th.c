#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<termios.h>
int fd;
void *thfun(void*);
int main()
{
   printf("Welcome to serial program test\n");
   int n,bytes,res;
   char c;
   char buffer;
   pthread_t th1;

   struct termios options;
   //fd = open("/dev/ttyACM0",O_RDWR | O_NOCTTY);
   fd = open("/dev/ttyUSB0",O_RDWR | O_NOCTTY);

   if(fd < 0)
   {
	perror("open_port:Unable to open /dev/ttyUSB0\n");
   }
   else
   {
	//fcntl(fd,F_SETFL,FNDELAY);
   }
   tcgetattr(fd,&options);	
   cfsetispeed(&options,B115200);
   cfsetospeed(&options,B115200);

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
 
   n =  write(fd,"Hello world\n",11);
   res = pthread_create(&th1,NULL,thfun,"Thread1");

   if(n < 0)
   {
	printf("write failed\n");
   }
  
   while(1)
   {
	read(0,&buffer,1);
        write(fd,&buffer,1);
   }

}

void *thfun(void *arg)
{
  char ch;
  while(1)
  {
    read(fd,&ch,1);
    write(1,&ch,1);
  }
}
