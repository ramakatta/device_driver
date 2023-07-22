This program is  Quick test to see kernel printk's at all 8 log levels
when run on a console, only those messages < current (console) log level
(seen as the first integer in the output of /proc/sys/kernel/printk) will
appear on the console device.

To insert module in the kernel:
insmod printk_loglvl.ko

To remove module from the kernel:
rmmod printk_loglvl.ko


