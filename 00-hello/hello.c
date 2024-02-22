#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void)
{
	printk("hello kernel\n");
	return 0;
}

module_init(hello_init);

static void __exit hello_exit(void)
{
	printk("bye kernel\n");
}
module_exit(hello_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("hello module for RPi 3B+");
MODULE_ALIAS("Hello");
MODULE_AUTHOR("lryain");

