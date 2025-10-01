savedcmd_atomic.mod := printf '%s\n'   atomic.o | awk '!x[$$0]++ { print("./"$$0) }' > atomic.mod
