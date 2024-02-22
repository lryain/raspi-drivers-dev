#include <linux/init.h>
#include <linux/module.h>

//#include <linux/device.h>
//#include <linux/uaccess.h>

static struct file_operations simple_fops;
static int major = 0;
static int ker_val = 123;

int __init simple_drv_init(void)
{
	printk("Simple driver init.\n");
	major = register_chrdev(0, "simple_drv", &simple_fops);
	printk("Register char device major: %d \n", major);	
	return 0;
}

static ssize_t simple_read(struct file *file, char __user *buf, size_t size, loff_t *offset)
{
	int err;
	printk("%s fs line %d\n", __FILE__, __FUNCTION__, __LINE__);
	copy_to_user(buf, &ker_val, 4);
	return 4;
}

static ssize_t simple_write(struct file * file, const char __user *buf, size_t size, loff_t *offset)
{
	int err;
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	copy_from_user(&ker_val, buf, 4);
	return 4;
}

static struct file_operations simple_fops = {
	.owner	 = THIS_MODULE,
	.read	 = simple_read,
	.write 	 = simple_write,
};

module_init(simple_drv_init);

void __exit simple_drv_exit(void)
{
	printk("bye kernel\n");
	unregister_chrdev(major, "simple_drv");
}

module_exit(simple_drv_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("hello module for RPi CM4");
MODULE_ALIAS("Simple_drv");
MODULE_AUTHOR("lryain");

