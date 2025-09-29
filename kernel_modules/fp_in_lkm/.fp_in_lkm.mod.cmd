savedcmd_fp_in_lkm.mod := printf '%s\n'   fp_in_lkm.o | awk '!x[$$0]++ { print("./"$$0) }' > fp_in_lkm.mod
