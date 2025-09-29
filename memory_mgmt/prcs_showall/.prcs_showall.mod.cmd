savedcmd_prcs_showall.mod := printf '%s\n'   prcs_showall.o | awk '!x[$$0]++ { print("./"$$0) }' > prcs_showall.mod
