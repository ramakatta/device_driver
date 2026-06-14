obj-m += khello.o
PWD := $(shell pwd)
CCPREFIX := aarch64-linux-gnu-

KDIR = /home/vector/Downloads/rp4/linux 

all:
	make ARCH=arm64 CROSS_COMPILE=${CCPREFIX} -C $(KDIR)  M=$(shell pwd) modules

clean:
	make ARCH=arm64 CROSS_COMPILE=${CCPREFIX} -C $(KDIR)  M=$(shell pwd) clean

