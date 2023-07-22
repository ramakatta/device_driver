This is just a basic linux device driver. This kernel module will print some debug messages at the init and exit time.
This module also prints information about process. Prints data from task_struct data structure

To insert module in the kernel:
insmod khello.ko

To remove module from the kernel:
rmmod khello.ko


