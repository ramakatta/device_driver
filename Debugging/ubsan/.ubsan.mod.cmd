savedcmd_ubsan.mod := printf '%s\n'   ubsan.o | awk '!x[$$0]++ { print("./"$$0) }' > ubsan.mod
