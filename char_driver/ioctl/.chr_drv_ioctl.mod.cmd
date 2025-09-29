savedcmd_chr_drv_ioctl.mod := printf '%s\n'   chr_drv_ioctl.o | awk '!x[$$0]++ { print("./"$$0) }' > chr_drv_ioctl.mod
