#include <linux/module.h>

MODULE_LICENSE("GPL");

void say_message(void);

static int __init sayhello_init(void)
{
	say_message();
	return 0;
}

module_init(sayhello_init);

