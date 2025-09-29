obj-m := irq_kthread.o
KDIR := /lib/modules/$(shell uname -r)/build
#KDIR  := /home/asr907/SDK/QorIQ-SDK-T1040-BSP0.2-20140310-yocto/build_t1040qds_release/tmp/sysroots/t1040qds/usr/src/kernel
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

