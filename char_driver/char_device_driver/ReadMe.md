This is just a basic linux device driver which explains about the real read and write of the device file.

Build the application using the below command for Ubuntu and Raspberry Pi.
		gcc -o test_app test_app.c
Build the application using the below command for Raspberry Pi
		arm-linux-gnueabihf-gcc -o test_app test_app.c

insmod driver.ko

rmmod driver.ko


