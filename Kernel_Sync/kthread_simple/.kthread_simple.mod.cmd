savedcmd_kthread_simple.mod := printf '%s\n'   kthread_simple.o | awk '!x[$$0]++ { print("./"$$0) }' > kthread_simple.mod
