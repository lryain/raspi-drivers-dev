#include <linux/init.h>
#include <linux/module.h>
#include <asm/io.h>

#define BCM2711_PERI_BASE		0xFE000000
#define BCM2711_GPIO_BASE		(BCM2711_PERI_BASE + 0x200000)
#define BCM2711_GPIO_FSEL0_OFFSET	0x0
#define BCM2711_GPIO_SET0_OFFSET	0x1C
#define BCM2711_GPIO_CLR0_OFFSET	0x28

static void* gpio = 0;

static int __init rgbled_init(void)
{
  // get the mem dress of the GPIO
  gpio = ioremap(BCM2711_GPIO_BASE, 0xB0);

  // set bit2,6,9 to OUTPUT
  int val = ioread32(gpio + BCM2711_GPIO_FSEL0_OFFSET);
  val &= ~(7 << 6);
  val |= 1 << 6;

  val &= ~(7 << 9);
  val |= 1 << 9;

  val &= ~(7 << 12);
  val |= 1 << 12;

  // GPIO bit2 output 0
  iowrite32(val, gpio);
  iowrite32(1 << 2, gpio + BCM2711_GPIO_CLR0_OFFSET);
  iowrite32(1 << 3, gpio + BCM2711_GPIO_CLR0_OFFSET);
  iowrite32(1 << 4, gpio + BCM2711_GPIO_CLR0_OFFSET);

  return 0;
}

module_init(rgbled_init);

static void __exit rgbled_exit(void)
{
  // GPIO bit2 output 1
  iowrite32(1 << 2, gpio + BCM2711_GPIO_SET0_OFFSET);
  iowrite32(1 << 3, gpio + BCM2711_GPIO_SET0_OFFSET);
  iowrite32(1 << 4, gpio + BCM2711_GPIO_SET0_OFFSET);
  iounmap(gpio);
}

module_exit(rgbled_exit);

MODULE_LICENSE("GPL");
