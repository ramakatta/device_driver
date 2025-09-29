savedcmd_mod1.mod := printf '%s\n'   mod1.o | awk '!x[$$0]++ { print("./"$$0) }' > mod1.mod
