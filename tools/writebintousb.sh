#!/bin/sh

device=`mount | grep "CRP DISABLD" | cut -d ' ' -f 1`

echo unmounting $device

umount $device

echo write $1 to $device

dd if=$1 of=$device seek=4
