savedcmd_percpu.mod := printf '%s\n'   percpu.o | awk '!x[$$0]++ { print("./"$$0) }' > percpu.mod
