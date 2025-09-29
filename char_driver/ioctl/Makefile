obj-m :=chr_drv_ioctl.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf $(wildcard *.o *.ko mo* Mo* *.mod.c a.out ) 

