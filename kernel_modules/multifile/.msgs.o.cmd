savedcmd_msgs.o := ld -m elf_x86_64 -z noexecstack --no-warn-rwx-segments   -r -o msgs.o @msgs.mod 
