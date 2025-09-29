savedcmd_core_lkm.mod := printf '%s\n'   core_lkm.o | awk '!x[$$0]++ { print("./"$$0) }' > core_lkm.mod
