savedcmd_msgs.mod := printf '%s\n'   util/saymessage.o sayhello.o | awk '!x[$$0]++ { print("./"$$0) }' > msgs.mod
