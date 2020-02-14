
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

#define BUFF_SIZE 1024 /* size of the buffer */
#define MAJOR_NUMBER 307 /* because 7 ate 9 */
#define DEVICE_NAME "pa2_character_device" /* name */

static char *device_buff;
static int open_Count = 0;
static int close_Count = 0;

int simple_char_driver_open(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	open_Count++;
	printk("Open Count: %d\n", open_Count);
	return 0; 
}

int simple_char_driver_close(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	close_Count++;
	printk("Close Count: %d\n", close_Count);
	return 0; 
}

loff_t simple_char_driver_seek(struct file *pfile, loff_t offset, int whence){
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	loff_t new_offset = 0;
	switch(whence) {
		case 0: /* SEEK_SET: index into buffer */
			new_offset = offset;
			break;
		case 1: /* SEEK_CUR: increment current positon */
			new_offset = pfile->f_pos + offset;
			break;
		case 2: /* SEEK_END: go to end of buffer */
			new_offset = BUFF_SIZE - offset;
			break;
	}

	if(new_offset < 0){
		printk(KERN_ALERT "Error: Seeking before buffer");
	}

	if(new_offset > BUFF_SIZE){
		printk(KERN_ALERT "Error: Seeking after buffer");
	}

	/* make the file position equal to our new offset*/
	pfile->f_pos = new_offset;

	/*return how many bytes the new offset is */
	return new_offset;
}

ssize_t simple_char_driver_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	
	/* max bytes that can be read from kernel buffer */
	int MAX_BYTES = BUFF_SIZE - *offset;
	
	/*number of bytes to read */
	/*number of bytes that we passed through */
	int BYTES_TO_READ;
	int BYTES_READ;
	
	/* if buffer is larger than the length of user buffer, only can read as much length can hold*/
	if(MAX_BYTES > length){
		BYTES_TO_READ = length;
	} else {
		BYTES_TO_READ = MAX_BYTES;
	}
	/* test for empty file */
	if(BYTES_TO_READ == 0){
		printk(KERN_ALERT "END OF DEVICE \n");
	}
	/* how many bytes did we read */
	BYTES_READ = BYTES_TO_READ - copy_to_user(buffer, device_buff + *offset, BYTES_TO_READ);	
	printk(KERN_ALERT "DEVICE READ: %d BYTES\n", BYTES_READ);
	/* move the offset hoewver many bytes we read */
	*offset += BYTES_READ;

	printk(KERN_ALERT "DEVICE FINISH READING");
	/*return how many bytes read*/
	return BYTES_READ; /* 0 for empty file */
}

ssize_t simple_char_driver_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset){
	
	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	
	/* max num of bytes that can be WRITE from offset to BUFF_SIZE */
	int MAX_BYTES = BUFF_SIZE - *offset;
	/*number of bytes to WRITE */
	/*number of bytes WRITTEN */
	int BYTES_TO_WRITE, BYTES_WROTE;
	/* logical statements about length of writing and buffer */	
	if(MAX_BYTES > length){
		BYTES_TO_WRITE = length;
	} else {
		BYTES_TO_WRITE = MAX_BYTES;
	}
	/* the bytes we wrote is equal with the total number of bytes to write, minus the remaining but we have yet read
		this remaaing bit comees from user space*/
	BYTES_WROTE = BYTES_TO_WRITE - copy_from_user(device_buff + *offset, buffer, BYTES_TO_WRITE);
	/* when we say howmany bytes we wrote */
	printk(KERN_ALERT "DEVICE WROTE: %d BYTES\n", BYTES_WROTE);
	/* move the offset by however many bytes we wrote*/
	*offset += BYTES_WROTE;
	/* alert kernel that we are finished */
	printk(KERN_ALERT "DEVICE FINISHED WRITING\n");

	return BYTES_WROTE; /*returning the length of the bytes.*/
}

/* file ops on this device */
struct file_operations simple_char_driver_file_operations ={
	.owner		= THIS_MODULE,					/* in the file op struct */
	.open 		= simple_char_driver_open, 		/* opens */
	.release	= simple_char_driver_close, 	/* closes*/
	.llseek 	= simple_char_driver_seek, 		/* seeks */
	.read 		= simple_char_driver_read, 		/* reads */
	.write 		= simple_char_driver_write, 	/* writes */
};

int simple_char_driver_init(void){

	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);

	device_buff = kmalloc(BUFF_SIZE, GFP_KERNEL);

	register_chrdev(MAJOR_NUMBER, DEVICE_NAME, &simple_char_driver_file_operations);
	return 0;
}

void simple_char_driver_exit(void){

	printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
	if(device_buff){
		kfree(device_buff);
	}

	unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME);
}

module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);

