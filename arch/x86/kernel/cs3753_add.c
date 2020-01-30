#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/uaccess.h>
asmlinkage long sys_cs3753_add(int a, int b, int* result) {
	int sum;
	sum = a + b;

	copy_to_user(result, &sum, sizeof(int));

	printk(KERN_ALERT "First number is %d\n", a);
	printk(KERN_ALERT "Second number is %d\n", b);

	printk(KERN_ALERT "Result of addition is %d\n", sum);
	return 0;
}
