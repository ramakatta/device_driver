savedcmd_lowlevel_mem.mod := printf '%s\n'   lowlevel_mem.o | awk '!x[$$0]++ { print("./"$$0) }' > lowlevel_mem.mod
