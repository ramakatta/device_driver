#include <stdint.h>
#include <stdio.h>

int main(void) {
    uint64_t rcs = 0;
    int ring_level;

    // Use inline assembly to move the value of the CS register into the 'rcs' variable
    asm volatile ("mov %%cs, %0" : "=r" (rcs));

    // The current privilege level is in the bottom two bits (rcs & 3)
    ring_level = (int) (rcs & 3);

    printf("This program is running on ring level %d.\n", ring_level);

    return 0;
}

