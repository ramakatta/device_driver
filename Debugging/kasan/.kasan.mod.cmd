savedcmd_kasan.mod := printf '%s\n'   kasan.o | awk '!x[$$0]++ { print("./"$$0) }' > kasan.mod
