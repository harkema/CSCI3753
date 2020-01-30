Kiana Harkema
kiana.harkema@colorado.edu
CSCI 3753 Spring 2020

arch/x86/kernel/cs3753_add.c: Contains the system call definition to add two integers. Takes in two integers, a pointer to a memory address in user space, and returns the sum.

arch/x86/kernel/Makefile: Created custom objects definitions here for helloworld and cs3753_add

arch/x86/entry/entry/syscalls/syscall_64.tbl: Helloworld and cs3753_add entires added here

include/linux/syscalls.h: Function definitions located here

/var/log/syslog: Logs of successful runs of hellworld and cs3753_add (displays results of addition)

userspace.c: Source code for test programs

To run and test both helloworld and cs3753, userspace.c need to be compiled and its cooresponding .o files needs to be run:

sudo gcc userspace.c

sudo ./a.out

After running this, in the user space, the results of the helloworld call and cs3753 call will be displayed. Check syslog for more information regarding what is occuring in the kernel space.
