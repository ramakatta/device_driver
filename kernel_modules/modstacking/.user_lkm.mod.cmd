savedcmd_user_lkm.mod := printf '%s\n'   user_lkm.o | awk '!x[$$0]++ { print("./"$$0) }' > user_lkm.mod
