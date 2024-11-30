#unmount the device

unmount /dev/device

#detach the loop device
losetup -d /dev/device

#remove the bin file
rm -r bin