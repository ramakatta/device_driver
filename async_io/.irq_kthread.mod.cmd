savedcmd_irq_kthread.mod := printf '%s\n'   irq_kthread.o | awk '!x[$$0]++ { print("./"$$0) }' > irq_kthread.mod
