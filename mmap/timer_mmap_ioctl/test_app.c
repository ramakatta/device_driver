#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "timer_ioctl.h"

int main(void)
{
    int fd;
    struct timer_reg reg;
    __u64 timer;

    fd = open("/dev/timer_mmap", O_RDWR);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    /* Read CLO */
    reg.reg = TIMER_CLO;

    if (ioctl(fd, TIMER_IOC_READ_REG, &reg) < 0) {
        perror("TIMER_IOC_READ_REG");
        close(fd);
        return 1;
    }

    printf("CLO = 0x%08x\n", reg.value);

    /* Read 64-bit timer */
    if (ioctl(fd, TIMER_IOC_GET_TIME, &timer) < 0) {
        perror("TIMER_IOC_GET_TIME");
        close(fd);
        return 1;
    }

    printf("Timer = %llu us\n",
           (unsigned long long)timer);

    close(fd);

    return 0;
}
