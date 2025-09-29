savedcmd_current_affairs.mod := printf '%s\n'   current_affairs.o | awk '!x[$$0]++ { print("./"$$0) }' > current_affairs.mod
