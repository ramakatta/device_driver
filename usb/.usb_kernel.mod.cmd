savedcmd_usb_kernel.mod := printf '%s\n'   usb_kernel.o | awk '!x[$$0]++ { print("./"$$0) }' > usb_kernel.mod
