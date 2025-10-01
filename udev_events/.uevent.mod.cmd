savedcmd_uevent.mod := printf '%s\n'   uevent.o | awk '!x[$$0]++ { print("./"$$0) }' > uevent.mod
