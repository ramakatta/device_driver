/***************************************************************************//**
*  \file       test_app.c
*
*  \details    Userspace application to test the Device driver
*
*
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int8_t write_buf[2048];
int8_t read_buf[2048];
struct tpm_cap
{
  char name[20];
  char type[20];
  char fw_version[20];
  char platform[25];
  char board_name[25];
  char version[10];
  char sid[100];
  char fpga_name[20];
  char fpga_version[10];
};

struct tpm_cap tpm_cap={{"Intel"},{"itpm"},{"45.42.1"},{"explorer6"},\
	{"Lion"},{"2.1.1"},{"102323232132-3434"},{"BYAKKO"},{"1.0.034"}};
int main()
{
        int fd;
        char option;
	sprintf(write_buf,"%s%s%s\n%s%s%s\n%s%s%s\n%s%s%s\n%s%s%s\n%s%s%s\n%s%s%s\n%s%s%s\n%s%s%s\n",
			"<sbc><tpm><name>",tpm_cap.name,"</name></tpm></sbc>",
			"<sbc><tpm><type>",tpm_cap.type,"</type></tpm></sbc>",
			"<sbc><tpm><fwversion>",tpm_cap.fw_version,"</fwversion></tpm></sbc>",
			"<sbc><board><platform>",tpm_cap.platform,"</platform></board></sbc>",
			"<sbc><board><name>",tpm_cap.board_name,"</name></board></sbc>",
			"<sbc><board><version>",tpm_cap.version,"</version></board></sbc>",
			"<sbc><board><sid>",tpm_cap.sid,"</sid></board></sbc>",
			"<sbc><fpga><name>",tpm_cap.fpga_name,"</name></fpga></sbc>",
			"<sbc><fpga><version>",tpm_cap.fpga_version,"</version></fpga></sbc>");
		
        printf("*********************************\n%s",write_buf);
#if 1 
        fd = open("/dev/etx_device", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }

        while(1) {
                printf("****Please Enter the Option******\n");
                printf("        1. Write               \n");
                printf("        2. Read                 \n");
                printf("        3. Exit                 \n");
                printf("*********************************\n");
                scanf(" %c", &option);
                printf("Your Option = %c\n", option);
                
                switch(option) {
                        case '1':
                                /*printf("Enter the string to write into driver :");
                                scanf("  %[^\t\n]s", write_buf);*/
                                printf("Data Writing ...");
                                write(fd, write_buf, strlen(write_buf)+1);
                                printf("Done!\n");
                                break;
                        case '2':
                                printf("Data Reading ...");
                                read(fd, read_buf, 1024);
                                printf("Done!\n\n");
                                printf("Data = %s\n\n", read_buf);
                                break;
                        case '3':
                                close(fd);
                                exit(1);
                                break;
                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;
                }
        }
        close(fd);
#endif
}
