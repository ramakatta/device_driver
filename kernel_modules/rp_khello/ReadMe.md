This is just a basic linux kernel module.This Makefile written to compile for Raspberry PI-3 board. This kernel module will print some debug messages at the init and exit time. This module also prints information about process. Prints data from task_struct data structure

To insert module in the kernel on Raspberry PI Board:
insmod khello.ko

To remove module from the kernel on Raspberry PI Board
rmmod khello.ko


