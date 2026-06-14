savedcmd_rp4_clock.mod := printf '%s\n'   rp4_clock.o | awk '!x[$$0]++ { print("./"$$0) }' > rp4_clock.mod
