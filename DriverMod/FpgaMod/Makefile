ifneq ($(KERNELRELEASE),)
	module-objs := FpgaMod.o
	obj-m := FpgaMod.o
else

CUR_DIR  = $(shell pwd)
CROSS_COMPILE	:=$(CUR_DIR)/../../arm-2014.05/bin/arm-none-linux-gnueabi-

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld

PWD:=$(shell pwd)
KDIR:=../../BootLoader/linux-2.6.30

all:
	@$(MAKE) -C $(KDIR) M=$(PWD) modules -s
	@\cp FpgaMod.ko ../../rootfs/lib/modules/2.6.30/
	@\cp FpgaMod.ko ../../rootfs_min/lib/modules/2.6.30/
#@sz FpgaMod.ko

f:
	@../../APP/astyle *.c -cs2bCSKNwYMm2pPDHk1n >/dev/null
	@../../APP/astyle *.h -cs2bCSKNwYMm2pPDHk1n >/dev/null

clean:
	@rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions *.mod.c .*.cmd *.order *.symvers 

endif

