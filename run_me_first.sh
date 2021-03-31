#!/bin/sh

if [ ! -d rootfs ];
then
	tar -xavf rootfs.tlz
fi

if [ ! -d rootfs_min ];
then
	tar -xavf rootfs_min.tlz
fi

if [ ! -d 4.3.3 ];
then
	tar -xavf 4.3.3.tlz
fi

if [ ! -d arm-2014.05 ];
then
	tar -xavf arm-2014.05.tlz 
fi

