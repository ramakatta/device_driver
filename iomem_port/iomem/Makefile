obj-m += iomem.o

CCPREFIX := arm-linux-gnueabihf-

KDIR = /home/vector/Downloads/linux

all:
	make ARCH=arm CROSS_COMPILE=${CCPREFIX} -C $(KDIR)  M=$(shell pwd) modules

clean:
	make ARCH=arm CROSS_COMPILE=${CCPREFIX} -C $(KDIR)  M=$(shell pwd) clean

