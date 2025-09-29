savedcmd_mod2.mod := printf '%s\n'   mod2.o | awk '!x[$$0]++ { print("./"$$0) }' > mod2.mod
