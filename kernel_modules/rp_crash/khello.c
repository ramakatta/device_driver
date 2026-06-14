#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kernel Tester");
MODULE_DESCRIPTION("A real-time buggy driver mimicking a null-pointer dereference");

static int __init my_crash_init(void)
{
    // Create a pointer pointing to memory address 0x0 (Null)
    volatile int *corrupt_ptr = NULL;

    pr_alert("Crash Driver: Simulating a real hardware driver memory fault...\n");

    // Attempting to write to address 0x0 forces an instant Page Fault Exception
    *corrupt_ptr = 0xDEADBEEF; 

    return 0;
}

static void __exit my_crash_exit(void)
{
    // This will never be reached
    pr_info("Crash Driver removed\n");
}

module_init(my_crash_init);
module_exit(my_crash_exit);

