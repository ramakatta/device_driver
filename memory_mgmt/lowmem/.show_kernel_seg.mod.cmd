savedcmd_show_kernel_seg.mod := printf '%s\n'   kernel_seg.o klib_llkd.o | awk '!x[$$0]++ { print("./"$$0) }' > show_kernel_seg.mod
