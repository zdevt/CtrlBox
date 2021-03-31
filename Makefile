LOCALCONFIG_FILE := APP/mk
include $(LOCALCONFIG_FILE)

CUR_DATE ?= $(shell date +%Y%m%d)
GIT_CMTID ?=$(shell git rev-parse --short HEAD)

all:
	@echo $(VER) $(CUR_DATE) $(GIT_CMTID)

app: gen
	@make -C APP
	@GenUpgFile/gen APP/MAINAPP 0x1 0x1 $(VER) MAIN_$(VER).hs

samplex: app mod
	@echo $(CUR_DATE) >rootfs/app/fs_ver.txt
	@\cp PicBackup/logo_1080P_samplex.bmp rootfs/app/logo_1080P.bmp
	@cd rootfs; tar -cavf ../fs.tlz * >/dev/null
	@GenUpgFile/gen fs.tlz 0x3 0x1 $(VER) fs_$(CUR_DATE)_$(VER)_$(GIT_CMTID)_samplex.hs
	@rm -f fs.tlz

siter: app mod
	@echo $(CUR_DATE) >rootfs/app/fs_ver.txt
	@\cp PicBackup/logo_1080P_siter.bmp rootfs/app/logo_1080P.bmp
	@cd rootfs; tar -cavf ../fs.tlz * >/dev/null
	@GenUpgFile/gen fs.tlz 0x3 0x1 $(VER) fs_$(CUR_DATE)_$(VER)_$(GIT_CMTID)_siter.hs
	@rm -f fs.tlz

fs: app mod
	@echo $(CUR_DATE) >rootfs/app/fs_ver.txt
	@\cp PicBackup/logo_1080P.bmp rootfs/app/logo_1080P.bmp
	@cd rootfs; tar -cavf ../fs.tlz * >/dev/null
	@GenUpgFile/gen fs.tlz 0x3 0x1 $(VER) fs_$(CUR_DATE)_$(VER)_$(GIT_CMTID).hs
	@rm -f fs.tlz

fs_clean:
	@rm -rf rootfs_min rootfs

fsm: app ker mod
	@rm -f rootfs_min/app/fsm.tlz rootfs_min/app/uImage_9G45.bin 
	@cd rootfs_min; tar -cavf ../fsm.tlz * >/dev/null
	@mv fsm.tlz rootfs_min/app
	@\cp uImage_9G45.bin rootfs_min/app

ker: gen
	@cd BootLoader/linux-2.6.30/;\cp CONFIG .config;sh u.sh
	@\cp BootLoader/linux-2.6.30/uImage_9G45.bin .
	@GenUpgFile/gen uImage_9G45.bin 0x4 0x1 $(VER) uImage_$(VER).hs

boot: fsm genboot
	@cd BootLoader/Bootstrap-v1.15; sh u.sh;
	@\cp BootLoader/Bootstrap-v1.15/Bootstrap.bin .
	@cd BootLoader/u-boot-1.3.4; sh u.sh;
	@\cp BootLoader/u-boot-1.3.4/u-boot9g45.bin .
	@cd BootLoader/linux-2.6.30;\cp CONFIG_INITRAMFS .config;sh u.sh
	@\cp BootLoader/linux-2.6.30/uImage_9G45.bin .
	@./genbootloader
#@GenUpgFile/gen bootloader.bin 0x0 0x1 $(VER) boot_$(VER)_$(CUR_DATE).hs
	@GenUpgFile/gen bootloader.bin 0x0 0x1 $(VER) boot_$(CUR_DATE).hs
	@rm -f Bootstrap.bin u-boot9g45.bin uImage_9G45.bin rootfs_min/app/fsm.tlz rootfs_min/app/uImage_9G45.bin
	@mv bootloader.bin boot_$(CUR_DATE).bin
#@sz bootloader.bin

genboot:
	@make -C BootLoader/Tool/
	@cp BootLoader/Tool/genbootloader .

check:
	@sh run_me_first.sh

gen: check
	@make -C GenUpgFile

mod:
	@make -C DriverMod clean
	@make -C DriverMod

bk:
	@tar -cavf rootfs.tlz rootfs >/dev/null
	@tar -cavf rootfs_min.tlz rootfs_min >/dev/null

clean:
	@rm -f *.bin *.hs genbootloader fs.tlz
	
distclean: clean
	@make -C BootLoader/Bootstrap-v1.15  clean
	@make -C BootLoader/u-boot-1.3.4 distclean
	@make -C BootLoader/linux-2.6.30 distclean
	@rm -rf rootfs_min rootfs 4.3.3 arm-2014.05 

