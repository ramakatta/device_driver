savedcmd_misc_driver.mod := printf '%s\n'   misc_driver.o | awk '!x[$$0]++ { print("./"$$0) }' > misc_driver.mod
