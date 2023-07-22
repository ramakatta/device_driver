In userspace, C main() applicaiton takes input via command line arguments argc and argv[] paramters. Similarly Linux kernel modules allows user to pass arguments while inserting kernel modules.

To insert module in the kernel with arguments:
insmod khello_arg.ko msg="pci" io=0xA

To remove module from the kernel:
rmmod khello_arg.ko


