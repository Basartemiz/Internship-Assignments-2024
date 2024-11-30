#creates a device link and assing it to the loop device

losetup -fP storage_vgc.img
LOOP_DEVICE=$(losetup -j storage_vgc.img | cut -d':' -f1)
ln -sf $LOOP_DEVICE /dev/device

#mount the device to the mount directory
mount /dev/device /mount

#compile games and main menu and put them into bin file

for src_file in "$SRC_DIR"/*.c; do
    binary_name=$(basename "$src_file" .c)
    gcc "$src_file" -o "$BIN_DIR/$binary_name"
done

#mount the files in the bin file 

cp -r bin/* mount/





