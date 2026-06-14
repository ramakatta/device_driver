#ifndef CLOCK_SMC_H
#define CLOCK_SMC_H


/*
 * TF-A SMC IDs
 *
 * 0xC3:
 *   SMC64
 *   Fast call
 *   OEM owning entity
 */
#define RPI4_SMC_GET_FREQ   0xC3000001U
#define RPI4_SMC_GET_COUNT  0xC3000002U

/*
 * Linux IOCTL interface
 */
#define RPI4_CLOCK_IOC_MAGIC   'C'

#define RPI4_CLOCK_GET_FREQ \
    _IOR(RPI4_CLOCK_IOC_MAGIC, 1, uint64_t)

#define RPI4_CLOCK_GET_COUNT \
    _IOR(RPI4_CLOCK_IOC_MAGIC, 2, uint64_t)

#define RPI4_CLOCK_DEVICE_NAME "rpi4_clock"

#endif
