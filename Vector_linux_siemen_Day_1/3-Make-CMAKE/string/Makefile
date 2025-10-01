#Without .PHONY, if a file or directory exists with the same name as the target, make may skip that rule, thinking it's aAlready up to date. If a file named clean exists in your directory, running make clean will do nothing
.PHONY: clean
CC = gcc
CFLAGS = -c 
OBJS = main.o mystrlen.o mystrcpy.o mystrcmp.o mystrrev.o 
string: $(OBJS)
	$(CC) $(OBJS) -o string
main.o: main.c
	$(CC) $(CFLAGS) main.c
mystrlen.o: mystrlen.c
	$(CC) $(CFLAGS) mystrlen.c
mystrcpy.o: mystrcpy.c
	$(CC) $(CFLAGS) mystrcpy.c
mysrcmp.o: mystrcmp.c
	$(CC) $(CFLAGS) mystrcmp.c
install:
	cp string /usr/local/bin
clean:
	rm *.o string 
