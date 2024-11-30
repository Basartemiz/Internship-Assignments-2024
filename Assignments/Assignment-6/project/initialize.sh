#this will remove the image file if it exists
if [ -f "storage_vgc.img" ]; then
    echo   "removing"
    rm storage_vgc.img
fi

#create the disk image
dd if=/dev/zero of=storage_vgc.img bs=1M count=100

#format the disk image 
mkfs.ext4 storage_vgc.img


