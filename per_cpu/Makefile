obj-m := percpu.o
KDIR := /lib/modules/$(shell uname -r)/build
#KDIR := /usr/src/linux-headers-3.8.81.0 
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	$(shell rm -f modules.order Module.markers)

install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install

