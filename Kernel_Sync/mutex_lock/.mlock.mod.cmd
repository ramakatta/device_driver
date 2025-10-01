savedcmd_mlock.mod := printf '%s\n'   mlock.o | awk '!x[$$0]++ { print("./"$$0) }' > mlock.mod
