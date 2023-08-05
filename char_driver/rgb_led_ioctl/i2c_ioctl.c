#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int file;
    char *filename = "/dev/i2c-1";
    char buffer[3];
    
    if ((file = open(filename, O_RDWR)) < 0) {
	    /* ERROR HANDLING: you can check errno to see what went wrong */
	    perror("Failed to open the i2c bus");
	    exit(1);
    }

    int addr = 0x68;          // The I2C address of the ADC
    if (ioctl(file, I2C_SLAVE, addr) < 0) {
	    printf("Failed to acquire bus access and/or talk to slave.\n");
	        /* ERROR HANDLING; you can check errno to see what went wrong */
	    exit(1);
    }

    buffer[0]=0xf5;
    
    if(write(file,buffer,1)!=1){
	printf("Failed to write register ");
    }
    if(read(file,buffer,1)!=1){
	            printf("Failed to read register ");
     }
     printf("0x%x\n",buffer[0]);
}
