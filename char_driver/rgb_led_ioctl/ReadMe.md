This is just a basic linux character device driver which explains about the gpio operations.
The LED is connected to one of GPIO header of Raspberry PI.
This driver providing framework to connect 3 LEDs with 3 device file instances
The LED on/off will be controlled with IOCTL

To insert module in the kernel:
insmod rgbled_ioctl.ko

To remove module from the kernel:
rmmod rgbled_ioctl.ko



