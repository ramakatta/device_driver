savedcmd_ioregion.mod := printf '%s\n'   ioregion.o | awk '!x[$$0]++ { print("./"$$0) }' > ioregion.mod
