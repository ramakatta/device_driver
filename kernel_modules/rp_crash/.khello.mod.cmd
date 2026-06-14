savedcmd_khello.mod := printf '%s\n'   khello.o | awk '!x[$$0]++ { print("./"$$0) }' > khello.mod
