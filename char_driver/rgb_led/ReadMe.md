This is just a basic linux character device driver which explains about the gpio operations.
The LED is connected to one of GPIO header of Raspberry PI.
This driver providing framework to connect 3 LEDs with 3 device file instances

To insert module in the kernel:
insmod rgbled.ko

To remove module from the kernel:
rmmod rgbled.ko



