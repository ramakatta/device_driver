TARGET = custom-make
all := $(TARGET)
CFLAGS ?= -Wall 
bindir = $(DESTDIR)/usr/bin

OBJS = custom-make.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS)  $^ -o $@

install:
	install -d ${D}$(bindir)
	install -m 0755 $(TARGET) ${D}$(bindir)
uninstall:
	${RM} ${D}$(bindir)/$(TARGET)
clean:
	$(RM) $(TARGET) $(OBJS)

.PHONY: all clean install uninstall
