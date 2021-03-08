mkdir img
sudo mount -o loop floppy.img img
sudo cp src/kernel img
sudo umount img
rmdir img