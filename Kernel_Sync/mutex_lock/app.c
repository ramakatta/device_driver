#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#define MTXDEMO_IOC_MAGIC 'M'
#define MTXDEMO_IOC_HOLD  _IOW(MTXDEMO_IOC_MAGIC, 0x01, unsigned int)

static void on_sigint(int sig)
{
   write(1, "demo: caught signal \n", 20);
}

int main(void)
{
    int fd = open("/dev/mtx_demo", O_RDONLY);
    if (fd < 0) {
      perror("open /dev/mtx_demo");
      return 1;
    }

    signal(SIGINT, on_sigint);

    pid_t child = fork();
    if (child < 0) {
        perror("fork");
        return 1;
    }

    if (child == 0) {
         unsigned int seconds = 60;
        fprintf(stderr, "child[%d]: ioctl hold for %u seconds\n", getpid(), seconds);
        if (ioctl(fd, MTXDEMO_IOC_HOLD, &seconds) < 0) {
             perror("ioctl HOLD");
             return 1;
        }
        fprintf(stderr, "child[%d]: released mutex, exiting\n", getpid());
        return 0;
    }

    sleep(1);
    fprintf(stderr, "parent[%d]: about to read() and block on mutex. "
         "From another shell, run: kill -INT %d\n", getpid(), getpid());

     char buf[1];
     ssize_t n = read(fd, buf, sizeof(buf));
     if (n < 0) {
       fprintf(stderr, "parent[%d]: read() failed: %s (errno=%d)\n",
        getpid(), strerror(errno), errno);
    } else {
        fprintf(stderr, "parent[%d]: read() returned %zd\n", getpid(), n);
    }

   kill(child, SIGTERM);
   waitpid(child, NULL, 0);
   close(fd);
   return 0;
}

