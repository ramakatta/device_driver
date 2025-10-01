savedcmd_kthread_sync.mod := printf '%s\n'   kthread_sync.o | awk '!x[$$0]++ { print("./"$$0) }' > kthread_sync.mod
