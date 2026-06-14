#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>

/*
USERSPACE
   |
   | ioctl()
   v
KERNEL
   |
   | arm_smccc_smc()
   v
EL3 / TF-A BL31
   |
   | read CNTFRQ_EL0
   | or
   | read CNTPCT_EL0
   |
   | SMC_RET1()
   v
KERNEL
   |
   | copy_to_user()
   v
USERSPACE
struct arm_smccc_res {
    unsigned long a0;
    unsigned long a1;
    unsigned long a2;
    unsigned long a3;
};
*/

/*
 * ============================================================
 * Must match the kernel module
 * ============================================================
 */

#define RPI4_CLOCK_IOC_MAGIC   'C'

#define RPI4_CLOCK_GET_FREQ \
    _IOR(RPI4_CLOCK_IOC_MAGIC, 1, uint64_t)

#define RPI4_CLOCK_GET_COUNT \
    _IOR(RPI4_CLOCK_IOC_MAGIC, 2, uint64_t)


#define DEVICE_NAME "/dev/rpi4_clock"


int main(void)
{
    int fd;
    uint64_t frequency;
    uint64_t counter;


    /*
     * --------------------------------------------------------
     * Open device
     * --------------------------------------------------------
     */

    fd = open(DEVICE_NAME, O_RDWR);

    if (fd < 0) {
        fprintf(
            stderr,
            "Failed to open %s: %s\n",
            DEVICE_NAME,
            strerror(errno));

        return EXIT_FAILURE;
    }


    /*
     * --------------------------------------------------------
     * Get CNTFRQ_EL0
     * --------------------------------------------------------
     */

    if (ioctl(
            fd,
            RPI4_CLOCK_GET_FREQ,
            &frequency) < 0) {

        fprintf(
            stderr,
            "GET_FREQ ioctl failed: %s\n",
            strerror(errno));

        close(fd);
        return EXIT_FAILURE;
    }


    /*
     * --------------------------------------------------------
     * Get CNTPCT_EL0
     * --------------------------------------------------------
     */

    if (ioctl(
            fd,
            RPI4_CLOCK_GET_COUNT,
            &counter) < 0) {

        fprintf(
            stderr,
            "GET_COUNT ioctl failed: %s\n",
            strerror(errno));

        close(fd);
        return EXIT_FAILURE;
    }


    /*
     * --------------------------------------------------------
     * Print results
     * --------------------------------------------------------
     */

    printf(
        "Frequency: %llu Hz\n",
        (unsigned long long)frequency);

    printf(
        "Counter:   %llu\n",
        (unsigned long long)counter);


    close(fd);

    return EXIT_SUCCESS;
}
