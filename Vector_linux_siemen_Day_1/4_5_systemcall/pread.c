#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

main() {
  int ret, file_descriptor;
  off_t off=5;
  char buf[]="Test text check";

  if ((file_descriptor = open("test.output", O_RDWR|O_CREAT)) < 0)
     perror("creat() error");
  else {
    if (-1==(ret=write(file_descriptor, buf, sizeof(buf)-1)))
       perror("write() error");
    if (close(file_descriptor)!= 0)
       perror("close() error");
  }

  if ((file_descriptor = open("test.output", O_RDONLY)) < 0)
    perror("open() error");
  else {
    ret = pread(file_descriptor, buf, ((sizeof(buf)-1)-off), off);
    buf[ret] = 0x00;
    printf("block pread: \n<%s>\n", buf);
    if (close(file_descriptor)!= 0)
       perror("close() error");
  }
  if (unlink("test.output")!= 0)
     perror("unlink() error");
}
