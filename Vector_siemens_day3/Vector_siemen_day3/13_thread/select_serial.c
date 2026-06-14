#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<termios.h>
#include<signal.h>
int fd;
void *thfun(void*);
void myhandler(int signo)
{
   close(fd);
   exit(0);
}
int main()
{
   printf("Welcome to serial program test\n");
   int n,bytes,res,stat;
   char buffer,buffer2;
   fd_set readfds, testfds; 
   signal(SIGINT,myhandler);
   struct termios options;
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
 
   n =  write(fd,"Hello world\n",11);

   if(n < 0)
   {
	printf("write failed\n");
   }
   FD_ZERO(&readfds);
   FD_SET(0,&readfds);
   FD_SET(fd,&readfds);
  
   while(1)
   {
	testfds = readfds;
        stat = select(fd+1, &testfds,NULL,NULL,NULL);
        if(FD_ISSET(0,&testfds))
        {
	  read(0,&buffer,1);
          write(fd,&buffer,1);
        }
        if(FD_ISSET(fd,&testfds))
        {
	  read(fd,&buffer2,1);
          write(1,&buffer2,1);
        }

   }

}

