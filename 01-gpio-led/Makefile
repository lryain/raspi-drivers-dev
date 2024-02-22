KVERS = $(shell uname -r)
obj-m = rgb-led.o

KDIR = ../../../linux-rpi-5.15.y
CROSS = ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-

all:
	$(MAKE) -C $(KDIR) M=$(PWD) $(CROSS) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(CROSS) clean

