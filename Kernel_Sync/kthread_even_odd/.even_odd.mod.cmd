savedcmd_even_odd.mod := printf '%s\n'   even_odd.o | awk '!x[$$0]++ { print("./"$$0) }' > even_odd.mod
