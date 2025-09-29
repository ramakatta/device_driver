obj-m := refcount.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	$(shell rm -f modules.order Module.markers)

install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install

