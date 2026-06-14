TARGET = custom-make
CFLAGS ?= -Wall 
bindir = $(DESTDIR)/usr/bin

OBJS = custom-make.o

all := $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS)  $^ -o $@ 

install:
	install -d $(bindir)
	install -m 0755 $(TARGET) $(bindir)
uninstall:
	${RM} $(bindir)/$(TARGET)
clean:
	$(RM) $(TARGET) $(OBJS)

.PHONY: all clean install uninstall
