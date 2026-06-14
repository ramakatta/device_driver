#ifndef TIMER_IOCTL_H
#define TIMER_IOCTL_H

#include <linux/ioctl.h>
#include <linux/types.h>

/*
 * Raspberry Pi System Timer registers
 */
#define TIMER_CS         0x00
#define TIMER_CLO        0x04
#define TIMER_CHI        0x08
#define TIMER_C0         0x0C
#define TIMER_C1         0x10
#define TIMER_C2         0x14
#define TIMER_C3         0x18

/*
 * Register/value pair used by READ_REG and WRITE_REG.
 */
struct timer_reg {
    __u32 reg;
    __u32 value;
};

/*
 * IOCTL magic number
 */
#define TIMER_IOC_MAGIC  'T'

/*
 * Read a timer register.
 *
 * Input:
 *     struct timer_reg.reg
 *
 * Output:
 *     struct timer_reg.value
 */
#define TIMER_IOC_READ_REG \
    _IOWR(TIMER_IOC_MAGIC, 1, struct timer_reg)

/*
 * Write a timer register.
 *
 * Input:
 *     struct timer_reg {
 *         .reg   = register offset,
 *         .value = value to write
 *     };
 */
#define TIMER_IOC_WRITE_REG \
    _IOW(TIMER_IOC_MAGIC, 2, struct timer_reg)

/*
 * Get the complete 64-bit system timer value.
 */
#define TIMER_IOC_GET_TIME \
    _IOR(TIMER_IOC_MAGIC, 3, __u64)

/*
 * Clear timer match/status bits.
 *
 * Bits 0-3 correspond to C0-C3 match status.
 */
#define TIMER_IOC_CLEAR_STATUS \
    _IOW(TIMER_IOC_MAGIC, 4, __u32)

#endif /* TIMER_IOCTL_H */
