savedcmd_spin.mod := printf '%s\n'   spin.o | awk '!x[$$0]++ { print("./"$$0) }' > spin.mod
