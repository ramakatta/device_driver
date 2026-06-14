obj-m := khello_2.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
#ccflags-y := -DTRIGGER_OOPS
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

