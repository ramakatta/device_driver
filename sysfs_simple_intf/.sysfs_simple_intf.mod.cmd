savedcmd_sysfs_simple_intf.mod := printf '%s\n'   sysfs_simple_intf.o | awk '!x[$$0]++ { print("./"$$0) }' > sysfs_simple_intf.mod
