savedcmd_irq_thread_shot.mod := printf '%s\n'   irq_thread_shot.o | awk '!x[$$0]++ { print("./"$$0) }' > irq_thread_shot.mod
