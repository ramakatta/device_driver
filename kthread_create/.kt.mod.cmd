savedcmd_kt.mod := printf '%s\n'   kt.o | awk '!x[$$0]++ { print("./"$$0) }' > kt.mod
