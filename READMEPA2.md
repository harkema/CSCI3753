
1. Make modules folder

2. run sudo mknod -m 777 /dev/pa2_character_device 307 0

3. run make -C /lib/modules/$(uname -r)/build M=$PWD modules

4. run sudo insmod pa2_char_device.ko

5. sudo gcc charTestProgram.c -o charTestProgram
