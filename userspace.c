#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{
         long int hello_call = syscall(548);
         printf("System call sys_hello returned %ld\n", hello_call);
	 int result;
	 long int add_call  = syscall(549,2,5,&result);
         printf("Result is %d\n", result);
	 printf("System call sys_cs3753_add returned %ld\n", add_call);
         return 0;
}
