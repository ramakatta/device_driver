savedcmd_khello_arg.mod := printf '%s\n'   khello_arg.o | awk '!x[$$0]++ { print("./"$$0) }' > khello_arg.mod
